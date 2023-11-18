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

[IF WXFRAME]//(*Headers([CLASS_PREFIX]Frame)
//*)

class [CLASS_PREFIX]Frame: public wxFrame
{
    public:

        [CLASS_PREFIX]Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~[CLASS_PREFIX]Frame();

    private:

        //(*Handlers([CLASS_PREFIX]Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers([CLASS_PREFIX]Frame)
        //*)

        //(*Declarations([CLASS_PREFIX]Frame)
        //*)

        DECLARE_EVENT_TABLE()
};[ENDIF WXFRAME][IF WXDIALOG]//(*Headers([CLASS_PREFIX]Dialog)
//*)

class [CLASS_PREFIX]Dialog: public wxDialog
{
    public:

        [CLASS_PREFIX]Dialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~[CLASS_PREFIX]Dialog();

    private:

        //(*Handlers([CLASS_PREFIX]Dialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers([CLASS_PREFIX]Dialog)

        //*)

        //(*Declarations([CLASS_PREFIX]Dialog)

        //*)

        DECLARE_EVENT_TABLE()
};[ENDIF WXDIALOG]

#endif // [PROJECT_HDR]MAIN_H
