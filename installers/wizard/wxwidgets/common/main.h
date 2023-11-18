/***************************************************************
 * Name:      [FILENAME_PREFIX]Main.h
 * Purpose:   Defines Application Frame
 * Author:    [AUTHOR_NAME] ([AUTHOR_EMAIL])
 * Created:   [NOW]
 * Copyright: [AUTHOR_NAME] ([AUTHOR_WWW])
 * License:
 **************************************************************/

#ifndef [PROJECT_HDR]MAIN_H
#define [PROJECT_HDR]MAIN_H

[IF NONE]#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif[ENDIF NONE]

#include "[FILENAME_PREFIX]App.h"

[IF WXFRAME][IF NONE]class [CLASS_PREFIX]Frame: public wxFrame
{
    public:
        [CLASS_PREFIX]Frame(wxFrame *frame, const wxString& title);
        ~[CLASS_PREFIX]Frame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};[ENDIF NONE]
[IF WXFB]#include "GUIFrame.h"

class [CLASS_PREFIX]Frame: public GUIFrame
{
    public:
        [CLASS_PREFIX]Frame(wxFrame *frame);
        ~[CLASS_PREFIX]Frame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};[ENDIF WXFB][ENDIF WXFRAME]
[IF WXDIALOG][IF NONE]#include <wx/button.h>
#include <wx/statline.h>
class [CLASS_PREFIX]Dialog: public wxDialog
{
    public:
        [CLASS_PREFIX]Dialog(wxDialog *dlg, const wxString& title);
        ~[CLASS_PREFIX]Dialog();

    protected:
        enum
        {
            idBtnQuit = 1000,
            idBtnAbout
        };
        wxStaticText* m_staticText1;
        wxButton* BtnAbout;
        wxStaticLine* m_staticline1;
        wxButton* BtnQuit;

    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};[ENDIF NONE]
[IF WXFB]#include "GUIDialog.h"

class [CLASS_PREFIX]Dialog: public GUIDialog
{
    public:
        [CLASS_PREFIX]Dialog(wxDialog *dlg);
        ~[CLASS_PREFIX]Dialog();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};[ENDIF WXFB][ENDIF WXDIALOG]
#endif // [PROJECT_HDR]MAIN_H
