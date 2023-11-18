#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "wx/wx.h"
#include "wx/socket.h"
#include "wx/event.h"
#include <list>

DECLARE_EVENT_TYPE(EV_CONNECTED, wxCommandEvent);
DECLARE_EVENT_TYPE(EV_CLIENTONDATA, wxCommandEvent);

class SimpleTCPClient : public wxEvtHandler
{

    public:


        int maxClients;

        SimpleTCPClient(wxEvtHandler* parent, wxWindowID id); // Constructor
        virtual ~SimpleTCPClient(); // Destructor

        void Connect( wxString hostname, unsigned int port ); // This will start listening (address is optional, port can be also set with different function)

        void Disconnect();

        unsigned int Port( unsigned int port = 0 ); // Return current port number (if no arguments) or set new port number (if specified)

        wxTextCtrl *logBox; // Text control to be used as log output (optional)


        void OnSocketEvent(wxSocketEvent &event);

        void OnRecv(wxSocketBase *sock);

        wxString ReadStr();

        int Read( void *buffer, unsigned int nbytes );

        wxString PeekStr();

        int Peek( void *buffer, unsigned int nbytes );

        void WriteStr( wxString str_in );

        // Write data (for example char array) to socket
        void Write( const void *data, unsigned int dataBytes );

        // Write data (for example char array) to socket
        void WriteWait( const void *data, unsigned int dataBytes );

        bool isDisconnected()
        {
            if (Client)
            {
                if (Client->IsDisconnected()) return true;
                else return false;
            }
            else return true;
        };


    private:


        bool disconnected;
        wxEvtHandler * m_parent; // Parent form
        wxWindowID m_id; // ID assigned to current instance of server

        wxSocketClient *Client; // Client things will happen here

        void LogClient( wxString logText ); // Log will be printed with this function if required


        static const long SOCKET_ID; // For event handling
        DECLARE_EVENT_TABLE() // For event handling

};

#endif // TCPCLIENT_H
