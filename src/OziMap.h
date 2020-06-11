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
 * OziMap.h
 *
 *  Created on: 28.02.2020
 *      Author: kogo
 */

#ifndef OZIMAP_H_
#define OZIMAP_H_

#include <memory>
#include <wx/filename.h>

#include "../include/gdal_priv.h"
#include "../include/cpl_conv.h" // for CPLMalloc()

/*
 * =====================================================================================
 *        Class:  Preferences
 *  Description: Create OziExplorer Map Data File Version 2.2
 * =====================================================================================
 */
class OziMap
{
	public:
		OziMap() = delete;
		OziMap( const wxFileName &fname );
		virtual ~OziMap();
		OziMap( const OziMap &other ) = delete;
		OziMap( OziMap &&other ) = delete;
		OziMap& operator=( const OziMap &other ) = delete;
		OziMap& operator=( OziMap &&other ) = delete;
		void WriteMapFile( const wxFileName &m );
		void CleanUp();

	private:
		void OpenGeoTiff();
		std::tuple<double, double> CalcEdges( const double *adfGeoTransform,
				double xe, double ye, OGRCoordinateTransformation *ht );
		const char* getHemisphere( double angle, const wxString &axis );
	  wxString FormatPoint( int n, int x_px, int y_px, double x, double y );
		constexpr double X_Coor( const double *adfGeoTransform, double x, double y );
		constexpr double Y_Coor( const double *adfGeoTransform, double x, double y );


		GDALDataset *poDataset = nullptr;
		wxFileName geotiff_file;
};

#endif /* OZIMAP_H_ */
