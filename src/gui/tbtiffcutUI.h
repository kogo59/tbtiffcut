///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Nov 14 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class tbtiffcutFrame
///////////////////////////////////////////////////////////////////////////////
class tbtiffcutFrame : public wxFrame
{
	private:
		wxBoxSizer* bSizer1;

	protected:
		wxMenuBar* tbtiffcutMenuBar;
		wxMenu* FileMenu;
		wxMenu* HelpMenu;
		wxPanel* m_panel1;
		wxStaticText* m_staticText1;
		wxFilePickerCtrl* tiffFilePicker;
		wxStaticText* m_staticText2;
		wxDirPickerCtrl* outputDirPicker;
		wxStaticText* m_staticText3;
		wxChoice* pixelChoice;
		wxStaticText* m_staticText4;
		wxRadioBox* radioBoxTileDim;
		wxCheckBox* tar_CheckBox;
		wxButton* okButton;
		wxButton* cancelButton;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnExitApp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSourceChanged( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void OnOutputDirChanged( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void OnChoiceBP( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileDimension( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTARCheckbox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		tbtiffcutFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("tbtiffcut"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~tbtiffcutFrame();

};

