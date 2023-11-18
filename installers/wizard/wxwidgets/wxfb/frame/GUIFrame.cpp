///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE( GUIFrame, wxFrame )
    EVT_CLOSE( GUIFrame::_wxFB_OnClose )
    EVT_MENU( idMenuQuit, GUIFrame::_wxFB_OnQuit )
    EVT_MENU( idMenuAbout, GUIFrame::_wxFB_OnAbout )
END_EVENT_TABLE()

GUIFrame::GUIFrame( wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style ) : wxFrame( parent, id, title, pos, size, style )
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    
    mbar = new wxMenuBar( 0 );
    wxMenu* fileMenu;
    fileMenu = new wxMenu();
    wxMenuItem* menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
    fileMenu->Append( menuFileQuit );
    mbar->Append( fileMenu, wxT("&File") );
    wxMenu* helpMenu;
    helpMenu = new wxMenu();
    wxMenuItem* menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
    helpMenu->Append( menuHelpAbout );
    mbar->Append( helpMenu, wxT("&Help") );
    this->SetMenuBar( mbar );
    
    statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
}
