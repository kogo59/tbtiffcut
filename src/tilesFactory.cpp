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
 * tilesFactory.cpp
 *
 *  Created on: 01.05.2020
 *      Author: kogo
 */

#include <wx/log.h>
#include <wx/file.h>
#include <wx/bitmap.h>
#include <wx/quantize.h>
#include <wx/dcmemory.h>

#include "utils.h"
#include "tilesFactory.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Tile
 *      Method:
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Tile::Tile( int x, int y, const wxFileName &tiff_name, const wxBitmap &bmp,
		bool first ) :
		x_pos(x), y_pos(y), bitmap(bmp)
{
	img_filename = tiff_name;
	tile_name = tiff_name.GetName() + '_' + wxString::Format(wxT("%i"), x) + '_'
			+ wxString::Format(wxT("%i"), y);

	first_tile = first;
	x_pos = x;
	y_pos = y;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  TileFactory
 *      Method:
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
TileFactory::TileFactory( const wxFileName &fname, int tile_size, int depth )
{
	wxLogNull noerrormessages;

	tiff_file = fname;

	tiff_image.LoadFile(tiff_file.GetFullPath());
	height = tiff_image.GetHeight();
	width = tiff_image.GetWidth();

	TileSize = tile_size;

	x_tiles = width % tile_size ? width / tile_size + 1 : width / tile_size;
	y_tiles = height % tile_size ? height / tile_size + 1 : height / tile_size;
	x = -TileSize;
	y = -0;

	if ( depth == bp8 )
	{
		wxImage reducedImg;
		auto err = wxQuantize::Quantize(tiff_image, reducedImg);
		bitmap = wxBitmap(reducedImg);
	}
	else
		bitmap = wxBitmap(tiff_image);

}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pngTileFactory
 *      Method:makeTile
 * Description:
 *--------------------------------------------------------------------------------------
 */
std::unique_ptr<Tile> pngTileFactory::makeTile( bool first )
{

	/*
	 if (y > height - TileSize)
	 {
	 y = 0;
	 x += TileSize;
	 }
	 else
	 y += TileSize;

	 if (x > width)
	 return nullptr;
	 */

	if ( x > width - TileSize )
	{
		x = 0;
		y += TileSize;
	}
	else
		x += TileSize;

	if ( y > height )
	{
		return nullptr;
	}

	return std::make_unique<pngTile>(x, y, tiff_file, bitmap, first);

}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pngTileFactory
 *      Method:  writeTile
 * Description:
 *--------------------------------------------------------------------------------------
 */
void pngTile::writeTile( const wxFileName &directory, int TileSize,
		std::vector<wxFileName> &file_list )
{
	auto img = utils::rep_underline(img_filename);

	auto set_file = directory.GetFullPath() + img.GetName() + ".set";
	auto set_dir = directory.GetFullPath() + "set\\";
	auto mode = wxFile::write_append;
	auto ts_w = TileSize;
	auto ts_h = TileSize;

	if ( first_tile )
		mode = wxFile::write;

	auto set = wxFile(set_file, mode);
	set.Write(tile_name + '\n');

	if ( x_pos + TileSize > bitmap.GetWidth() )
		ts_w = bitmap.GetWidth() - x_pos;

	if ( y_pos + TileSize > bitmap.GetHeight() )
		ts_h = bitmap.GetHeight() - y_pos;

	auto tile = wxRect(x_pos, y_pos, ts_w, ts_h);
	auto bmp = bitmap.GetSubBitmap(tile);

	//auto d = bmp.GetDepth();
	//auto dest_bmp = wxBitmap(TileSize, TileSize, d);
	//wxMemoryDC src_dc = wxMemoryDC(bmp);
	//wxMemoryDC dest_dc = wxMemoryDC(dest_bmp);
	//dest_dc.Blit(0,0,bmp.GetWidth(),bmp.GetHeight(),&src_dc,0,0);

	auto wr = bmp.ConvertToImage();
	wr.SetOption(wxIMAGE_OPTION_PNG_FORMAT, wxPNG_TYPE_PALETTE);
	wr.SetOption(wxIMAGE_OPTION_PNG_COMPRESSION_LEVEL, 9);
	wr.SetOption(wxIMAGE_OPTION_PNG_COMPRESSION_MEM_LEVEL, 8);
	wr.SetOption(wxIMAGE_OPTION_PNG_COMPRESSION_STRATEGY, 0);
	wr.SetOption(wxIMAGE_OPTION_PNG_FILTER, 0);
	wr.SetOption(wxIMAGE_OPTION_PNG_COMPRESSION_BUFFER_SIZE, 20 * 1048576); // 20 MB

	file_list.emplace_back(set_dir + tile_name + ".png");

	wr.SaveFile(set_dir + tile_name + ".png", wxBITMAP_TYPE_PNG);

}
