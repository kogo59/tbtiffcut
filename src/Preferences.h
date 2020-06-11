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
 * Preferences.h
 *
 *  Created on: 27.02.2020
 *      Author: kogo
 */

#ifndef PREFERENCES_H_
#define PREFERENCES_H_

#include <wx/string.h>

#include "utils.h"

/*
 * =====================================================================================
 *        Class:  Preferences
 *  Description:
 * =====================================================================================
 */
class Preferences
{
	public:
		Preferences();
		virtual ~Preferences();
		Preferences( const Preferences &other ) = delete;
		Preferences( Preferences &&other ) = delete;
		Preferences& operator=( const Preferences &other );
		Preferences& operator=( Preferences &&other ) = delete;

		BitsPixel getColDep() const
		{
			return ColDep == 0 ? bp8 : bp32;
		}

		void setColDep( BitsPixel dp )
		{
			ColDep = dp == bp8 ? 0 : 1;
		}

		const wxString& getOutputDir() const
		{
			return OutputDir;
		}

		void setOutputDir( const wxString &outputDir )
		{
			OutputDir = outputDir;
		}

		const wxString& getSourceDir() const
		{
			return SourceDir;
		}

		void setSourceDir( const wxString &sourceDir )
		{
			SourceDir = sourceDir;
		}

		TileDimension getTileDim() const
		{
			return TileDim;
		}

		void setTileDim( TileDimension tileDim )
		{
			TileDim = tileDim;
		}

		bool getBuildTAR()
		{
			return BuildTAR;
		}

		void setBuildTAR( bool bt )
		{
			BuildTAR = bt;
		}

	protected:

	private:
		void read();

		wxString SourceDir;
		wxString OutputDir;
		TileDimension TileDim;
		int ColDep;
		bool BuildTAR;
};

#endif /* PREFERENCES_H_ */
