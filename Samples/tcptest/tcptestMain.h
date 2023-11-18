#ifndef HEADER_878F1DDCB707631B
#define HEADER_878F1DDCB707631B

/***************************************************************
 * Name:      tcptestMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2023-11-10
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef TCPTESTMAIN_H
#define TCPTESTMAIN_H

//(*Headers(tcptestFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)

#include "tcpserver.h"
#include "tcpclient.h"

class tcptestFrame: public wxFrame
{
    public:

        tcptestFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~tcptestFrame();

        void LogServer(wxString logText);
        void LogClient(wxString logText);
        void UpdateGUI();


    private:

        //(*Handlers(tcptestFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnBtnOpenSrvClick(wxCommandEvent& event);
        void OnBtnSrvSendSelClick(wxCommandEvent& event);
        void OnBtnOpenSrvClick1(wxCommandEvent& event);
        void OnBtnCloseSrvClick(wxCommandEvent& event);
        void OnBtnClientConnClick(wxCommandEvent& event);
        void OnBtnClientDisconnClick(wxCommandEvent& event);
        void OnBtnClientSendClick(wxCommandEvent& event);
        void OnBtnSrvSendAllClick(wxCommandEvent& event);
        void OnCheckBinarySrvClick(wxCommandEvent& event);
        void OnBtnDropClientClick(wxCommandEvent& event);
        void OnCheckBinaryClientClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(tcptestFrame)
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_PANEL5;
        static const long ID_STATICTEXT1;
        static const long ID_LISTBOX1;
        static const long ID_BUTTON8;
        static const long ID_PANEL6;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL1;
        static const long ID_PANEL7;
        static const long ID_PANEL2;
        static const long ID_TEXTCTRL3;
        static const long ID_CHECKBOX1;
        static const long ID_SPINCTRL1;
        static const long ID_PANEL10;
        static const long ID_PANEL8;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_PANEL9;
        static const long ID_PANEL4;
        static const long ID_PANEL3;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL7;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_PANEL14;
        static const long ID_STATICTEXT8;
        static const long ID_TEXTCTRL5;
        static const long ID_PANEL16;
        static const long ID_PANEL13;
        static const long ID_TEXTCTRL6;
        static const long ID_CHECKBOX2;
        static const long ID_SPINCTRL2;
        static const long ID_PANEL19;
        static const long ID_PANEL18;
        static const long ID_BUTTON7;
        static const long ID_PANEL20;
        static const long ID_PANEL17;
        static const long ID_PANEL12;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(tcptestFrame)
        wxButton* BtnClientConn;
        wxButton* BtnClientDisconn;
        wxButton* BtnClientSend;
        wxButton* BtnCloseSrv;
        wxButton* BtnDropClient;
        wxButton* BtnOpenSrv;
        wxButton* BtnSrvSendAll;
        wxButton* BtnSrvSendSel;
        wxCheckBox* CheckBinaryClient;
        wxCheckBox* CheckBinarySrv;
        wxListBox* ListBox1;
        wxNotebook* Notebook1;
        wxPanel* Panel10;
        wxPanel* Panel12;
        wxPanel* Panel13;
        wxPanel* Panel14;
        wxPanel* Panel16;
        wxPanel* Panel17;
        wxPanel* Panel18;
        wxPanel* Panel19;
        wxPanel* Panel1;
        wxPanel* Panel20;
        wxPanel* Panel2;
        wxPanel* Panel3;
        wxPanel* Panel4;
        wxPanel* Panel5;
        wxPanel* Panel6;
        wxPanel* Panel7;
        wxPanel* Panel8;
        wxPanel* Panel9;
        wxSpinCtrl* SpinCtrlClient1;
        wxSpinCtrl* SpinCtrlSrv1;
        wxStaticText* LabelCount1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxStatusBar* StatusBar1;
        wxTextCtrl* LogClient1;
        wxTextCtrl* LogSrv1;
        wxTextCtrl* PortSrvText1;
        wxTextCtrl* TextClientHost1;
        wxTextCtrl* TextClientPort1;
        wxTextCtrl* TextSendClient1;
        wxTextCtrl* TextSendSrv1;
        //*)

        SimpleTCPServer *TCPServer1;
        static const long ID_TCPSERVER1;
        void TCPServer1OnConnected( wxCommandEvent& event ); // When new client is connected
        void TCPServer1OnDisconnected( wxCommandEvent& event ); // When a client is disconnected
        void TCPServer1OnData( wxCommandEvent& event ); // When new data is available
        void TCPServer1OnError( wxCommandEvent& event ); // When an error happens

        SimpleTCPClient *TCPClient1;
        static const long ID_TCPCLIENT1;
        void TCPClient1OnData( wxCommandEvent& event ); // When new data is available


        DECLARE_EVENT_TABLE()
};

#endif // TCPTESTMAIN_H
#endif // header guard

