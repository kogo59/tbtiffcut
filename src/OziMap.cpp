/*
 *  This file is part of tbtiffcut.
 *
 *  Copyright (c) 2020 kogo <kogo@gmx.de>
 *
 *  tbtiffcut is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  tbtiffcut is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with tbtiffcut.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * OziMap.cpp
 *
 *  Created on: 28.02.2020
 *      Author: kogo
 */

#include <cmath>
#include <list>
#include <exception>
#include <wx/log.h>
#include <wx/file.h>
#include "utils.h"
#include "gui/tbtiffcutUI.h"
#include "OziMap.h"

constexpr auto OziMapFile1 =
		"\
OziExplorer Map Data File Version 2.2\n\
%s\n\
%S\n\
1 ,Map Code,\n\
WGS 84,WGS 84,   0.0000,   0.0000,WGS 84\n\
Reserved 1\n\
Reserved 2\n\
Magnetic Variation, , , E\n\
Map Projection,Mercator, Polycal, No, AutoCalOnly, No, BSBUseWPX, No\n";

constexpr auto OziMapFile_point =
		"\
Point%02i,xy,  %i,  %i,in, deg,  %3.0f , %9.6f,%c,  %3.0f, %9.6f,%c, grid,   ,           ,           ,%c\n\
";

constexpr auto OziMapFile_point_empty =
		"Point%02i,xy,  ,  ,in, deg,   , ,N, ,  ,W, grid,   ,           ,           ,N\n\
";

constexpr auto OziMapFile2 =
		"\
Projection Setup,,,,,,,,,,\n\
Map Feature = MF ; Map Comment = MC     These follow if they exist\n\
Track File = TF      These follow if they exist\n\
Moving Map Parameters = MM?    These follow if they exist\n\
MM0 , Yes\n\
";

constexpr auto OziMapFile3 =
		"\
MMPNUM,4\n\
MMPXY,1,000000,000000\n\
MMPXY,2,%06i,000000\n\
MMPXY,3,%06i,%06i\n\
MMPXY,4,000000,%06i\n\
";

constexpr auto OziMapFile_mmpll = "MMPLL,%i,%9.6f,%9.6f\n";

constexpr auto OziMapFile4 =
		"\
MM1B,%09.6f\n\
MOP,Map Open Position,0,0\n\
IWH,Map Image Width/Height,%06i,%06i\n\
";

class gdalerr: public std::exception
{
		virtual const char* what() const throw ( )
		{
			return CPLGetLastErrorMsg();
		}
} gdal_error;

class mapfileerr: public std::exception
{
		virtual const char* what() const throw ( )
		{
			return _("OziMapFile creation failed.");
		}
} mapfile_error;

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  OziMap
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
OziMap::OziMap( const wxFileName &fname )
{
	geotiff_file = fname;

	GDALAllRegister();

	OpenGeoTiff();
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  ~OziMap
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
OziMap::~OziMap()
{
	CleanUp();
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  CleanUp()
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
void OziMap::CleanUp()

{
	GDALClose(poDataset);
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  OpenGeoTiff
 * Description:
 *--------------------------------------------------------------------------------------
 */
void OziMap::OpenGeoTiff()
{

	poDataset = (GDALDataset*) GDALOpen(geotiff_file.GetFullPath(), GA_ReadOnly);

	if ( poDataset == NULL )
		throw gdal_error;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  WriteMapFile
 * Description:
 *--------------------------------------------------------------------------------------
 */
void OziMap::WriteMapFile( const wxFileName &m )
{
	double adfGeoTransform[6] =
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	const OGRSpatialReference *hProj = nullptr;
	OGRCoordinateTransformation *hTransform = nullptr;

	auto x_sz = poDataset->GetRasterXSize();
	auto y_sz = poDataset->GetRasterYSize();

	if ( poDataset->GetGeoTransform(adfGeoTransform) == CE_None )
		hProj = poDataset->GetSpatialRef();

	if ( hProj )
	{
		auto hLatLong = hProj->CloneGeogCS();

		if ( hLatLong == nullptr )
			throw gdal_error;
		else
		{
			// Override GEOGCS|UNIT child to be sure to output as degrees
			hLatLong->SetAngularUnits( SRS_UA_DEGREE, CPLAtof(SRS_UA_DEGREE_CONV));

			hLatLong->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

			CPLPushErrorHandler(CPLQuietErrorHandler);

			hTransform = OGRCreateCoordinateTransformation(hProj, hLatLong);

			if ( hTransform == nullptr )
				throw gdal_error;

			CPLPopErrorHandler();

			OGRSpatialReference::DestroySpatialReference(hLatLong);

		}
	}

	auto [UpperLeftX, UpperLeftY] = CalcEdges(adfGeoTransform, 0.0, 0.0,
			hTransform);

	auto [LowerLeftX, LowerLeftY] = CalcEdges(adfGeoTransform, 0.0, y_sz,
			hTransform);

	auto [UpperRightX, UpperRightY] = CalcEdges(adfGeoTransform, x_sz, 0.0,
			hTransform);

	auto [LowerRightX, LowerRightY] = CalcEdges(adfGeoTransform, x_sz, y_sz,
			hTransform);

	OGRCoordinateTransformation::DestroyCT(hTransform);

	wxString png_file = geotiff_file.GetName() + ".png";

	wxString png_file_full = geotiff_file.GetPath()
			+ geotiff_file.GetPathSeparator() + png_file;

	std::list<wxString> mf_output;

	mf_output.emplace_back(wxString::Format(OziMapFile1, png_file, png_file));

	mf_output.emplace_back(wxString::Format(OziMapFile1, png_file, png_file));

	mf_output.emplace_back(FormatPoint(1, 0, 0, UpperLeftX, UpperLeftY));
	mf_output.emplace_back(FormatPoint(2, x_sz - 1, 0, UpperRightX, UpperRightY));
	mf_output.emplace_back(
			FormatPoint(3, x_sz - 1, y_sz - 1, LowerRightX, LowerRightY));
	mf_output.emplace_back(FormatPoint(4, 0, y_sz - 1, LowerLeftX, LowerLeftY));

	for ( int i = 5 ; i <= 30 ; ++i )
		mf_output.emplace_back(wxString::Format(OziMapFile_point_empty, i));

	mf_output.emplace_back(OziMapFile2);

	setlocale( LC_ALL, "C");

	mf_output.emplace_back(
			wxString::Format(OziMapFile3, x_sz - 1, x_sz - 1, y_sz - 1, y_sz - 1));

	mf_output.emplace_back(
			wxString::Format(OziMapFile_mmpll, 1, UpperLeftX, UpperLeftY));
	mf_output.emplace_back(
			wxString::Format(OziMapFile_mmpll, 2, UpperRightX, UpperRightY));
	mf_output.emplace_back(
			wxString::Format(OziMapFile_mmpll, 3, LowerRightX, LowerRightY));
	mf_output.emplace_back(
			wxString::Format(OziMapFile_mmpll, 4, LowerLeftX, LowerLeftY));

	mf_output.emplace_back(wxString::Format(OziMapFile4));

	// ozi.java, method writeMapFile
	// extracted from Mobile Atlas Creator (for trekbuddy)
	double midLat = ((UpperLeftY + LowerLeftY) / 2.0) * M_PI / 180;
	double rlonMax = UpperLeftX * M_PI / 180;
	double rlonMin = UpperRightX * M_PI / 180;
	double Lon50 = (50.0 / x_sz) * fabs(rlonMax - rlonMin);
	double midLon = (rlonMax + rlonMin) / 2.0;
	double lonW = midLon - Lon50;
	double lonE = midLon + Lon50;
	double mDistA = cos(midLat);
	double mDistB = sin((lonW - lonE) / 2.0);
	double mDist = 2.0 * asin(sqrt(mDistA * mDistA * mDistB * mDistB));
	double mm1b = 6399592 * mDist / 100.0;

	mf_output.emplace_back(wxString::Format(OziMapFile4, mm1b, x_sz, y_sz));

	setlocale( LC_ALL, "");

	auto map_filename = utils::rep_underline(m);

	wxFile map_file(map_filename.GetFullPath(), wxFile::write);

	if ( map_file.IsOpened() )
		for ( auto w : mf_output )
			map_file.Write(w);
	else
		throw mapfile_error;

}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  EdgeX
 * Description:
 *--------------------------------------------------------------------------------------
 */
constexpr double OziMap::X_Coor( const double *adfGeoTransform, double x,
		double y )
{
	return adfGeoTransform[0] + adfGeoTransform[1] * x + adfGeoTransform[2] * y;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  EdgeY
 * Description:
 *--------------------------------------------------------------------------------------
 */
constexpr double OziMap::Y_Coor( const double *adfGeoTransform, double x,
		double y )
{
	return adfGeoTransform[3] + adfGeoTransform[4] * x + adfGeoTransform[5] * y;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  CalcEdges
 * Description:
 *--------------------------------------------------------------------------------------
 */
std::tuple<double, double> OziMap::CalcEdges( const double *adfGeoTransform,
		double xe, double ye, OGRCoordinateTransformation *ht )
{
	auto x = xe;
	auto y = ye;
	auto z = 0.0;

	double CornerX = X_Coor(adfGeoTransform, x, y);
	double CornerY = Y_Coor(adfGeoTransform, x, y);

	ht->Transform(1, &CornerX, &CornerY, &z);

	return std::make_tuple(CornerX, CornerY);
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  CalcEdges
 * Description:
 *--------------------------------------------------------------------------------------
 */
const char* OziMap::getHemisphere( double angle, const wxString &axis )
{
	if ( axis == "Long" && angle < 0.0 )
		return "w";
	else if ( axis == "Long" )
		return "E";
	else if ( angle < 0.0 )
		return "S";
	else
		return "N";
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  OziMap
 *      Method:  FormatPoint
 * Description:
 *--------------------------------------------------------------------------------------
 */
wxString OziMap::FormatPoint( int n, int x_px, int y_px, double x, double y )
{
	double f3;
	double f2 = std::modf(x, &f3) * 60.0;

	double f5;
	double f4 = std::modf(y, &f5) * 60.0;

	auto Easting = getHemisphere(x, "Long");
	auto Northing = getHemisphere(y, "Lat");

	setlocale( LC_ALL, "C");

	auto point_n = wxString::Format(OziMapFile_point, n, x_px, y_px, f5, f4,
			*Northing, f3, f2, *Easting, *Northing);

	setlocale( LC_ALL, "");

	return point_n;

}
