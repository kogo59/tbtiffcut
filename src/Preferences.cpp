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
 * Preferences.cpp
 *
 *  Created on: 27.02.2020
 *      Author: kogo
 */

#include <memory>
#include <wx/fileconf.h>

#include "utils.h"
#include "Preferences.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Preferences
 *      Method:  Preferences
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Preferences::Preferences()
{
	read();
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Preferences
 *      Method:  Preferences
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Preferences::~Preferences()
{

}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Preferences
 *      Method:  read
 * Description:
 *--------------------------------------------------------------------------------------
 */
void Preferences::read()
{
	wxFileConfig config("", "", utils::make_ini_filename());

	auto p = wxStandardPaths::Get().GetDocumentsDir();

	SourceDir = config.Read(utils::SourceDir, p);
	OutputDir = config.Read(utils::OutputDir, p);
	TileDim = static_cast<TileDimension>(config.Read(utils::TileDim, 1));
	ColDep = config.Read(utils::ColDep, 0L);
	BuildTAR = config.Read(utils::BuildTAR,0L);
}

