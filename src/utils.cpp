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
 * utils.cpp
 *
 *  Created on: 27.02.2020
 *      Author: kogo
 */

#include <math.h>

#include "gui/tbtiffcut_config.h"
#include "utils.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class: utils
 *      Method: make_ini_filename
 * Description: generate filename for inifile
 *--------------------------------------------------------------------------------------
 */
wxString utils::make_ini_filename()
{

	return wxStandardPaths::Get().GetUserConfigDir()
			+ wxFileName::GetPathSeparator() + INIFILE;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: utils
 *      Method: rep_underline
 * Description: replace underline char in filename (for gpxsee)
 *--------------------------------------------------------------------------------------
 */
wxFileName utils::rep_underline( const wxFileName &m )
{

	auto filename = m;
	auto f = filename.GetFullName();   // workaround for gpxsee
	f.Replace("_", "-");
	filename.SetFullName(f);

	return filename;
}
