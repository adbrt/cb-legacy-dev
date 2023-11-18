/***************************************************************
 * Name:      [FILENAME_PREFIX]App.cpp
 * Purpose:   Code for Application Class
 * Author:    [AUTHOR_NAME] ([AUTHOR_EMAIL])
 * Created:   [NOW]
 * Copyright: [AUTHOR_NAME] ([AUTHOR_WWW])
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "[FILENAME_PREFIX]App.h"
#include "[FILENAME_PREFIX]Main.h"

IMPLEMENT_APP([CLASS_PREFIX]App);

bool [CLASS_PREFIX]App::OnInit()
{
    [IF WXFRAME][CLASS_PREFIX]Frame* frame = new [CLASS_PREFIX]Frame(0L[IF NONE], _("wxWidgets Application Template")[ENDIF NONE]);
    [IF WINDOWS]frame->SetIcon(wxICON(aaaa)); // To Set App Icon[ENDIF WINDOWS]
    frame->Show();[ENDIF WXFRAME]
    [IF WXDIALOG][CLASS_PREFIX]Dialog* dlg = new [CLASS_PREFIX]Dialog(0L[IF NONE], _("wxWidgets Application Template")[ENDIF NONE]);
    [IF WINDOWS]dlg->SetIcon(wxICON(aaaa)); // To Set App Icon[ENDIF WINDOWS]
    dlg->Show();[ENDIF WXDIALOG]
    return true;
}
