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
 * utils.h
 *
 *  Created on: 27.02.2020
 *      Author: kogo
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <wx/string.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>

enum BitsPixel
{
	bp8 = 8, bp32 = 32
};

enum TileDimension
{
	Tile256x256 = 0, Tile512x512 = 1, Tile768x768 = 2, Tile1024x1024 = 3
};

const int TileSize[] =
{ 256, 512, 768, 1024 };

class utils
{
	public:
		static wxString make_ini_filename();
		static wxFileName rep_underline( const wxFileName &m );

		static const char *const SourceDir;
		static const char *const OutputDir;
		static const char *const TileDim;
		static const char *const ColDep;
		static const char *const BuildTAR;

};

#endif /* UTILS_H_ */
