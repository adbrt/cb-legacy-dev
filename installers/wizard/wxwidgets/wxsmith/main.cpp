/***************************************************************
 * Name:      [FILENAME_PREFIX]Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    [AUTHOR_NAME] ([AUTHOR_EMAIL])
 * Created:   [NOW]
 * Copyright: [AUTHOR_NAME] ([AUTHOR_WWW])
 * License:
 **************************************************************/

[PCH_INCLUDE]#include "[FILENAME_PREFIX]Main.h"
#include <wx/msgdlg.h>

//(*InternalHeaders([CLASS_PREFIX][IF WXFRAME]Frame[ENDIF WXFRAME][IF WXDIALOG]Dialog[ENDIF WXDIALOG])
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

[IF WXFRAME]//(*IdInit([CLASS_PREFIX]Frame)
//*)

BEGIN_EVENT_TABLE([CLASS_PREFIX]Frame,wxFrame)
    //(*EventTable([CLASS_PREFIX]Frame)
    //*)
END_EVENT_TABLE()

[CLASS_PREFIX]Frame::[CLASS_PREFIX]Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize([CLASS_PREFIX]Frame)
    //*)
}

[CLASS_PREFIX]Frame::~[CLASS_PREFIX]Frame()
{
    //(*Destroy([CLASS_PREFIX]Frame)
    //*)
}

void [CLASS_PREFIX]Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void [CLASS_PREFIX]Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}[ENDIF WXFRAME][IF WXDIALOG]//(*IdInit([CLASS_PREFIX]Dialog)
//*)

BEGIN_EVENT_TABLE([CLASS_PREFIX]Dialog,wxDialog)
    //(*EventTable([CLASS_PREFIX]Dialog)
    //*)
END_EVENT_TABLE()

[CLASS_PREFIX]Dialog::[CLASS_PREFIX]Dialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize([CLASS_PREFIX]Dialog)
    //*)
}

[CLASS_PREFIX]Dialog::~[CLASS_PREFIX]Dialog()
{
    //(*Destroy([CLASS_PREFIX]Dialog)
    //*)
}

void [CLASS_PREFIX]Dialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void [CLASS_PREFIX]Dialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}[ENDIF WXDIALOG]
