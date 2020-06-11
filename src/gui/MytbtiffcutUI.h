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
 * MytbtiffcutUI.h
 *
 *  Created on: 24.02.2020
 *      Author: kogo
 */

#ifndef GUI_MYTBTIFFCUTUI_H_
#define GUI_MYTBTIFFCUTUI_H_

#include <memory>
#include <vector>
#include <tuple>
#include <wx/filename.h>
#include <wx/archive.h>
#include <wx/wfstream.h>
#include <wx/tarstrm.h>
#include <wx/progdlg.h>


#include "tbtiffcutUI.h"
#include "../Preferences.h"
#include "../tilesFactory.h"

/*
 * =====================================================================================
 *        Class: MyTbtiffcutUI
 *  Description: derived class for wxBuilder generated gui-class
 * =====================================================================================
 */
class MyTbtiffcutUI: public tbtiffcutFrame
{
	public:
		MyTbtiffcutUI();
		virtual ~MyTbtiffcutUI();

	protected:

		virtual void OnClose( wxCloseEvent &event );
		void OnExitApp( wxCommandEvent &event );
		void OnCancel( wxCommandEvent &event );
		void OnOk( wxCommandEvent &event );
		void OnAbout( wxCommandEvent &event );
		void OnSourceChanged( wxFileDirPickerEvent &event );
		void OnOutputDirChanged( wxFileDirPickerEvent &event );
		void OnTileDimension( wxCommandEvent &event );
		void OnChoiceBP( wxCommandEvent &event );
		void OnTARCheckbox( wxCommandEvent &event );

	private:
		std::unique_ptr<Preferences> p_pref = nullptr;
		std::vector<wxFileName> file_list;
		void SavPref();
		bool ErrorCheck( const wxFileName &fn, const wxString &msg );
		void WriteOziMapFile( const wxFileName &fnam, const wxFileName &output );
		void PrepareSet( const wxFileName &output );
		void ShowExMsg( std::exception &ex );
		void BuildTiles( const wxFileName &fnam, const wxFileName &output,
				wxProgressDialog &dlg );

		void OpenTar( const wxFileName &tar_archive );
		void MakeTar( const wxFileName &tar_archive );
		void CleanSet( const wxFileName &output );
		bool CopyStreamData( wxInputStream &inputStream,
				wxOutputStream &outputStream, wxFileOffset size );
		void DoJob( const wxFileName &fnam, const wxFileName &output );

};

#endif /* GUI_MYTBTIFFCUTUI_H_ */
