///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIDialog__
#define __GUIDialog__

// Define WX_GCH in order to support precompiled headers with GCC compiler.
// You have to create the header "wx_pch.h" and include all files needed
// for compile your gui inside it.
// Then, compile it and place the file "wx_pch.h.gch" into the same
// directory that "wx_pch.h".
#ifdef WX_GCH
#include <wx_pch.h>
#else
#include <wx/wx.h>
#endif

#include <wx/button.h>
#include <wx/statline.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialog
///////////////////////////////////////////////////////////////////////////////
class GUIDialog : public wxDialog 
{
    DECLARE_EVENT_TABLE()
    private:
        
        // Private event handlers
        void _wxFB_OnClose( wxCloseEvent& event ){ OnClose( event ); }
        void _wxFB_OnAbout( wxCommandEvent& event ){ OnAbout( event ); }
        void _wxFB_OnQuit( wxCommandEvent& event ){ OnQuit( event ); }
        
    
    protected:
        enum
        {
            idBtnAbout = 1000,
            idBtnQuit,
        };
        
        wxStaticText* m_staticText1;
        wxButton* BtnAbout;
        wxStaticLine* m_staticline1;
        wxButton* BtnQuit;
        
        // Virtual event handlers, overide them in your derived class
        virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
        virtual void OnAbout( wxCommandEvent& event ){ event.Skip(); }
        virtual void OnQuit( wxCommandEvent& event ){ event.Skip(); }
        
    
    public:
        GUIDialog( wxWindow* parent, int id = wxID_ANY, wxString title = wxT("wxWidgets Application Template"), wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, int style = wxDEFAULT_DIALOG_STYLE );
    
};

#endif //__GUIDialog__
