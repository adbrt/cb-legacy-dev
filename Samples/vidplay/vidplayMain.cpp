/***************************************************************
 * Name:      vidplayMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2023-11-12
 * Copyright:  ()
 * License:
 ******************************************Œ********************/

#include "vidplayMain.h"
#include <wx/msgdlg.h>
//#include <commdlg.h>

//(*InternalHeaders(vidplayFrame)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

#include <wx/version.h>
#include <wx/filedlg.h>

// Load additional backend for newer wx versions
#if wxCHECK_VERSION(3, 0, 0)
    #if defined(__WXMSW__) && !defined(WXUSINGDLL)
        #include "wx/link.h"
        wxFORCE_LINK_MODULE(wxmediabackend_am)
    #endif // static wxMSW build
#endif


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


const long vidplayFrame::ID_MEDIACTRL1 = wxNewId();

//(*IdInit(vidplayFrame)
const long vidplayFrame::ID_PANEL2 = wxNewId();
const long vidplayFrame::ID_BUTTON1 = wxNewId();
const long vidplayFrame::ID_STATICTEXT1 = wxNewId();
const long vidplayFrame::ID_TEXTCTRL1 = wxNewId();
const long vidplayFrame::ID_BUTTON3 = wxNewId();
const long vidplayFrame::ID_BUTTON2 = wxNewId();
const long vidplayFrame::ID_PANEL1 = wxNewId();
const long vidplayFrame::ID_SLIDER1 = wxNewId();
const long vidplayFrame::ID_PANEL3 = wxNewId();
const long vidplayFrame::ID_PANEL4 = wxNewId();
const long vidplayFrame::ID_TIMER1 = wxNewId();
const long vidplayFrame::ID_TIMER2 = wxNewId();
//*)


BEGIN_EVENT_TABLE(vidplayFrame,wxFrame)
    //(*EventTable(vidplayFrame)
    //*)
END_EVENT_TABLE()

wxString wxItoa(int number)
{

}

vidplayFrame::vidplayFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(vidplayFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;

    Create(parent, wxID_ANY, _("Video player"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxFULL_REPAINT_ON_RESIZE, _T("wxID_ANY"));
    SetMinSize(wxSize(-1,250));
    SetBackgroundColour(wxColour(0,0,0));
    // This code will set a smaller font if Win 3.11 is detected:
    int majorVer; int minorVer;
    wxGetOsVersion(&majorVer, &minorVer);
    if (minorVer == 30 || majorVer == 30 || majorVer == 3)
    {
        wxFont thisFont(8,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
        SetFont(thisFont);
    }
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer5 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4->Add(BoxSizer5, 1, wxALL|wxEXPAND, 0);
    Placeholder = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxSize(10,156), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Placeholder->SetMaxSize(wxSize(-1,-1));
    Placeholder->Hide();
    Placeholder->SetBackgroundColour(wxColour(0,0,0));
    BoxSizer4->Add(Placeholder, 0, wxALL, 0);
    BoxSizer3->Add(BoxSizer4, 1, wxALL|wxEXPAND, 1);
    BoxSizer6 = new wxBoxSizer(wxVERTICAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(406,77), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Play"), wxPoint(8,8), wxSize(72,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Time"), wxPoint(8,48), wxSize(184,24), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT1"));
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("video.avi"), wxPoint(224,8), wxSize(173,32), wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Button3 = new wxButton(Panel1, ID_BUTTON3, _("Load"), wxPoint(160,8), wxSize(56,32), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button2 = new wxButton(Panel1, ID_BUTTON2, _("Pause"), wxPoint(88,8), wxSize(64,32), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer6->Add(Panel1, 0, wxEXPAND|wxFIXED_MINSIZE, 0);
    BoxSizer3->Add(BoxSizer6, 0, wxALL|wxEXPAND, 0);
    Panel2 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxSize(362,24), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel2->SetMinSize(wxDLG_UNIT(this,wxSize(-1,16)));
    Panel2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    Slider1 = new wxSlider(Panel2, ID_SLIDER1, 0, 0, 200, wxDefaultPosition, wxDLG_UNIT(Panel2,wxSize(-1,10)), wxSL_BOTH|wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_SLIDER1"));
    BoxSizer7->Add(Slider1, 1, wxEXPAND, 0);
    Panel2->SetSizer(BoxSizer7);
    BoxSizer3->Add(Panel2, 0, wxALL|wxEXPAND, 0);
    BoxSizer8 = new wxBoxSizer(wxVERTICAL);
    Panel3 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxSize(362,16), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Panel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    BoxSizer8->Add(Panel3, 0, wxALL|wxEXPAND, 0);
    BoxSizer3->Add(BoxSizer8, 0, wxALL|wxEXPAND, 0);
    BoxSizer1->Add(BoxSizer3, 2, wxALL|wxEXPAND, 0);
    SetSizer(BoxSizer1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(66, false);
    Timer2.SetOwner(this, ID_TIMER2);
    Fit();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&vidplayFrame::OnButton1Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&vidplayFrame::OnButton3Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&vidplayFrame::OnButton2Click);
    Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&vidplayFrame::OnSlider1CmdSliderUpdated);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&vidplayFrame::OnTimer1Trigger);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&vidplayFrame::OnTimer2Trigger);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&vidplayFrame::OnResize);
    //*)


    // Create a media player control and load media backend.
    // Note: it uses wxMEDIABACKEND_MCI, which is considered to be obsolete,
    // but that's the only thing that also works under Win 3.11

    // wxMEDIABACKEND_MCI currently will work only with wx 2.8

    m_mediactrl = new wxMediaCtrl();

    wxString mediaBackend = wxMEDIABACKEND_MCI;

    // Use direct show backend on newer wx versions, because MCI wouldn't work
    #if wxCHECK_VERSION(3, 0, 0)
        mediaBackend = wxMEDIABACKEND_DIRECTSHOW;
    #endif // wxCHECK_VERSION

    bool bOK = m_mediactrl->Create(this, ID_MEDIACTRL1, wxEmptyString, wxDefaultPosition, wxSize(320,240), NULL, mediaBackend );

    Connect(ID_MEDIACTRL1, wxEVT_MEDIA_LOADED, wxMediaEventHandler(vidplayFrame::OnMediaLoaded));

    VideoSizer = BoxSizer5;

    VideoSizer->Add(m_mediactrl, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND|wxSHAPED, 0);

    if (m_mediactrl) m_mediactrl->Load(TextCtrl1->GetValue());

    if (!bOK) wxMessageBox("Could not load media backend");


}

vidplayFrame::~vidplayFrame()
{
    //(*Destroy(vidplayFrame)
    //*)
}

void vidplayFrame::OnMediaLoaded(wxMediaEvent& WXUNUSED(evt))
{
    // This will determine the proper size
    wxSize vidsize = m_mediactrl->GetBestSize();
    wxString sizeStr;

    sizeStr << vidsize.GetWidth();

    VideoSizer->GetItem(m_mediactrl)->SetRatio(vidsize.GetWidth(), vidsize.GetHeight());
}


void vidplayFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void vidplayFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void vidplayFrame::OnButton1Click(wxCommandEvent& event)
{
    m_mediactrl->Play();
}

void vidplayFrame::OnSlider1CmdSliderUpdated(wxScrollEvent& event)
{
    if (m_mediactrl)
    {
        long newOffset = 0;
        long maxVal = Slider1->GetMax();
        long mediaLength = m_mediactrl->Length();
        long sliderVal = Slider1->GetValue();
        if (sliderVal > 0)
        {
            newOffset = (mediaLength) * (float(sliderVal)/maxVal);
        }
        else newOffset = 0;

        m_mediactrl->Seek(newOffset);

        wxString progressStr;
        progressStr << newOffset;
    }
}

void vidplayFrame::OnButton2Click(wxCommandEvent& event)
{
    if (m_mediactrl) m_mediactrl->Pause();
}

void vidplayFrame::OnTimer1Trigger(wxTimerEvent& event)
{
    if (m_mediactrl)
    {
        long maxVal = Slider1->GetMax();
        long mediaPos = m_mediactrl->Tell();
        long mediaLength = m_mediactrl->Length();

        if (mediaLength > 0 && (m_mediactrl->GetState() == wxMEDIASTATE_PLAYING) )
        {
            int newSliderVal = (float(mediaPos)/mediaLength)*maxVal;
            Slider1->SetValue(newSliderVal);
        }

        int minutes = (mediaPos/1000)/60;
        int hours = minutes/60;
        int seconds = (mediaPos/1000);
        int milliseconds = mediaPos - (seconds*1000);

        wxString durationString = wxString::Format(("%02d:%02d:%02d,%02d"),hours,minutes,seconds,milliseconds);

        StaticText1->SetLabel(durationString);
    }
}

void vidplayFrame::OnResize(wxSizeEvent& event)
{
    // This will check one time after 100 milliseconds if the player window is correct size
    // May look like a hack, but works rather well
    Timer2.Start(100, true);

    // Skip means process the rest of events normally
    event.Skip();
}

void vidplayFrame::OnTimer2Trigger(wxTimerEvent& event)
{
    if (m_mediactrl)
    {
        VideoSizer->Fit(m_mediactrl);
        Layout();
    }
}

void vidplayFrame::OnButton3Click(wxCommandEvent& event)
{

    // This button is used to open a file browser
    // and load a media file. This is one of the trickier
    // examples when we want to have Win 3.11 compatibility.

    // This code will check if Win 3.11 is running:
    int majorVer; int minorVer;
    wxGetOsVersion(&majorVer, &minorVer);
    if (minorVer == 30 || majorVer == 30 || majorVer == 3)
    {
        // Would not compile in unicode
        #ifndef wxUSE_UNICODE
        // The following code is only for Win 3.11,
        // it invokes legacy file browser
        typedef BOOL WINAPI (*GetOpenFileName_f)( LPOPENFILENAME ofn );
        GetOpenFileName_f func_GetOpenFileName;

        static char achFileName[128];
        static char szAppFilter[]="Media files\0*.avi;*.mpg;*.mp4;*.ts\0";
        OPENFILENAME ofn;

        HWND hwnd = (HWND)this->GetHWND();

            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hwnd;
            ofn.hInstance = NULL;
            ofn.lpstrFilter = szAppFilter;
            ofn.lpstrCustomFilter = NULL;
            ofn.nMaxCustFilter = 0;
            ofn.nFilterIndex = 0;
            ofn.lpstrFile = achFileName;
            ofn.nMaxFile = sizeof(achFileName);
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.lpstrTitle = NULL;
            ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
            ofn.nFileOffset = 0;
            ofn.nFileExtension = 0;
            ofn.lpstrDefExt = NULL;
            ofn.lCustData = 0;
            ofn.lpfnHook = NULL;
            ofn.lpTemplateName = NULL;

        if(GetOpenFileNameA(&ofn))
        {
            TextCtrl1->SetValue( ofn.lpstrFile );
        }
        if (m_mediactrl) m_mediactrl->Load(TextCtrl1->GetValue());
        #endif // wxUSE_UNICODE
    }

    else // if Win 3.11 is NOT detected, then it is really easy:
    {
        // This will work if we are using Win 95 or anything newer
        wxFileDialog* FileDialog1 = new wxFileDialog(this, _("Select file"),
                                    wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr,
                                    wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

        bool dialog = FileDialog1->ShowModal();
        if (dialog) TextCtrl1->SetValue(FileDialog1->GetFilename());
        if (m_mediactrl) m_mediactrl->Load(TextCtrl1->GetValue());

        FileDialog1->Destroy();
    }
}
