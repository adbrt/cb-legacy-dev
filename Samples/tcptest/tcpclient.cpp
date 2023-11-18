#include "tcpclient.h"

#define BUF_SIZE 1024

const long SimpleTCPClient::SOCKET_ID = wxNewId();

BEGIN_EVENT_TABLE(SimpleTCPClient, wxEvtHandler)
    EVT_SOCKET(SOCKET_ID, SimpleTCPClient::OnSocketEvent)
END_EVENT_TABLE()


DEFINE_EVENT_TYPE(EV_CONNECTED);
DEFINE_EVENT_TYPE(EV_CLIENTONDATA);

SimpleTCPClient::SimpleTCPClient(wxEvtHandler* parent, wxWindowID id)
{

    m_id = id;
    m_parent = parent;
    logBox = NULL;
    Client = NULL;

}

SimpleTCPClient::~SimpleTCPClient()
{

}

// Read specified number of bytes to specified buffer from socket and return actual number of read bytes
int SimpleTCPClient::Read( void *buffer, unsigned int nbytes )
{

    int result = 0;

    // Read data
    if (Client != NULL)
    {
        if ( Client->IsConnected() && !disconnected)
        {
            Client->Read(buffer, nbytes);
            result = Client->LastCount(); // Set number of actually read bytes as result
        }
    }

    return result;
}

// Peek specified number of bytes to specified buffer from socket and return actual number of peeked bytes
// This doesn't remove the data from socket and it can be read afterwards
int SimpleTCPClient::Peek( void *buffer, unsigned int nbytes )
{
    int result = 0;
    // Peek data
    if (Client != NULL && !disconnected)
    {
        if ( Client->IsConnected() )
        {
            Client->Peek(buffer, nbytes);
            result = Client->LastCount(); // Set number of actually peeked bytes as result
        }
    }
    return result;
}


// Read from socket and return a string (this should be mostly used for "human-readable" data)
wxString SimpleTCPClient::ReadStr()
{
    wxString readString = "";

    char buff[BUF_SIZE + 1]; // Buffer with byte for zero termination (end of string)
    memset(buff, 0, sizeof(buff));

    // Read data
    if (Client != NULL) Client->Read(&buff, BUF_SIZE);

    readString = buff;

    return readString;
}


// Peek data in socket without clearing the data and return a string (this should be mostly used for "human-readable" data)
wxString SimpleTCPClient::PeekStr()
{
    wxString readString = "";

    char buff[BUF_SIZE + 1]; // Buffer with byte for zero termination (end of string)
    memset(buff, 0, sizeof(buff));

    // Read data
    if (Client != NULL) Client->Peek(&buff, BUF_SIZE);

    readString = buff;

    return readString;
}

void SimpleTCPClient::LogClient( wxString logText )
{
   // Append text to provided wxTextCtrl (if exists)
   // "(internal)" is added just to make it easier to understand how the application works
   // It will show which messages came from the "inside" of tcpclient.cpp file
   if (logBox != NULL) logBox->WriteText("(internal) " + logText + "\n");
}

void SimpleTCPClient::Connect(wxString hostname, unsigned int port)
{
    if (Client == NULL)
    {
        wxIPV4address ipaddr;
        ipaddr.Hostname(hostname);
        ipaddr.Service(port);

        LogClient("Opening client");
        Client = new wxSocketClient();
        Client->SetFlags(wxSOCKET_NOWAIT); // wxSOCKET_NONE is default but produced some segfaults on retry

        Client->SetEventHandler(*this, SOCKET_ID);
        Client->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
        Client->Notify(true);

        Client->Connect(ipaddr, false);

    }
    else
    {

        if ( Client->IsConnected() )
        {
            LogClient( "Already connected" );
        }
        else if ( !Client->IsConnected() )
        {
            LogClient( "Connection in progress" );
        }

    }
}


void SimpleTCPClient::WriteStr( wxString str_in )
{
    if (Client != NULL) // No point in trying if client is not active
    {
        // Send string to server
        if ( Client->IsConnected() )
        {
            Client->Write(str_in.c_str(), str_in.Length());
            LogClient("Sent \"" + str_in + "\"");
        }
    }
}

void SimpleTCPClient::Write( const void *data, unsigned int dataBytes )
{
    if (Client != NULL) // No point in trying if client is not active
    {
        // Write data
        if ( Client->IsConnected() )
        {
            Client->Write(data, dataBytes);
            LogClient("Sent binary data");
        }
    }
}

void SimpleTCPClient::WriteWait( const void *data, unsigned int dataBytes )
{
    if (Client != NULL) // No point in trying if client is not active
    {
        // Write data
        if ( Client->IsConnected() )
        {
            //wxSocketFlags tempFlags = Client->GetFlags();

            //Client->SetFlags(wxSOCKET_BLOCK);

            Client->Write(data, dataBytes);
            Client->WaitForWrite(0,10);

            //Client->SetFlags(tempFlags);
        }
    }
}


void SimpleTCPClient::OnRecv(wxSocketBase *sock)
{

    LogClient("Incoming data");

    // Put current socket in event data, so main application will be able to read it
    wxCommandEvent myevent(EV_CLIENTONDATA, m_id);
    myevent.SetClientData( sock );
    wxPostEvent(m_parent, myevent);


    //**** Data must be handled in main application.
    //**** If main application will only read partial data,
    //**** next events will be fired until all data is read.
    //**** But if application does not read any data,
    //**** data receive event will get stuck until it is manually read

    //if ( sock->IsData() ) OnRecv( sock ); // Keep receiving if more data is available (this is default behavior anyway)

}

void SimpleTCPClient::Disconnect()
{
    if (Client != NULL)
    {
        Client->Destroy();
        Client->WaitForLost(0,50);
        Client = NULL;
        LogClient("Disconnecting from server");
    }
}

void SimpleTCPClient::OnSocketEvent(wxSocketEvent &event)
{

	LogClient("Socket event");

    wxSocketBase *sock = event.GetSocket();

    switch(event.GetSocketEvent())
    {
        case wxSOCKET_CONNECTION:
        {
            LogClient("Successfully connected");


            wxCommandEvent myevent(EV_CONNECTED, m_id);
            myevent.SetClientData( sock );
            wxPostEvent(m_parent, myevent);
            disconnected = false;

            break;
        }

        case wxSOCKET_INPUT:
        {
            // Redirect to OnRecv function
            OnRecv(event.GetSocket());
            break;
        }

        case wxSOCKET_LOST:
        {
            LogClient("Disconnected");
            sock->Close();
            sock->Discard();
            sock->Destroy();
            Client->Close();
            Client->Discard();
            Client->Destroy();
            Client = NULL;
            disconnected = true;
            break;
        }

        default:
        {
            LogClient("Unknown event");
            break;
        }
    }

}
