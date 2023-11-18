/***************************************************************
 * Name:      vidplayMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2023-11-12
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef VIDPLAYMAIN_H
#define VIDPLAYMAIN_H

//(*Headers(vidplayFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

#include <wx/mediactrl.h>

class vidplayFrame: public wxFrame
{
    public:

        vidplayFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~vidplayFrame();

    private:

        //(*Handlers(vidplayFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnSlider1CmdSliderUpdated(wxScrollEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnResize(wxSizeEvent& event);
        void OnTimer2Trigger(wxTimerEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(vidplayFrame)
        static const long ID_PANEL2;
        static const long ID_BUTTON1;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON3;
        static const long ID_BUTTON2;
        static const long ID_PANEL1;
        static const long ID_SLIDER1;
        static const long ID_PANEL3;
        static const long ID_PANEL4;
        static const long ID_TIMER1;
        static const long ID_TIMER2;
        //*)

        //(*Declarations(vidplayFrame)
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxPanel* Panel3;
        wxPanel* Placeholder;
        wxSlider* Slider1;
        wxStaticText* StaticText1;
        wxTextCtrl* TextCtrl1;
        wxTimer Timer1;
        wxTimer Timer2;
        //*)


        static const long ID_MEDIACTRL1;
        wxMediaCtrl* m_mediactrl;

        void OnMediaLoaded(wxMediaEvent& event);

        wxSizer * VideoSizer;

        DECLARE_EVENT_TABLE()
};

#endif // VIDPLAYMAIN_H
