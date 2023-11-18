/***************************************************************
 * Name:      tcptestApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2023-11-10
 * Copyright:  ()
 * License:
 **************************************************************/

#include "tcptestApp.h"

//(*AppHeaders
#include "tcptestMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(tcptestApp);

bool tcptestApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        tcptestFrame* Frame = new tcptestFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
