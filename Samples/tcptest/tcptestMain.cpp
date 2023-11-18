/***************************************************************
 * Name:      tcptestMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2023-11-10
 * Copyright:  ()
 * License:
 **************************************************************/

#include "tcptestMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(tcptestFrame)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
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

//(*IdInit(tcptestFrame)
const long tcptestFrame::ID_STATICTEXT3 = wxNewId();
const long tcptestFrame::ID_STATICTEXT4 = wxNewId();
const long tcptestFrame::ID_TEXTCTRL2 = wxNewId();
const long tcptestFrame::ID_BUTTON1 = wxNewId();
const long tcptestFrame::ID_BUTTON2 = wxNewId();
const long tcptestFrame::ID_PANEL5 = wxNewId();
const long tcptestFrame::ID_STATICTEXT1 = wxNewId();
const long tcptestFrame::ID_LISTBOX1 = wxNewId();
const long tcptestFrame::ID_BUTTON8 = wxNewId();
const long tcptestFrame::ID_PANEL6 = wxNewId();
const long tcptestFrame::ID_STATICTEXT2 = wxNewId();
const long tcptestFrame::ID_TEXTCTRL1 = wxNewId();
const long tcptestFrame::ID_PANEL7 = wxNewId();
const long tcptestFrame::ID_PANEL2 = wxNewId();
const long tcptestFrame::ID_TEXTCTRL3 = wxNewId();
const long tcptestFrame::ID_CHECKBOX1 = wxNewId();
const long tcptestFrame::ID_SPINCTRL1 = wxNewId();
const long tcptestFrame::ID_PANEL10 = wxNewId();
const long tcptestFrame::ID_PANEL8 = wxNewId();
const long tcptestFrame::ID_BUTTON3 = wxNewId();
const long tcptestFrame::ID_BUTTON4 = wxNewId();
const long tcptestFrame::ID_PANEL9 = wxNewId();
const long tcptestFrame::ID_PANEL4 = wxNewId();
const long tcptestFrame::ID_PANEL3 = wxNewId();
const long tcptestFrame::ID_STATICTEXT5 = wxNewId();
const long tcptestFrame::ID_TEXTCTRL7 = wxNewId();
const long tcptestFrame::ID_STATICTEXT6 = wxNewId();
const long tcptestFrame::ID_TEXTCTRL4 = wxNewId();
const long tcptestFrame::ID_BUTTON5 = wxNewId();
const long tcptestFrame::ID_BUTTON6 = wxNewId();
const long tcptestFrame::ID_PANEL14 = wxNewId();
const long tcptestFrame::ID_STATICTEXT8 = wxNewId();
const long tcptestFrame::ID_TEXTCTRL5 = wxNewId();
const long tcptestFrame::ID_PANEL16 = wxNewId();
const long tcptestFrame::ID_PANEL13 = wxNewId();
const long tcptestFrame::ID_TEXTCTRL6 = wxNewId();
const long tcptestFrame::ID_CHECKBOX2 = wxNewId();
const long tcptestFrame::ID_SPINCTRL2 = wxNewId();
const long tcptestFrame::ID_PANEL19 = wxNewId();
const long tcptestFrame::ID_PANEL18 = wxNewId();
const long tcptestFrame::ID_BUTTON7 = wxNewId();
const long tcptestFrame::ID_PANEL20 = wxNewId();
const long tcptestFrame::ID_PANEL17 = wxNewId();
const long tcptestFrame::ID_PANEL12 = wxNewId();
const long tcptestFrame::ID_NOTEBOOK1 = wxNewId();
const long tcptestFrame::ID_PANEL1 = wxNewId();
const long tcptestFrame::idMenuQuit = wxNewId();
const long tcptestFrame::idMenuAbout = wxNewId();
const long tcptestFrame::ID_STATUSBAR1 = wxNewId();
//*)


const long tcptestFrame::ID_TCPSERVER1 = wxNewId();
const long tcptestFrame::ID_TCPCLIENT1 = wxNewId();


BEGIN_EVENT_TABLE(tcptestFrame,wxFrame)
    //(*EventTable(tcptestFrame)
    //*)
END_EVENT_TABLE()

tcptestFrame::tcptestFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(tcptestFrame)
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer13;
    wxBoxSizer* BoxSizer14;
    wxBoxSizer* BoxSizer16;
    wxBoxSizer* BoxSizer17;
    wxBoxSizer* BoxSizer18;
    wxBoxSizer* BoxSizer19;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer20;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer9;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("TCP Client/Server"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxFULL_REPAINT_ON_RESIZE, _T("wxID_ANY"));
    SetMinSize(wxSize(340,320));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    // This code will set a smaller font if Win 3.11 is detected:
    int majorVer; int minorVer;
    wxGetOsVersion(&majorVer, &minorVer);
    if (minorVer == 30 || majorVer == 30 || majorVer == 3)
    {
        wxFont thisFont(8,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
        SetFont(thisFont);
    }
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(286,334), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    Notebook1 = new wxNotebook(Panel1, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    Panel2 = new wxPanel(Panel3, ID_PANEL2, wxDefaultPosition, wxSize(330,191), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    Panel5 = new wxPanel(Panel2, ID_PANEL5, wxDefaultPosition, wxDLG_UNIT(Panel2,wxSize(58,36)), wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    LabelCount1 = new wxStaticText(Panel5, ID_STATICTEXT3, _("Client count: 0"), wxDefaultPosition, wxDLG_UNIT(Panel5,wxSize(56,8)), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT3"));
    BoxSizer7->Add(LabelCount1, 0, wxALIGN_LEFT, 0);
    BoxSizer7->Add(20,1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(Panel5, ID_STATICTEXT4, _("Port"), wxDefaultPosition, wxDLG_UNIT(Panel5,wxSize(38,8)), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT4"));
    BoxSizer7->Add(StaticText4, 0, wxALIGN_LEFT, 5);
    PortSrvText1 = new wxTextCtrl(Panel5, ID_TEXTCTRL2, _("3000"), wxDefaultPosition, wxDLG_UNIT(Panel5,wxSize(30,-1)), wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer7->Add(PortSrvText1, 0, wxTOP|wxBOTTOM, 0);
    BtnOpenSrv = new wxButton(Panel5, ID_BUTTON1, _("Open server"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer7->Add(BtnOpenSrv, 0, wxTOP|wxEXPAND, 8);
    BtnCloseSrv = new wxButton(Panel5, ID_BUTTON2, _("Close server"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer7->Add(BtnCloseSrv, 0, wxTOP|wxBOTTOM|wxEXPAND, 4);
    Panel5->SetSizer(BoxSizer7);
    BoxSizer3->Add(Panel5, 0, wxALL|wxEXPAND, 5);
    Panel6 = new wxPanel(Panel2, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    BoxSizer5 = new wxBoxSizer(wxVERTICAL);
    StaticText1 = new wxStaticText(Panel6, ID_STATICTEXT1, _("Client list"), wxDefaultPosition, wxDLG_UNIT(Panel6,wxSize(45,8)), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT1"));
    BoxSizer5->Add(StaticText1, 0, wxALL|wxALIGN_LEFT, 5);
    ListBox1 = new wxListBox(Panel6, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_LISTBOX1"));
    BoxSizer5->Add(ListBox1, 1, wxALL|wxEXPAND, 5);
    BtnDropClient = new wxButton(Panel6, ID_BUTTON8, _("Drop client"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer5->Add(BtnDropClient, 0, wxALL|wxALIGN_LEFT, 4);
    Panel6->SetSizer(BoxSizer5);
    BoxSizer3->Add(Panel6, 1, wxALL|wxEXPAND, 0);
    Panel7 = new wxPanel(Panel2, ID_PANEL7, wxDefaultPosition, wxSize(360,172), wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    BoxSizer6 = new wxBoxSizer(wxVERTICAL);
    StaticText2 = new wxStaticText(Panel7, ID_STATICTEXT2, _("Log"), wxDefaultPosition, wxDLG_UNIT(Panel7,wxSize(61,8)), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT2"));
    BoxSizer6->Add(StaticText2, 0, wxALL|wxALIGN_LEFT, 5);
    LogSrv1 = new wxTextCtrl(Panel7, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    BoxSizer6->Add(LogSrv1, 1, wxALL|wxEXPAND, 5);
    Panel7->SetSizer(BoxSizer6);
    BoxSizer3->Add(Panel7, 2, wxALL|wxEXPAND, 0);
    Panel2->SetSizer(BoxSizer3);
    BoxSizer4->Add(Panel2, 1, wxALL|wxEXPAND, 5);
    Panel4 = new wxPanel(Panel3, ID_PANEL4, wxDefaultPosition, wxSize(646,79), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    Panel8 = new wxPanel(Panel4, ID_PANEL8, wxDefaultPosition, wxDLG_UNIT(Panel4,wxSize(68,26)), wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    BoxSizer9 = new wxBoxSizer(wxVERTICAL);
    TextSendSrv1 = new wxTextCtrl(Panel8, ID_TEXTCTRL3, _("Message"), wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    BoxSizer9->Add(TextSendSrv1, 0, wxEXPAND, 0);
    Panel10 = new wxPanel(Panel8, ID_PANEL10, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    CheckBinarySrv = new wxCheckBox(Panel10, ID_CHECKBOX1, _("Binary mode (send a number)"), wxDefaultPosition, wxDLG_UNIT(Panel10,wxSize(119,8)), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBinarySrv->SetValue(false);
    BoxSizer10->Add(CheckBinarySrv, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlSrv1 = new wxSpinCtrl(Panel10, ID_SPINCTRL1, _T("12345"), wxDefaultPosition, wxDLG_UNIT(Panel10,wxSize(80,-1)), wxBORDER_SIMPLE, -32737, 32737, 12345, _T("ID_SPINCTRL1"));
    SpinCtrlSrv1->SetValue(_T("12345"));
    SpinCtrlSrv1->Disable();
    BoxSizer10->Add(SpinCtrlSrv1, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
    Panel10->SetSizer(BoxSizer10);
    BoxSizer9->Add(Panel10, 1, wxALL|wxEXPAND, 0);
    Panel8->SetSizer(BoxSizer9);
    BoxSizer8->Add(Panel8, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 4);
    Panel9 = new wxPanel(Panel4, ID_PANEL9, wxDefaultPosition, wxSize(139,95), wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    BoxSizer11 = new wxBoxSizer(wxVERTICAL);
    BtnSrvSendAll = new wxButton(Panel9, ID_BUTTON3, _("Send to all"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BtnSrvSendAll->SetMinSize(wxDLG_UNIT(Panel9,wxSize(48,13)));
    BoxSizer11->Add(BtnSrvSendAll, 0, wxEXPAND, 0);
    BtnSrvSendSel = new wxButton(Panel9, ID_BUTTON4, _("Send to sel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BtnSrvSendSel->SetMinSize(wxDLG_UNIT(Panel9,wxSize(48,13)));
    BoxSizer11->Add(BtnSrvSendSel, 0, wxTOP|wxEXPAND, 4);
    Panel9->SetSizer(BoxSizer11);
    BoxSizer8->Add(Panel9, 0, wxLEFT|wxEXPAND, 2);
    Panel4->SetSizer(BoxSizer8);
    BoxSizer4->Add(Panel4, 0, wxALL|wxEXPAND, 5);
    Panel3->SetSizer(BoxSizer4);
    Panel12 = new wxPanel(Notebook1, ID_PANEL12, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL12"));
    BoxSizer12 = new wxBoxSizer(wxVERTICAL);
    Panel13 = new wxPanel(Panel12, ID_PANEL13, wxDefaultPosition, wxSize(330,191), wxTAB_TRAVERSAL, _T("ID_PANEL13"));
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    Panel14 = new wxPanel(Panel13, ID_PANEL14, wxDefaultPosition, wxDLG_UNIT(Panel13,wxSize(58,36)), wxTAB_TRAVERSAL, _T("ID_PANEL14"));
    BoxSizer14 = new wxBoxSizer(wxVERTICAL);
    StaticText3 = new wxStaticText(Panel14, ID_STATICTEXT5, _("Address"), wxDefaultPosition, wxDLG_UNIT(Panel14,wxSize(56,8)), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT5"));
    BoxSizer14->Add(StaticText3, 0, wxBOTTOM|wxALIGN_LEFT, 5);
    TextClientHost1 = new wxTextCtrl(Panel14, ID_TEXTCTRL7, _("127.0.0.1"), wxDefaultPosition, wxDLG_UNIT(Panel14,wxSize(30,-1)), wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    BoxSizer14->Add(TextClientHost1, 0, wxTOP|wxBOTTOM|wxEXPAND, 0);
    StaticText5 = new wxStaticText(Panel14, ID_STATICTEXT6, _("Port"), wxDefaultPosition, wxDLG_UNIT(Panel14,wxSize(38,8)), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT6"));
    BoxSizer14->Add(StaticText5, 0, wxALIGN_LEFT, 5);
    TextClientPort1 = new wxTextCtrl(Panel14, ID_TEXTCTRL4, _("3000"), wxDefaultPosition, wxDLG_UNIT(Panel14,wxSize(30,-1)), wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    BoxSizer14->Add(TextClientPort1, 0, wxTOP|wxBOTTOM, 0);
    BtnClientConn = new wxButton(Panel14, ID_BUTTON5, _("Connect"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer14->Add(BtnClientConn, 0, wxTOP|wxEXPAND, 8);
    BtnClientDisconn = new wxButton(Panel14, ID_BUTTON6, _("Disconnect"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer14->Add(BtnClientDisconn, 0, wxTOP|wxBOTTOM|wxEXPAND, 4);
    Panel14->SetSizer(BoxSizer14);
    BoxSizer13->Add(Panel14, 0, wxALL|wxEXPAND, 5);
    Panel16 = new wxPanel(Panel13, ID_PANEL16, wxDefaultPosition, wxSize(360,172), wxTAB_TRAVERSAL, _T("ID_PANEL16"));
    BoxSizer16 = new wxBoxSizer(wxVERTICAL);
    StaticText7 = new wxStaticText(Panel16, ID_STATICTEXT8, _("Log"), wxDefaultPosition, wxDLG_UNIT(Panel16,wxSize(61,8)), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT8"));
    BoxSizer16->Add(StaticText7, 0, wxALL|wxALIGN_LEFT, 5);
    LogClient1 = new wxTextCtrl(Panel16, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    BoxSizer16->Add(LogClient1, 1, wxALL|wxEXPAND, 5);
    Panel16->SetSizer(BoxSizer16);
    BoxSizer13->Add(Panel16, 2, wxALL|wxEXPAND, 0);
    Panel13->SetSizer(BoxSizer13);
    BoxSizer12->Add(Panel13, 1, wxALL|wxEXPAND, 5);
    Panel17 = new wxPanel(Panel12, ID_PANEL17, wxDefaultPosition, wxSize(646,79), wxTAB_TRAVERSAL, _T("ID_PANEL17"));
    BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    Panel18 = new wxPanel(Panel17, ID_PANEL18, wxDefaultPosition, wxDLG_UNIT(Panel17,wxSize(68,26)), wxTAB_TRAVERSAL, _T("ID_PANEL18"));
    BoxSizer18 = new wxBoxSizer(wxVERTICAL);
    TextSendClient1 = new wxTextCtrl(Panel18, ID_TEXTCTRL6, _("Message"), wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    BoxSizer18->Add(TextSendClient1, 0, wxEXPAND, 0);
    Panel19 = new wxPanel(Panel18, ID_PANEL19, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL19"));
    BoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
    CheckBinaryClient = new wxCheckBox(Panel19, ID_CHECKBOX2, _("Binary mode (send a number)"), wxDefaultPosition, wxDLG_UNIT(Panel19,wxSize(119,8)), 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBinaryClient->SetValue(false);
    BoxSizer19->Add(CheckBinaryClient, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlClient1 = new wxSpinCtrl(Panel19, ID_SPINCTRL2, _T("12345"), wxDefaultPosition, wxDLG_UNIT(Panel19,wxSize(80,-1)), wxBORDER_SIMPLE, -32737, 32737, 12345, _T("ID_SPINCTRL2"));
    SpinCtrlClient1->SetValue(_T("12345"));
    SpinCtrlClient1->Disable();
    BoxSizer19->Add(SpinCtrlClient1, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
    Panel19->SetSizer(BoxSizer19);
    BoxSizer18->Add(Panel19, 1, wxALL|wxEXPAND, 0);
    Panel18->SetSizer(BoxSizer18);
    BoxSizer17->Add(Panel18, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 4);
    Panel20 = new wxPanel(Panel17, ID_PANEL20, wxDefaultPosition, wxSize(139,95), wxTAB_TRAVERSAL, _T("ID_PANEL20"));
    BoxSizer20 = new wxBoxSizer(wxVERTICAL);
    BtnClientSend = new wxButton(Panel20, ID_BUTTON7, _("Send"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BtnClientSend->SetMinSize(wxDLG_UNIT(Panel20,wxSize(48,13)));
    BoxSizer20->Add(BtnClientSend, 0, wxEXPAND, 0);
    Panel20->SetSizer(BoxSizer20);
    BoxSizer17->Add(Panel20, 0, wxLEFT|wxEXPAND, 2);
    Panel17->SetSizer(BoxSizer17);
    BoxSizer12->Add(Panel17, 0, wxALL|wxEXPAND, 5);
    Panel12->SetSizer(BoxSizer12);
    Notebook1->AddPage(Panel3, _("Server"), false);
    Notebook1->AddPage(Panel12, _("Client"), false);
    BoxSizer2->Add(Notebook1, 1, wxALL|wxEXPAND, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Fit();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnBtnOpenSrvClick1);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnBtnCloseSrvClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnBtnDropClientClick);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnCheckBinarySrvClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnBtnSrvSendAllClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnBtnSrvSendSelClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnBtnClientConnClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnBtnClientDisconnClick);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnCheckBinaryClientClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&tcptestFrame::OnBtnClientSendClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&tcptestFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&tcptestFrame::OnAbout);
    //*)

    TCPServer1 = new SimpleTCPServer(this, ID_TCPSERVER1);
    Connect(ID_TCPSERVER1, EV_CLIENTCONNECTED,(wxObjectEventFunction)&tcptestFrame::TCPServer1OnConnected);
    Connect(ID_TCPSERVER1, EV_CLIENTDISCONNECTED,(wxObjectEventFunction)&tcptestFrame::TCPServer1OnDisconnected);
    Connect(ID_TCPSERVER1, EV_ONDATA,(wxObjectEventFunction)&tcptestFrame::TCPServer1OnData);


    TCPClient1 = new SimpleTCPClient(this, ID_TCPCLIENT1);
    Connect(ID_TCPCLIENT1, EV_CLIENTONDATA,(wxObjectEventFunction)&tcptestFrame::TCPClient1OnData);

}

// Old habits...
wxString IntToStr( int num_in )
{
    wxString str_out = wxString::Format(wxT("%i"),num_in);
    return str_out;
}
int StrToInt( wxString str_in )
{
    int int_out = wxAtoi(str_in);
    return int_out;
}
void tcptestFrame::LogServer( wxString logText )
{
    // Prints log to a text control
    // "(GUI)" is prepended to make it easier to understand how the application works
    // It will show which part of log was generated here
    LogSrv1->WriteText("(GUI) " + logText + "\n");
}
void tcptestFrame::LogClient( wxString logText )
{
    // Prints log to a text control
    // "(GUI)" is prepended to make it easier to understand how the application works
    // It will show which part of log was generated here
    LogClient1->WriteText("(GUI) " + logText + "\n");
}

void tcptestFrame::TCPClient1OnData(wxCommandEvent& event)
{

    // This will turn true if we find non-string data
    bool binaryData = false;

    LogClient("Incoming data:");

    // Peek single byte (peeking doesn't clear data that was read)
    unsigned char peekBuf[1];
    TCPClient1->Peek(peekBuf, 1);

    // If data starts with 0x00 or 0x01 we assume that it is binary data
    // This is just an example and not a standard of any kind
    if (peekBuf[0] == 0x00 || peekBuf[0] == 0x01) binaryData = true;


    // If this is not binary data, just read it as text string and print to log
    if ( !binaryData )
    {
        LogClient( TCPClient1->ReadStr() );
    }
    else if ( binaryData ) // If it is binary data, then proceed with it
    {
        LogClient("Found binary data");

        // Prepare 8-byte data buffer to receive data
        // because currently we are only handling 8-byte data packets

        unsigned char recvBuf[8];
        memset(recvBuf, 0, 8); // Fill with zeros

        // Read 8 bytes to buffer
        TCPClient1->Read(recvBuf, 8);

        // Check if data contains header and termination that we can understand
        // Currently we are only expecting data in this format:
        // 0x01 0x49 0x04 X X X X 0x04
        // where X X X X are 4 bytes of 32-bit integer number
        //
        if (recvBuf[0] == 0x01 && recvBuf[1] == 0x49 && recvBuf[2] == 0x04 && recvBuf[7] == 0x04)
        {
            // Resulting number will be stored here
            long integerValue = 0;

            // Read 4 bytes of data into 32-bit integer
            // i<4 means 4 bytes, recvBuf[3+i] means we start reading from 3rd byte of buffer
            for (int i=0; i<4; i++) integerValue |= (recvBuf[3+i] << i*8);

            // Print received integer value in log
            LogClient("Received 32-bit integer value:\n"
                      +  wxString::Format(wxT("%i"),integerValue) );

        }
        else LogClient("Unknown format of data"); // Warn about unrecognized data if it didn't met specified conditions

    }

}

void tcptestFrame::TCPServer1OnConnected(wxCommandEvent& event)
{
    LogServer("Client connected");
    UpdateGUI();
}

void tcptestFrame::TCPServer1OnDisconnected(wxCommandEvent& event)
{
    LogServer("Client disconnected");
    UpdateGUI();
}

void tcptestFrame::TCPServer1OnData(wxCommandEvent& event)
{

    wxSocketBase *sock = (wxSocketBase*) event.GetClientData();
    wxIPV4address addr;
    sock->GetPeer(addr);

    //LogServer( "Data from " + addr.IPAddress() + ":\n"
    //            + TCPServer1->ReadStr( sock ) );


    // This will turn true if we find non-string data
    bool binaryData = false;

    LogServer( "Data from " + addr.IPAddress() + "\n" );

    // Peek single byte (peeking doesn't clear data that was read)
    unsigned char peekBuf[1];
    TCPServer1->Peek(peekBuf, 1, sock);

    // If data starts with 0x00 or 0x01 we assume that it is binary data
    // This is just an example and not a standard of any kind
    if (peekBuf[0] == 0x00 || peekBuf[0] == 0x01) binaryData = true;


    // If this is not binary data, just read it as text string and print to log
    if ( !binaryData )
    {
        LogServer( TCPServer1->ReadStr(sock) );
    }
    else if ( binaryData ) // If it is binary data, then proceed with it
    {
        LogServer("Found binary data");

        // Prepare 8-byte data buffer to receive data
        // because currently we are only handling 8-byte data packets

        unsigned char recvBuf[8];
        memset(recvBuf, 0, 8); // Fill with zeros

        // Read 8 bytes to buffer
        TCPServer1->Read(recvBuf, 8, sock);

        // Check if data contains header and termination that we can understand
        // Currently we are only expecting data in this format:
        // 0x01 0x49 0x04 X X X X 0x04
        // where X X X X are 4 bytes of 32-bit integer number
        //
        if (recvBuf[0] == 0x01 && recvBuf[1] == 0x49 && recvBuf[2] == 0x04 && recvBuf[7] == 0x04)
        {
            // Resulting number will be stored here
            long integerValue = 0;

            // Read 4 bytes of data into 32-bit integer
            // i<4 means 4 bytes, recvBuf[3+i] means we start reading from 3rd byte of buffer
            for (int i=0; i<4; i++) integerValue |= (recvBuf[3+i] << i*8);

            // Print received integer value in log
            LogServer("Received 32-bit integer value:\n"
                      +  wxString::Format(wxT("%i"),integerValue) );

        }
        else LogServer("Unknown format of data"); // Warn about unrecognized data if it didn't met specified conditions

    }

}


tcptestFrame::~tcptestFrame()
{
    //(*Destroy(tcptestFrame)
    //*)
}

void tcptestFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}


void tcptestFrame::UpdateGUI()
{

    if (TCPServer1) // Update IP list and client count with current server data
    {
        // Display client count
        LabelCount1->SetLabel( "Client count: " + IntToStr( TCPServer1->clientCount() ) );

        // Get target address from selected IP list field
        int lastIndex = ListBox1->GetSelection();
        wxString lastSelection = "";
        if (lastIndex >= 0) lastSelection = ListBox1->GetString(lastIndex);

        ListBox1->Clear(); // Temporarily clear list of clients

        // Iterate over map of connected clients and update list
        for( std::map<wxSocketBase*, wxString>::const_iterator it = TCPServer1->clientMap.begin();
            it != TCPServer1->clientMap.end(); ++it)
        {
            ListBox1->Append( it->second );
        }

        // Bring back the last selection
        if (lastIndex >= 0) ListBox1->SetStringSelection(lastSelection);

    }
    else // Clear everything if server is not active
    {
        ListBox1->Clear();
        LabelCount1->SetLabel( "Client count: 0" );
    }
}


void tcptestFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = "TCP test built with \n" + wxbuildinfo(long_f);
    wxMessageBox(msg, _("About"));
}

void tcptestFrame::OnBtnOpenSrvClick(wxCommandEvent& event)
{


}

void tcptestFrame::OnBtnSrvSendSelClick(wxCommandEvent& event)
{

    // If no binary mode checked, just send text string
    if (!CheckBinarySrv->GetValue())
    {
        // Get target address from selected IP list field
        int selectedAddrIndex = ListBox1->GetSelection();

        // Proceed only if selection index is 0 or greater (-1 would mean no selection)
        if (selectedAddrIndex >= 0)
        {
            wxString targetAddr = ListBox1->GetString(selectedAddrIndex);
            // Send to target address
            TCPServer1->WriteStr(TextSendSrv1->GetValue(), targetAddr );
        }
    }
    else
    {
        // Prepare 8-byte data buffer
        unsigned char sendBuf[8];
        memset(sendBuf, 0, 8); // Fill with zeros

        // Get a number that we want to send as binary data
        // It will be stored in 32-bit integer, that means 4 bytes of data
        long integerValue = SpinCtrlSrv1->GetValue();

        // Create a header in first three bytes (we are counting bytes from zero)
        // this is just an example and not some standard format, client application needs to recognize our format
        sendBuf[0] = 0x01; // Receiver will read this as beginning of binary packet
        sendBuf[1] = 0x49; // This is hex code of "I" letter, that will mean signed integer
        sendBuf[2] = 0x04; // 0x04 will mean we are sending 4 bytes of 32-bit integer

        // Put 32-bit integer into buffer
        // 3 in sendBuf[3+i] means that value will be placed starting with 3rd byte of buffer
        // i<4 means that we are writing 4 bytes
        for (int i=0; i<4; i++) sendBuf[3+i] = (integerValue >> i*8) & 0xFF;

        sendBuf[7] = 0x04; // Set last byte to 0x04 as a footer (this is just an arbitrary choice)

        // Get target address from selected IP list field
        int selectedAddrIndex = ListBox1->GetSelection();

        // Proceed only if selection index is 0 or greater (-1 would mean no selection)
        if (selectedAddrIndex >= 0)
        {
            wxString targetAddr = ListBox1->GetString(selectedAddrIndex);
            // Send to target address
            TCPServer1->Write(sendBuf, 8, targetAddr );
        }

        /*
        // Note: because we are sending binary data, it also needs to be read as such.
        // Reading it as text would result in empty string or random characters.
        // Receiver should read first bytes of our header, recognize format of the data
        // and process it properly (this is done in client receiving example).
        */
    }


}

void tcptestFrame::OnBtnOpenSrvClick1(wxCommandEvent& event)
{
    TCPServer1->logBox = LogSrv1;
    TCPServer1->Port( wxAtoi( PortSrvText1->GetValue() ) );
    TCPServer1->Open();
}

void tcptestFrame::OnBtnCloseSrvClick(wxCommandEvent& event)
{
    TCPServer1->Close();
    UpdateGUI();
}

void tcptestFrame::OnBtnClientConnClick(wxCommandEvent& event)
{
    TCPClient1->logBox = LogClient1;
    TCPClient1->Connect( TextClientHost1->GetValue(), wxAtoi( TextClientPort1->GetValue() ) );
}

void tcptestFrame::OnBtnClientDisconnClick(wxCommandEvent& event)
{
    TCPClient1->Disconnect();
}

void tcptestFrame::OnBtnClientSendClick(wxCommandEvent& event)
{

    if (!CheckBinaryClient->GetValue())
    {
        TCPClient1->WriteStr( TextSendClient1->GetValue() );
    }
    else
    {
        // Prepare 8-byte data buffer
        unsigned char sendBuf[8];
        memset(sendBuf, 0, 8); // Fill with zeros

        // Get a number that we want to send as binary data
        // It will be stored in 32-bit integer, that means 4 bytes of data
        long integerValue = SpinCtrlClient1->GetValue();

        // Create a header in first three bytes (we are counting bytes from zero)
        // this is just an example and not some standard format, client application needs to recognize our format
        sendBuf[0] = 0x01; // Receiver will read this as beginning of binary packet
        sendBuf[1] = 0x49; // This is hex code of "I" letter, that will mean signed integer
        sendBuf[2] = 0x04; // 0x04 will mean we are sending 4 bytes of 32-bit integer

        // Put 32-bit integer into buffer
        // 3 in sendBuf[3+i] means that value will be placed starting with 3rd byte of buffer
        // i<4 means that we are writing 4 bytes
        for (int i=0; i<4; i++) sendBuf[3+i] = (integerValue >> i*8) & 0xFF;

        sendBuf[7] = 0x04; // Set last byte to 0x04 as a footer (this is just an arbitrary choice)

        TCPClient1->Write(sendBuf, 8);
    }

}



void tcptestFrame::OnBtnSrvSendAllClick(wxCommandEvent& event)
{
    // If no binary mode checked, just send text string
    if (!CheckBinarySrv->GetValue())
    {
        TCPServer1->WriteStr(TextSendSrv1->GetValue());
    }
    else
    {
        // Prepare 8-byte data buffer
        unsigned char sendBuf[8];
        memset(sendBuf, 0, 8); // Fill with zeros

        // Get a number that we want to send as binary data
        // It will be stored in 32-bit integer, that means 4 bytes of data
        long integerValue = SpinCtrlSrv1->GetValue();

        // Create a header in first three bytes (we are counting bytes from zero)
        // this is just an example and not some standard format, client application needs to recognize our format
        sendBuf[0] = 0x01; // Receiver will read this as beginning of binary packet
        sendBuf[1] = 0x49; // This is hex code of "I" letter, that will mean signed integer
        sendBuf[2] = 0x04; // 0x04 will mean we are sending 4 bytes of 32-bit integer

        // Put 32-bit integer into buffer
        // 3 in sendBuf[3+i] means that value will be placed starting with 3rd byte of buffer
        // i<4 means that we are writing 4 bytes
        for (int i=0; i<4; i++) sendBuf[3+i] = (integerValue >> i*8) & 0xFF;

        sendBuf[7] = 0x04; // Set last byte to 0x04 as a footer (this is just an arbitrary choice)

        // Iterate over list of all clients and send data
        for (int i=0; i< ListBox1->GetCount(); i++)
        {
            wxString targetAddr = ListBox1->GetString(i);
            TCPServer1->Write(sendBuf, 8, targetAddr );
        }

        /*
        // Note: because we are sending binary data, it also needs to be read as such.
        // Reading it as text would result in empty string or random characters.
        // Receiver should read first bytes of our header, recognize format of the data
        // and process it properly (this is done in client receiving example).
        */
    }

}

void tcptestFrame::OnCheckBinarySrvClick(wxCommandEvent& event)
{
    if (CheckBinarySrv->GetValue())
    {
        SpinCtrlSrv1->Enable();
        TextSendSrv1->Disable();
    }
    else
    {
        SpinCtrlSrv1->Disable();
        TextSendSrv1->Enable();
    }
}

void tcptestFrame::OnBtnDropClientClick(wxCommandEvent& event)
{
    // Get target address from selected IP list field
    int selectedAddrIndex = ListBox1->GetSelection();

    // Proceed only if selection index is 0 or greater (-1 would mean no selection)
    if (selectedAddrIndex >= 0)
    {
        wxString targetAddr = ListBox1->GetString(selectedAddrIndex);
        // Send to target address
        TCPServer1->DropClient(targetAddr);
    }
}

void tcptestFrame::OnCheckBinaryClientClick(wxCommandEvent& event)
{
    if (CheckBinaryClient->GetValue())
    {
        SpinCtrlClient1->Enable();
        TextSendClient1->Disable();
    }
    else
    {
        SpinCtrlClient1->Disable();
        TextSendClient1->Enable();
    }
}
