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
 * tbtiffcut.cpp
 *
 *  Created on: 24.02.2020
 *      Author: kogo
 */

#include <wx/utils.h>
#include <wx/filefn.h>

#include <memory>
#include <wx/app.h>

#include "gui/MytbtiffcutUI.h"
#include "utils.h"
#include "tbtiffcut.h"

const char *const utils::SourceDir = "SourceDir";
const char *const utils::OutputDir = "OutputDir";
const char *const utils::TileDim = "TileDimension";
const char *const utils::ColDep = "ColorDepth";
const char *const utils::BuildTAR = "BuildTAR";

wxIMPLEMENT_APP(tbtiffcutApp);
/*
 *--------------------------------------------------------------------------------------
 *       Class: tbtiffcutApp
 *      Method: OnInit
 * Description: Init Application
 *--------------------------------------------------------------------------------------
 */
bool tbtiffcutApp::OnInit()
{
	wxFileName prog(wxGetApp().argv[0]);

	wxSetEnv("PROJ_LIB", prog.GetPath());  // path for gdal proj.db


	wxInitAllImageHandlers();
	initLanguageSupport();

	if ( !wxApp::OnInit() )
		return false;

	frame = new MyTbtiffcutUI();

	frame->Show(true);
	frame->Refresh();
	frame->Update();

	return true;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: tbtiffcutApp
 *      Method: initLanguageSupport
 * Description:
 *--------------------------------------------------------------------------------------
 */
void tbtiffcutApp::initLanguageSupport()
{
	auto lang = wxLocale::GetSystemLanguage();

	if ( lang != wxLANGUAGE_UNKNOWN && wxLocale::IsAvailable(lang) )
	{
//		wxLog::AddTraceMask(wxS("i18n"));
		locale = std::make_unique<wxLocale>(lang);
		wxLocale::AddCatalogLookupPathPrefix(".");
		auto ok = locale->AddCatalog("tbtiffcut");

		if ( !ok )
		{
			wxLogError("Language catalog could not be loaded!");
			locale.release();
			return;
		}

		if ( !locale->IsOk() )
		{
			wxLogError("Selected language is wrong!");
			locale.release();
			return;
		}
	}
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: tbtiffcutApp
 *      Method: OnExit
 * Description: exit application
 *--------------------------------------------------------------------------------------
 */
int tbtiffcutApp::OnExit()
{

	return 0;
}

