///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Nov 14 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "tbtiffcutUI.h"

///////////////////////////////////////////////////////////////////////////

tbtiffcutFrame::tbtiffcutFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	tbtiffcutMenuBar = new wxMenuBar( 0 );
	FileMenu = new wxMenu();
	wxMenuItem* ExitMenuItem;
	ExitMenuItem = new wxMenuItem( FileMenu, wxID_ANY, wxString( _("&Exit") ) , wxEmptyString, wxITEM_NORMAL );
	FileMenu->Append( ExitMenuItem );

	tbtiffcutMenuBar->Append( FileMenu, _("&File") );

	HelpMenu = new wxMenu();
	wxMenuItem* AboutMenuItem;
	AboutMenuItem = new wxMenuItem( HelpMenu, wxID_ANY, wxString( _("About") ) , wxEmptyString, wxITEM_NORMAL );
	HelpMenu->Append( AboutMenuItem );

	tbtiffcutMenuBar->Append( HelpMenu, _("&Help") );

	this->SetMenuBar( tbtiffcutMenuBar );

	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	m_panel1->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_panel1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, _("Source-Bitmap (tiff):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_staticText1->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	m_staticText1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	fgSizer1->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );

	tiffFilePicker = new wxFilePickerCtrl( m_panel1, wxID_ANY, wxEmptyString, _("Select a file"), _("tif|*.tif|tiff|*.tiff|*.*|*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_SMALL );
	fgSizer1->Add( tiffFilePicker, 0, wxALL|wxEXPAND, 5 );

	m_staticText2 = new wxStaticText( m_panel1, wxID_ANY, _("Output Path:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	fgSizer1->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );

	outputDirPicker = new wxDirPickerCtrl( m_panel1, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_SMALL );
	fgSizer1->Add( outputDirPicker, 0, wxALL|wxEXPAND, 5 );


	bSizer2->Add( fgSizer1, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 5, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText3 = new wxStaticText( m_panel1, wxID_ANY, _("Color depth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	fgSizer2->Add( m_staticText3, 1, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );

	wxString pixelChoiceChoices[] = { _("8"), _("32") };
	int pixelChoiceNChoices = sizeof( pixelChoiceChoices ) / sizeof( wxString );
	pixelChoice = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, pixelChoiceNChoices, pixelChoiceChoices, 0 );
	pixelChoice->SetSelection( 0 );
	fgSizer2->Add( pixelChoice, 1, wxALIGN_CENTER_VERTICAL|wxLEFT, 15 );

	m_staticText4 = new wxStaticText( m_panel1, wxID_ANY, _("bits/pixel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	fgSizer2->Add( m_staticText4, 5, wxALIGN_CENTER_VERTICAL|wxALL|wxLEFT, 15 );

	wxString radioBoxTileDimChoices[] = { _("256 x 256"), _("512 x 512"), _("768 x 768"), _("1024 x 1024") };
	int radioBoxTileDimNChoices = sizeof( radioBoxTileDimChoices ) / sizeof( wxString );
	radioBoxTileDim = new wxRadioBox( m_panel1, wxID_ANY, _("Tile dimensions"), wxDefaultPosition, wxDefaultSize, radioBoxTileDimNChoices, radioBoxTileDimChoices, 2, wxRA_SPECIFY_COLS );
	radioBoxTileDim->SetSelection( 0 );
	radioBoxTileDim->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	radioBoxTileDim->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	fgSizer2->Add( radioBoxTileDim, 1, wxALIGN_RIGHT|wxEXPAND|wxRIGHT, 10 );

	tar_CheckBox = new wxCheckBox( m_panel1, wxID_ANY, _("  Build TAR file"), wxDefaultPosition, wxDefaultSize, 0 );
	tar_CheckBox->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	fgSizer2->Add( tar_CheckBox, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer2->Add( fgSizer2, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	okButton = new wxButton( m_panel1, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( okButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cancelButton = new wxButton( m_panel1, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer2->Add( bSizer6, 1, wxALIGN_RIGHT|wxALL, 5 );


	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( tbtiffcutFrame::OnClose ) );
	FileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( tbtiffcutFrame::OnExitApp ), this, ExitMenuItem->GetId());
	HelpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( tbtiffcutFrame::OnAbout ), this, AboutMenuItem->GetId());
	tiffFilePicker->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( tbtiffcutFrame::OnSourceChanged ), NULL, this );
	outputDirPicker->Connect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( tbtiffcutFrame::OnOutputDirChanged ), NULL, this );
	pixelChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( tbtiffcutFrame::OnChoiceBP ), NULL, this );
	radioBoxTileDim->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( tbtiffcutFrame::OnTileDimension ), NULL, this );
	tar_CheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tbtiffcutFrame::OnTARCheckbox ), NULL, this );
	okButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tbtiffcutFrame::OnOk ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tbtiffcutFrame::OnCancel ), NULL, this );
}

tbtiffcutFrame::~tbtiffcutFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( tbtiffcutFrame::OnClose ) );
	tiffFilePicker->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( tbtiffcutFrame::OnSourceChanged ), NULL, this );
	outputDirPicker->Disconnect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( tbtiffcutFrame::OnOutputDirChanged ), NULL, this );
	pixelChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( tbtiffcutFrame::OnChoiceBP ), NULL, this );
	radioBoxTileDim->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( tbtiffcutFrame::OnTileDimension ), NULL, this );
	tar_CheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( tbtiffcutFrame::OnTARCheckbox ), NULL, this );
	okButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tbtiffcutFrame::OnOk ), NULL, this );
	cancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( tbtiffcutFrame::OnCancel ), NULL, this );

}
