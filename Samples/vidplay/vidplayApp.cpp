/***************************************************************
 * Name:      vidplayApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2023-11-12
 * Copyright:  ()
 * License:
 **************************************************************/

#include "vidplayApp.h"

//(*AppHeaders
#include "vidplayMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(vidplayApp);

bool vidplayApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        vidplayFrame* Frame = new vidplayFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
