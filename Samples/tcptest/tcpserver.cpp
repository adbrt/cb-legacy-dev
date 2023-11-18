#include "tcpserver.h"

#define BUF_SIZE 1024

const long SimpleTCPServer::SERVER_ID = wxNewId();
const long SimpleTCPServer::CLIENT_ID = wxNewId();

BEGIN_EVENT_TABLE(SimpleTCPServer, wxEvtHandler)
    EVT_SOCKET(SERVER_ID, SimpleTCPServer::OnServerEvent)
    EVT_SOCKET(CLIENT_ID, SimpleTCPServer::OnClientEvent)
END_EVENT_TABLE()


DEFINE_EVENT_TYPE(EV_CLIENTCONNECTED);
DEFINE_EVENT_TYPE(EV_CLIENTDISCONNECTED);
DEFINE_EVENT_TYPE(EV_ONDATA);
DEFINE_EVENT_TYPE(EV_ONERROR);
DEFINE_EVENT_TYPE(EV_ONCLOSE);


SimpleTCPServer::SimpleTCPServer(wxEvtHandler* parent, wxWindowID id)
{
    maxClients = 10; // Clients beyond that will be rejected by server (more than 1 is not handled well right now)
    m_id = id;
    m_parent = parent;
    logBox = NULL;
    logLevel = 0;
    Listener = NULL;
    currentClient = new wxSocketBase();  // Socket of current/most recent client will be stored here

}

SimpleTCPServer::~SimpleTCPServer()
{

}


void SimpleTCPServer::LogServer( wxString logText )
{
   // Append text to provided wxTextCtrl (if exists)
   // "(internal)" is added just to make it easier to understand how the application works
   // It will show which messages came from the "inside" of tcpserver.cpp file
   if (logBox != NULL) logBox->WriteText("(internal) " + logText + "\n");
}

void SimpleTCPServer::Open(unsigned int port)
{
    if (Listener == NULL)
    {
        wxIPV4address ipaddr;
        ipaddr.AnyAddress();
        if (port == NULL)
        {
            ipaddr.Service( srvPort );
        }
        else  ipaddr.Service( port );


        LogServer("Opening server");
        Listener = new wxSocketServer(ipaddr);
        connectedClients = 0;
        currentClient = NULL;

        if(Listener->Ok())
            LogServer("Started listening");
        else
            LogServer("Could not start listening");

        Listener->SetEventHandler(*this, SERVER_ID);
        Listener->SetNotify(wxSOCKET_CONNECTION_FLAG);
        Listener->Notify(true);
    }
    else
    {
        LogServer("Server already opened");
    }
}

void SimpleTCPServer::Close()
{
    if (Listener)
    {
        /** Removed in favor of map of clients
        // Iterate over list of connected clients to disconnect them all
        std::list<wxSocketBase*>::iterator it;
        for (it = clients.begin(); it != clients.end(); ++it)
        {
            (*it)->Destroy(); // Disconnect client
        }
        clients.clear(); // Clear the list after everyone is disconnected
        **/

        if (connectedClients >0)
        {
            // Iterate over map of connected clients
            for( std::map<wxSocketBase*, wxString>::const_iterator it = clientMap.begin();
                it != clientMap.end(); ++it)
            {
                it->first->Destroy(); // Disconnect client ( ->first means first element of map, that is wxSocketBase )
            }
            clientMap.clear(); // Clear the map of clients

            connectedClients = 0; // Clear number of clients
        }
        currentClient = NULL; // Clear current client

        Listener->Destroy(); // Remove the server
        Listener = NULL;

        LogServer("Closing server");

        // Post event about server closing
        //wxCommandEvent myevent(EV_ONCLOSE, m_id);
        //wxPostEvent(m_parent, myevent);

    }
    else LogServer("Server already closed");



}


// Peek buffer, provide socket to read or use default one
int SimpleTCPServer::Peek( void *buffer, unsigned int nbytes, wxSocketBase* sock )
{
    int result = 0;

    // Read from specified socket or default socket if not specified
    if (sock != NULL)
    {
        sock->Peek(buffer, nbytes);
        result = sock->LastCount();
    }
    else if (currentClient != NULL)
    {
        currentClient->Peek(buffer, nbytes);
        result = currentClient->LastCount();
    }

    return result;
}

// Peek buffer as string, provide socket to read or use default one
wxString SimpleTCPServer::PeekStr(wxSocketBase* sock)
{
    wxString readString = "";

    char buff[BUF_SIZE + 1]; // Buffer with byte for zero termination (end of string)
    memset(buff, 0, sizeof(buff));


    if (sock != NULL)
    {
        sock->Peek(&buff, BUF_SIZE);
    }
    else if (currentClient != NULL)
    {
        currentClient->Peek(&buff, BUF_SIZE);
    }

    readString = buff;

    return readString;
}

// Peek buffer, provide socket to read or use default one
int SimpleTCPServer::Read( void *buffer, unsigned int nbytes, wxSocketBase* sock )
{
    int result = 0;

    // Read from specified socket or default socket if not specified
    if (sock != NULL)
    {
        sock->Read(buffer, nbytes);
        result = sock->LastCount();
    }
    else if (currentClient != NULL)
    {
        currentClient->Read(buffer, nbytes);
        result = currentClient->LastCount();
    }

    return result;
}


// Read from socket and return a string (this should be mostly used for "human-readable" data)
wxString SimpleTCPServer::ReadStr( wxSocketBase* sock )
{
    wxString readString = "";

    char buff[BUF_SIZE + 1]; // Buffer with byte for zero termination (end of string)
    memset(buff, 0, sizeof(buff));

    // Read from specified socket or default socket if not specified
    if (sock != NULL) sock->Read(&buff, BUF_SIZE);
    else if (currentClient != NULL) currentClient->Read(&buff, BUF_SIZE);

    readString = buff;

    return readString;
}

void SimpleTCPServer::WriteStr( wxString str_in, wxSocketBase* sock )
{
    if (Listener != NULL) // No point in trying if server doesn't exist
    {
        // Write string to specified socket
        if (sock != NULL)
        {
            sock->Write(str_in.c_str(), str_in.Length());
        }
        else // Send to everyone
        {
            // Iterate over map of connected clients
            for( std::map<wxSocketBase*, wxString>::const_iterator it = clientMap.begin();
                it != clientMap.end(); ++it)
            {
                    WriteStr(str_in, it->first);
            }
            LogServer("Sent \"" + str_in + "\"");


        }
        //else if (currentClient != NULL) currentClient->Write(str_in.c_str(), str_in.Length());

    }

}

void SimpleTCPServer::WriteStr( wxString str_in, wxString ip_port )
{

    bool success = false;

    // Iterate over map of connected clients
    for( std::map<wxSocketBase*, wxString>::const_iterator it = clientMap.begin();
        it != clientMap.end(); ++it)
    {
        if (it->second == ip_port) // If provided address matches one of connected sockets
        {
            WriteStr(str_in, it->first);
            success = true;
            LogServer("Sent \"" + str_in + "\"");

        }
        if (success) return;
    }

}


void SimpleTCPServer::Write( const void *data, unsigned int dataBytes, wxSocketBase* sock )
{
    if (Listener != NULL) // No point in trying if server doesn't exist
    {
        // Write data to specified socket or default socket
        if (sock != NULL) sock->Write(data, dataBytes);
        else if (currentClient != NULL) currentClient->Write(data, dataBytes);
        LogServer("Sent binary data");
    }

}

void SimpleTCPServer::Write( const void *data, unsigned int dataBytes, wxString ip_port )
{

    bool success = false;

    // Iterate over map of connected clients
    for( std::map<wxSocketBase*, wxString>::const_iterator it = clientMap.begin();
        it != clientMap.end(); ++it)
    {
        if (it->second == ip_port) // If provided address matches one of connected sockets
        {
            Write(data, dataBytes, it->first);
            success = true;
        }
        if (success) return;
    }

}



void SimpleTCPServer::OnServerEvent(wxSocketEvent &event)
{
    if(event.GetSocketEvent() == wxSOCKET_CONNECTION)
    {
        wxSocketBase *clientSock = Listener->Accept(false);

        // Drop client if exceeded maximum count of clients
        if (connectedClients >= maxClients)
        {
            clientSock->Destroy();
            LogServer("Client rejected (limit exceeded)");
        }
        else
        {
            // Proceed normally if limit not exceeded

            clientSock->SetEventHandler(*this, CLIENT_ID);
            clientSock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
            clientSock->Notify(true);



            // Get IP address and port of connected client
            wxIPV4address clientAddr;
            clientSock->GetPeer(clientAddr);
            // Prepare a string with address:port
            wxString clientAddStr = clientAddr.IPAddress() + ":" + wxString::Format(wxT("%i"),clientAddr.Service());

            // Store client data in map with pair of socket and string with address:port
            clientMap.insert( std::pair<wxSocketBase*, wxString>(clientSock, clientAddStr) );

            currentClient = clientSock; // Set this client as current client

            connectedClients++;
            LogServer("Client connected (" + clientAddStr + ")"); // Print log with address of client

            wxCommandEvent myevent(EV_CLIENTCONNECTED, m_id);
            wxPostEvent(m_parent, myevent);

        }

    }

}

void SimpleTCPServer::OnClientEvent(wxSocketEvent &event)
{
    switch(event.GetSocketEvent())
    {
        case wxSOCKET_INPUT: OnRecv(event.GetSocket()); break;
        case wxSOCKET_LOST: OnConnLost(event.GetSocket()); break;
    }
}


unsigned int SimpleTCPServer::Port(unsigned int port)
{
    // Return current port number if no arguments or invalid value specified
    if ( (port < 1) || (port > 65535) || port == NULL )
    {
        return port;
    }
    else // Set new port number and reopen the server if needed
    {
        // Proceed only if port is different
        if (port != srvPort)
        {
            srvPort = port;
            LogServer("New port: " + wxString::Format(wxT("%i"),port) );

            // Restart server with new port (only if it was running before)
            if (Listener != NULL)
            {
                Close();
                Open();
            }

        }

    }
    return port;
}

void SimpleTCPServer::OnRecv(wxSocketBase *sock)
{

    LogServer("Incoming data");

    currentClient = sock; // Set data sender as current client (so it will be easy to respond to it later)

    // Put current socket in event data, so main application will be able to read it
    wxCommandEvent myevent(EV_ONDATA, m_id);
    myevent.SetClientData( sock );
    wxPostEvent(m_parent, myevent);


    //**** Data must be handled in main application.
    //**** If main application will only read partial data,
    //**** next events will be fired until all data is read.
    //**** But if application does not read any data,
    //**** data receive event will get stuck until it is manually read

    //if ( sock->IsData() ) OnRecv( sock ); // Keep receiving if more data is available (this is default behavior anyway)

}

void SimpleTCPServer::OnConnLost(wxSocketBase *sock)
{
    LogServer("Client disconnected");

    wxCommandEvent myevent(EV_CLIENTDISCONNECTED, m_id);
    myevent.SetClientData( sock );
    wxPostEvent(m_parent, myevent);

    connectedClients--;

    clientMap.erase( sock ); // Remove client from map of connected clients

    // Removed in favor of map
    // clients.remove(sock); // Remove client from list of clients

    if (currentClient == sock)
    {
        currentClient = NULL; // Clear current client if this is the one disconnecting
        LogServer("Clearing current client");
    }

    sock->Destroy();
}

void SimpleTCPServer::DropClient(wxSocketBase *sock)
{
    //LogServer("Dropping client");

    connectedClients--;

    wxCommandEvent myevent(EV_CLIENTDISCONNECTED, m_id);
    myevent.SetClientData( sock );
    wxPostEvent(m_parent, myevent);

    clientMap.erase( sock ); // Remove client from map of connected clients

    // Get IP address and port of connected client
    wxIPV4address clientAddr;
    sock->GetPeer(clientAddr);
    // Prepare a string with address:port
    wxString clientAddStr = clientAddr.IPAddress() + ":" + wxString::Format(wxT("%i"),clientAddr.Service());
    LogServer("Dropping client " + clientAddStr);

    if (currentClient == sock)
    {
        currentClient = NULL; // Clear current client if this is the one disconnecting
    }

    sock->Destroy();
}



void SimpleTCPServer::DropClient(wxString ip_port)
{


    bool success = false;

    // Iterate over map of connected clients
    for( std::map<wxSocketBase*, wxString>::const_iterator it = clientMap.begin();
        it != clientMap.end(); ++it)
    {
        if (it->second == ip_port) // If provided address matches one of connected sockets
        {
            //LogServer("Dropping client");

            connectedClients--;

            wxCommandEvent myevent(EV_CLIENTDISCONNECTED, m_id);
            myevent.SetClientData( it->first );
            wxPostEvent(m_parent, myevent);

            // Get IP address and port of connected client
            wxIPV4address clientAddr;
            it->first->GetPeer(clientAddr);
            // Prepare a string with address:port
            wxString clientAddStr = clientAddr.IPAddress() + ":" + wxString::Format(wxT("%i"),clientAddr.Service());
            LogServer("Dropping client " + clientAddStr);

            if (currentClient == it->first)
            {
                currentClient = NULL; // Clear current client if this is the one disconnecting
            }

            clientMap.erase( it->first ); // Remove client from map of connected clients

            it->first->Destroy();


        }
    }


}




