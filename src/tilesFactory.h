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
 * tilesFactory.h
 *
 *  Created on: 01.05.2020
 *      Author: kogo
 */

#ifndef TILESFACTORY_H_
#define TILESFACTORY_H_
#include <memory>
#include <vector>

#include <wx/filename.h>
#include <wx/image.h>
#include <wx/string.h>

/*
 * =====================================================================================
 *        Class: Tile
 *  Description: abstract base class
 * =====================================================================================
 */

class Tile
{
	public:
		Tile() = delete;
		Tile( int x, int y, const wxFileName &tiff_name, const wxBitmap &bmp,
				bool first );
		virtual ~Tile()
		{
		}

		Tile( const Tile &other ) = delete;
		Tile( Tile &&other ) = delete;
		Tile& operator=( const Tile &other );
		Tile& operator=( Tile &&other ) = delete;

		virtual void writeTile( const wxFileName &directory, int TileSize,
				std::vector<wxFileName> &file_list ) = 0;

		const wxString& getName();

	protected:
		wxString tile_name;
		wxFileName img_filename;
		bool first_tile = false;
		int x_pos, y_pos;
		const wxBitmap &bitmap;

	private:
};

/*
 * =====================================================================================
 *        Class: pngTile
 *  Description: concrete tile
 * =====================================================================================
 */

class pngTile: public Tile
{
	public:
		using Tile::Tile;
		void writeTile( const wxFileName &directory, int TileSize,
				std::vector<wxFileName> &file_list ) override;
	private:
};

/*
 * =====================================================================================
 *        Class: TileFactory
 *  Description: abstract creator
 * =====================================================================================
 */
class TileFactory
{
	public:
		TileFactory() = delete;
		TileFactory( const wxFileName &fname, int tile_size, int depth );
		virtual ~TileFactory()
		{
		}

		TileFactory( const TileFactory &other ) = delete;
		TileFactory( Tile &&other ) = delete;
		TileFactory& operator=( const TileFactory &other );
		TileFactory& operator=( TileFactory &&other ) = delete;

		virtual std::unique_ptr<Tile> makeTile( bool first = false ) = 0;

		auto getX_Tiles()
		{
			return x_tiles;
		}
		auto getY_Tiles()
		{
			return y_tiles;
		}

	protected:
		wxFileName tiff_file, set_file;
		wxImage tiff_image;
		wxBitmap bitmap;
		int height = 0, width = 0;
		int x_tiles = 0, y_tiles = 0;
		int TileSize = 0;
		int x = 0, y = 0;

	private:

};

/*
 * =====================================================================================
 *        Class: pngTileFactory
 *  Description: concrete creator
 * =====================================================================================
 */

class pngTileFactory: public TileFactory
{
	public:
		using TileFactory::TileFactory;

		virtual std::unique_ptr<Tile> makeTile( bool first = false ) override;

	private:
};

#endif /* TILESFACTORY_H_ */
