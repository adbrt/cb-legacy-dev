#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "wx/wx.h"
#include "wx/socket.h"
#include "wx/event.h"
#include <list>
#include <map>


DECLARE_EVENT_TYPE(EV_CLIENTCONNECTED, wxCommandEvent);
DECLARE_EVENT_TYPE(EV_CLIENTDISCONNECTED, wxCommandEvent);
DECLARE_EVENT_TYPE(EV_ONDATA, wxCommandEvent);
DECLARE_EVENT_TYPE(EV_ONERROR, wxCommandEvent);
DECLARE_EVENT_TYPE(EV_ONCLOSE, wxCommandEvent);


class SimpleTCPServer :  public wxEvtHandler
{

    public:


        int maxClients;

        int logLevel;

        SimpleTCPServer(wxEvtHandler* parent, wxWindowID id); // Constructor
        virtual ~SimpleTCPServer(); // Destructor

        void Open( unsigned int port = NULL ); // This will start listening (address is optional, port can be also set with different function)

        wxSocketBase *currentClient; // Client currently interacting with server (automatically updated when someone connects or send data)

        wxString ReadStr( wxSocketBase* sock = NULL ); // Read from buffer as string, provide socket to read or use default one

        // Write string to socket (provide a socket or use currentClient)
        void WriteStr( wxString str_in, wxSocketBase* sock = NULL );

        // Write string to provided "ip:port" if a matching socket is connected
        void WriteStr( wxString str_in, wxString ip_port );

        // Write data (for example char array) to socket (provide a socket or use currentClient)
        void Write( const void *data, unsigned int dataBytes, wxSocketBase* sock = NULL );

        // Write data (for example char array) to provided "ip:port" if a matching socket is connected
        void Write( const void *data, unsigned int dataBytes, wxString ip_port );

        // Peek buffer as string, provide socket to read or use default one
        wxString PeekStr(wxSocketBase* sock = NULL);

        // Peek buffer, provide socket to read or use default one
        int Peek( void *buffer, unsigned int nbytes, wxSocketBase* sock = NULL );

        // Read buffer, provide socket to read or use default one
        int Read( void *buffer, unsigned int nbytes, wxSocketBase* sock = NULL );

        void Close(); // This will stop listening and disconnect everyone

        void DropClient(wxSocketBase *sock); // This will disconnect chosen client

        void DropClient(wxString ip_port); // This will disconnect chosen client


        unsigned int Port( unsigned int port = 0 ); // Return current port number (if no arguments) or set new port number (if specified)


        unsigned int clientCount() { return connectedClients; }; // Returns number of connected clients

        // Connected clients will be stored here along with info
        // wxSocketBase* is the actual socket, wxString is human-readable representation of address
        std::map<wxSocketBase*, wxString> clientMap;

        wxTextCtrl *logBox; // Text control to be used as log output (optional)



        void OnServerEvent(wxSocketEvent &event);
        void OnClientEvent(wxSocketEvent &event);

        void OnRecv(wxSocketBase *sock);
        void OnConnLost(wxSocketBase *sock);

        bool IsOk()
        {
            if (Listener) return Listener->IsOk();
            else return false;
        }




    private:

        wxEvtHandler * m_parent; // Parent form
        wxWindowID m_id; // ID assigned to current instance of server

        wxSocketServer* Listener; // Server things will be handled here

        unsigned int connectedClients; // Client count is stored here

        unsigned int srvPort;

        void LogServer( wxString logText ); // Log will be printed with this function if required


        static const long SERVER_ID; // For event handling
        static const long CLIENT_ID; // For event handling
        DECLARE_EVENT_TABLE() // For event handling

};

#endif // TCPSERVER_H
