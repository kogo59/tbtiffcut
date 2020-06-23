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
 * MytbtiffcutUI.cpp
 *
 *  Created on: 24.02.2020
 *      Author: kogo
 */

#include <wx/aboutdlg.h>
#include <wx/fileconf.h>
#include <wx/msgdlg.h>
#include <wx/colour.h>
#include <wx/dir.h>

#include "tbtiffcut_config.h"
#include "MytbtiffcutUI.h"
#include "../Preferences.h"
#include "../OziMap.h"

class WorkingDirErr: public std::exception
{
		virtual const char* what() const throw ( )
		{
			return _("Setting output directory failed.");
		}
} WorkingDirError;

class RemoveTile_Err: public std::exception
{
		virtual const char* what() const throw ( )
		{
			return _("Could not remove existing tile.");
		}
} RemoveTileError;

class MkDir_Err: public std::exception
{
		virtual const char* what() const throw ( )
		{
			return _("Could not create set directory.");
		}
} MkDirError;

class RemoveSetDir_Err: public std::exception
{
		virtual const char* what() const throw ( )
		{
			return _("Could not remove set directory.");
		}
} RemoveSetDirError;

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: MyTbtiffcutUI
 * Description: constructor
 *--------------------------------------------------------------------------------------
 */
MyTbtiffcutUI::MyTbtiffcutUI() :
		tbtiffcutFrame(nullptr)
{
	p_pref = std::make_unique<Preferences>();

	tiffFilePicker->SetInitialDirectory(
			wxFileName(p_pref->getSourceDir()).GetPath());
	outputDirPicker->SetInitialDirectory(p_pref->getOutputDir());
	radioBoxTileDim->SetSelection(p_pref->getTileDim());
	tar_CheckBox->SetValue(p_pref->getBuildTAR());

	int sel = 0;
	int bp = p_pref->getColDep();
	if ( bp == bp32 )
		sel = 1;

	pixelChoice->SetSelection(sel);

	SetIcon(wxICON(tbtiffcut_ico));
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: MyTbtiffcutUI
 * Description: destructor
 *--------------------------------------------------------------------------------------
 */
MyTbtiffcutUI::~MyTbtiffcutUI()
{
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnClose
 * Description: Quit App
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnClose( wxCloseEvent &event )
{
	event.Skip();
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnExitApp
 * Description: Handle Exit Menu
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnExitApp( wxCommandEvent &event )
{
	Close(true);
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnCancel
 * Description: Handle Cancel Button
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnCancel( wxCommandEvent &event )
{
	Close(true);

}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: ShowExMsg
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::ShowExMsg( std::exception &ex )
{
	auto m = wxMessageDialog(this, ex.what(), _("Error"),
	wxOK | wxCENTRE | wxICON_ERROR);
	m.ShowModal();
	wxSetCursor(wxNullCursor);
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: WriteOziMapFile
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::WriteOziMapFile( const wxFileName &fnam,
		const wxFileName &output )
{

	try
	{

		OziMap OziMapFile(fnam);

		wxString mapfile = output.GetFullPath() + fnam.GetName() + ".map";

		file_list.emplace_back(utils::rep_underline(mapfile));

		OziMapFile.WriteMapFile(mapfile);

	} catch ( std::exception &ex )
	{
		ShowExMsg(ex);
		throw;
	}

}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: CleanSet
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::CleanSet( const wxFileName &output )
{
	auto fnam = utils::rep_underline(tiffFilePicker->GetFileName().GetName());

	auto set_file = output.GetFullPath() + fnam.GetName() + ".set";
	auto map_file = output.GetFullPath() + fnam.GetName() + ".map";

	auto set_dir = output.GetFullPath() + "set";

	if ( wxDirExists(set_dir) )
	{
		wxDir dir(set_dir);
		if ( !wxSetWorkingDirectory(set_dir) )
			throw WorkingDirError;

		wxString filename;
		bool cont = dir.GetFirst(&filename, "*.*", wxDIR_FILES);

		while ( cont )
		{
			if ( !wxRemoveFile(filename) )
				throw RemoveTileError;

			cont = dir.GetNext(&filename);
		}

		wxSetWorkingDirectory(output.GetFullPath());

		if ( !wxRmdir(set_dir) )
			throw RemoveSetDirError;
	}

	if ( wxFileExists(set_file) )
		wxRemoveFile(set_file);

	if ( wxFileExists(map_file) )
		wxRemoveFile(map_file);

}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: PrepareSet
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::PrepareSet( const wxFileName &output )
{
	auto set_dir = output.GetFullPath() + "set";

	if ( wxDirExists(set_dir) )
	{
		try
		{
			CleanSet(output);
		} catch ( std::exception &ex )
		{
			throw;
		}
	}
	if ( !wxMkdir(set_dir) )
		throw MkDirError;

}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: BuildTiles
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::BuildTiles( const wxFileName &fnam,
		const wxFileName &output, wxProgressDialog &dlg )
{

	auto set_file = output.GetFullPath() + fnam.GetName() + ".set";

	file_list.emplace_back(utils::rep_underline(set_file));

	int ts = TileSize[p_pref->getTileDim()];

	auto pngFac = std::make_unique<pngTileFactory>(fnam, ts, p_pref->getColDep());

	auto numTiles = pngFac->getX_Tiles() * pngFac->getY_Tiles();

	dlg.SetRange(numTiles + 15);

	int i = 10;
	auto msg = _("Generating tiles.");

	auto png = pngFac->makeTile(true);
	while ( png != nullptr )
	{
		dlg.Update(i, msg);
		wxSetCursor(wxCursor(wxCURSOR_WAIT));
		png->writeTile(output, ts, file_list);
		png = pngFac->makeTile();
		++i;
	}
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: BuildTiles
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::DoJob( const wxFileName &fnam, const wxFileName &output )
{

	const int PROGRESS_COUNT = 100;
	wxProgressDialog dlg(_("Building"), "Preparing", PROGRESS_COUNT, this,
	wxPD_SMOOTH | wxPD_APP_MODAL | wxPD_AUTO_HIDE);

	try
	{
		PrepareSet(output);
	} catch ( std::exception &ex )
	{
		ShowExMsg(ex);
		return;
	}

	wxString msg = _("Writing map file.");
	dlg.Update(1, msg);

	try
	{
		WriteOziMapFile(fnam, output);
	} catch ( ... )
	{
		return;
	}

	dlg.Update(2, msg);
	BuildTiles(fnam, output, dlg);

	if ( p_pref->getBuildTAR() )
	{
		wxSetCursor(wxCursor(wxCURSOR_WAIT));
		msg = _("Generating tar file.");
		dlg.Update(dlg.GetRange() - 5, msg);
		auto tarf = utils::rep_underline(
				output.GetFullPath() + fnam.GetName() + ".tar");
		MakeTar(tarf);
		CleanSet(output);
	}

	msg = _("Finished.");
	dlg.Update(dlg.GetRange(), msg);
	wxMilliSleep(50);

}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnOk
 * Description: Handle Ok Button
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnOk( wxCommandEvent &event )
{

	wxSetCursor(wxCursor(wxCURSOR_WAIT));

	SavPref();

	file_list.clear();

	auto fnam = tiffFilePicker->GetFileName();

	auto output = outputDirPicker->GetDirName();

	if ( ErrorCheck(fnam, _("Source-Bitmap missing or not accessible."))
			|| ErrorCheck(output, _("Output-Path missing or not accessible.")) )
		return;

	DoJob(fnam, output);

	wxSetCursor(wxNullCursor);
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: MakeTar
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::MakeTar( const wxFileName &tar_archive )
{

	auto tarClassFactory = wxTarClassFactory();

	wxTempFileOutputStream fileOutputStream(tar_archive.GetFullPath());

	wxScopedPtr<wxArchiveOutputStream> archiveOutputStream(
			tarClassFactory.NewStream(fileOutputStream));

	for ( auto &&file : file_list )
	{
		wxFileInputStream inputFileStream(file.GetFullPath());

		auto f =
				file.GetExt() == "png" ?
						"set/" + file.GetFullName() : file.GetFullName();

		archiveOutputStream->PutNextEntry(f, wxDateTime::Now(),
				inputFileStream.GetLength());
		CopyStreamData(inputFileStream, *archiveOutputStream,
				inputFileStream.GetLength());
	}

	archiveOutputStream->Close();

	fileOutputStream.Commit();
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: MakeTar
 * Description:
 *--------------------------------------------------------------------------------------
 */
bool MyTbtiffcutUI::CopyStreamData( wxInputStream &inputStream,
		wxOutputStream &outputStream, wxFileOffset size )
{
	wxChar buf[256 * 1024];
	int readSize = 256 * 1024;
	wxFileOffset copiedData = 0;
	for ( ; ; )
	{
		if ( size != -1 && copiedData + readSize > size )
			readSize = size - copiedData;
		inputStream.Read(buf, readSize);

		size_t actuallyRead = inputStream.LastRead();
		outputStream.Write(buf, actuallyRead);
		if ( outputStream.LastWrite() != actuallyRead )
		{
			wxLogError
			("Failed to output data");
			return false;
		}

		if ( size == -1 )
		{
			if ( inputStream.Eof() )
				break;
		}
		else
		{
			copiedData += actuallyRead;
			if ( copiedData >= size )
				break;
		}
	}

	return true;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: ErrorCheck
 * Description:
 *--------------------------------------------------------------------------------------
 */
bool MyTbtiffcutUI::ErrorCheck( const wxFileName &fn, const wxString &msg )
{
	if ( !fn.IsOk() || !fn.DirExists() )
	{
		auto m = wxMessageDialog(this, msg, _("Error"),
		wxOK | wxCENTRE | wxICON_ERROR);
		m.ShowModal();
		return true;
	}
	return false;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnAbout
 * Description: Handle About Menu
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnAbout( wxCommandEvent &event )
{
	wxAboutDialogInfo info;
	info.SetName("tbtiffcut");
	info.SetVersion(TC_VERSION);
	info.SetDescription(_("Generate tiles from geotiff images for trekbuddy."));
	info.SetCopyright("(C) 2020");
	info.SetLicence(wxString::FromAscii(TC_LICENSE));
	info.AddDeveloper("KoGo");
	wxAboutBox(info, this);

	event.Skip(false);
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnSourceChanged
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnSourceChanged( wxFileDirPickerEvent &event )
{
	p_pref->setSourceDir(event.GetPath());

}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnOutputDirChanged
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnOutputDirChanged( wxFileDirPickerEvent &event )
{
	p_pref->setOutputDir(event.GetPath());
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnTileDimension
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnTileDimension( wxCommandEvent &event )
{
	p_pref->setTileDim(static_cast<TileDimension>(event.GetInt()));
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnChoiceBP
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnChoiceBP( wxCommandEvent &event )
{
	auto bitspx = bp8;

	int bp = event.GetInt();

	if ( bp == 1 )
		bitspx = bp32;

	p_pref->setColDep(bitspx);
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: OnChoiceBP
 * Description:
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::OnTARCheckbox( wxCommandEvent &event )
{
	p_pref->setBuildTAR(event.GetInt());
}

/*
 *--------------------------------------------------------------------------------------
 *       Class: MyTbtiffcutUI
 *      Method: SavPref
 * Description: save preferences
 *--------------------------------------------------------------------------------------
 */
void MyTbtiffcutUI::SavPref()
{
	wxFileConfig config("", "", utils::make_ini_filename());

	config.Write(utils::SourceDir, p_pref->getSourceDir());
	config.Write(utils::OutputDir, p_pref->getOutputDir());
	config.Write(utils::TileDim, static_cast<int>(p_pref->getTileDim()));
	config.Write(utils::BuildTAR, p_pref->getBuildTAR());

	int sel = p_pref->getColDep() == bp8 ? 0 : 1;

	config.Write(utils::ColDep, sel);
}
