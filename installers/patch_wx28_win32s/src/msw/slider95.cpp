#ifdef __BORLANDC__
/////////////////////////////////////////////////////////////////////////////
// Name:        slidermsw.cpp
// Purpose:     wxSlider
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: slidrmsw.cpp,v 1.28 2003/08/09 12:46:30 VS Exp $
// Copyright:   (c) Julian Smart
// Licence:       wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "slider95.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <stdio.h>
#endif

#include "wx/utils.h"
#include "wx/brush.h"
#include "wx/msw/slider95.h"
#include "wx/msw/private.h"

IMPLEMENT_DYNAMIC_CLASS(wxSlider, wxControl)

// Slider
wxSlider::wxSlider()
{
  m_staticValue = 0;
  m_staticMin = 0;
  m_staticMax = 0;
  m_pageSize = 1;
  m_lineSize = 1;
  m_rangeMax = 0;
  m_rangeMin = 0;
}

bool wxSlider::Create(wxWindow *parent, wxWindowID id,
           int value, int minValue, int maxValue,
           const wxPoint& pos,
           const wxSize& size, long style,
           const wxValidator& validator,
           const wxString& name)
{
    if ( (style & wxBORDER_MASK) == wxBORDER_DEFAULT )
        style |= wxBORDER_NONE;

  SetName(name);
#if wxUSE_VALIDATORS
  SetValidator(validator);
#endif // wxUSE_VALIDATORS

  if (parent) parent->AddChild(this);
  SetBackgroundColour(parent->GetBackgroundColour()) ;
  SetForegroundColour(parent->GetForegroundColour()) ;

  m_staticValue = 0;
  m_staticMin = 0;
  m_staticMax = 0;
  m_pageSize = 1;
  m_lineSize = 1;
  m_windowStyle = style;

  if ( id == -1 )
      m_windowId = (int)NewControlId();
  else
    m_windowId = id;

  int x = pos.x;
  int y = pos.y;
  int width = size.x;
  int height = size.y;

  // non-Win95 implementation

  long msStyle = SS_CENTER;

  WXDWORD exStyle = 0;
  msStyle |= MSWGetStyle(GetWindowStyle(), & exStyle) ;

  m_staticValue = (WXHWND) CreateWindowEx(exStyle, wxT("STATIC"), NULL,
                           msStyle,
                           0, 0, 0, 0, (HWND) parent->GetHWND(), (HMENU)NewControlId(),
                           wxGetInstance(), NULL);

  // Now create min static control
  wxString buf;
  buf.Printf(wxT("%d"), minValue);
  DWORD wstyle = STATIC_FLAGS;
  if ( m_windowStyle & wxCLIP_SIBLINGS )
        wstyle |= WS_CLIPSIBLINGS;
  m_staticMin = (WXHWND) CreateWindowEx(0, wxT("STATIC"), buf,
                         wstyle,
                         0, 0, 0, 0, (HWND) parent->GetHWND(), (HMENU)NewControlId(),
                         wxGetInstance(), NULL);

  msStyle = 0;
  if (m_windowStyle & wxSL_VERTICAL)
    msStyle = SBS_VERT | WS_CHILD | WS_VISIBLE | WS_TABSTOP ;
  else
    msStyle = SBS_HORZ | WS_CHILD | WS_VISIBLE | WS_TABSTOP ;

  HWND scroll_bar = CreateWindowEx(exStyle, wxT("SCROLLBAR"), wxEmptyString,
                         msStyle,
                         0, 0, 0, 0, (HWND) parent->GetHWND(), (HMENU)m_windowId,
                         wxGetInstance(), NULL);

  m_pageSize = (int)((maxValue-minValue)/10);
  m_rangeMax = maxValue;
  m_rangeMin = minValue;

  ::SetScrollRange(scroll_bar, SB_CTL, minValue, maxValue, FALSE);
  ::SetScrollPos(scroll_bar, SB_CTL, value, FALSE);
  ShowWindow(scroll_bar, SW_SHOW);

  m_hWnd = (WXHWND)scroll_bar;

  // Subclass again for purposes of dialog editing mode
  SubclassWin(GetHWND());

  // Finally, create max value static item
  buf.Printf(wxT("%d"), maxValue);
  wstyle = STATIC_FLAGS;
  if ( m_windowStyle & wxCLIP_SIBLINGS )
        wstyle |= WS_CLIPSIBLINGS;
  m_staticMax = (WXHWND) CreateWindowEx(0, wxT("STATIC"), buf,
                         wstyle,
                         0, 0, 0, 0, (HWND) parent->GetHWND(), (HMENU)NewControlId(),
                         wxGetInstance(), NULL);

  SetFont(parent->GetFont());

  if (GetFont().Ok())
  {
//    GetFont()->RealizeResource();
    if (GetFont().GetResourceHandle())
    {
        if ( m_staticMin )
              SendMessage((HWND)m_staticMin,WM_SETFONT,
                      (WPARAM)GetFont().GetResourceHandle(),0L);
        if ( m_staticMax )
              SendMessage((HWND)m_staticMax,WM_SETFONT,
                  (WPARAM)GetFont().GetResourceHandle(),0L);
          if (m_staticValue)
            SendMessage((HWND)m_staticValue,WM_SETFONT,
                    (WPARAM)GetFont().GetResourceHandle(),0L);
    }
  }

  SetSize(x, y, width, height);
  SetValue(value);

  return TRUE;
}

bool wxSlider::MSWOnScroll(int WXUNUSED(orientation), WXWORD wParam,
                              WXWORD pos, WXHWND control)
{
    int position = ::GetScrollPos((HWND)control, SB_CTL);

    int nScrollInc;
    wxEventType scrollEvent = wxEVT_NULL;
    switch ( wParam )
    {
        case SB_TOP:
            nScrollInc = m_rangeMax - position;
            scrollEvent = wxEVT_SCROLL_TOP;
            break;

        case SB_BOTTOM:
            nScrollInc = - position;
            scrollEvent = wxEVT_SCROLL_BOTTOM;
            break;

        case SB_LINEUP:
            nScrollInc = - GetLineSize();
            scrollEvent = wxEVT_SCROLL_LINEUP;
            break;

        case SB_LINEDOWN:
            nScrollInc = GetLineSize();
            scrollEvent = wxEVT_SCROLL_LINEDOWN;
            break;

        case SB_PAGEUP:
            nScrollInc = -GetPageSize();
            scrollEvent = wxEVT_SCROLL_PAGEUP;
            break;

        case SB_PAGEDOWN:
            nScrollInc = GetPageSize();
            scrollEvent = wxEVT_SCROLL_PAGEDOWN;
            break;

        case SB_THUMBTRACK:
        case SB_THUMBPOSITION:
#ifdef __WIN32__
            nScrollInc = (signed short)pos - position;
#else
            nScrollInc = pos - position;
#endif
            scrollEvent = wxEVT_SCROLL_THUMBTRACK;
            break;

        default:
            nScrollInc = 0;
    }

    if (nScrollInc == 0)
    {
        // no event...
        return FALSE;
    }

    int newPos = position + nScrollInc;

    if ( (newPos < GetMin()) || (newPos > GetMax()) )
    {
        // out of range - but we did process it
        return TRUE;
    }

    SetValue(newPos);

    wxScrollEvent event(scrollEvent, m_windowId);
    event.SetPosition(newPos);
    event.SetEventObject( this );
    GetEventHandler()->ProcessEvent(event);

    wxCommandEvent cevent( wxEVT_COMMAND_SLIDER_UPDATED, GetId() );
    cevent.SetInt( newPos );
    cevent.SetEventObject( this );

    return GetEventHandler()->ProcessEvent( cevent );
}

wxSlider::~wxSlider()
{
    if (m_staticMin)
      DestroyWindow((HWND) m_staticMin);
    if (m_staticMax)
      DestroyWindow((HWND) m_staticMax);
    if (m_staticValue)
      DestroyWindow((HWND) m_staticValue);
}

int wxSlider::GetValue() const
{
  return ::GetScrollPos(GetHwnd(), SB_CTL);
}

void wxSlider::SetValue(int value)
{
  ::SetScrollPos(GetHwnd(), SB_CTL, value, TRUE);
  if (m_staticValue)
  {
    wxString buf;
    buf.Printf(wxT("%d"), value);
    SetWindowText((HWND) m_staticValue, buf);
  }
}

void wxSlider::GetSize(int *width, int *height) const
{
  RECT rect;
  rect.left = -1; rect.right = -1; rect.top = -1; rect.bottom = -1;

  wxFindMaxSize(GetHWND(), &rect);

  if (m_staticMin)
    wxFindMaxSize(m_staticMin, &rect);
  if (m_staticMax)
    wxFindMaxSize(m_staticMax, &rect);
  if (m_staticValue)
    wxFindMaxSize(m_staticValue, &rect);

  *width = rect.right - rect.left;
  *height = rect.bottom - rect.top;
}

void wxSlider::GetPosition(int *x, int *y) const
{
  wxWindow *parent = GetParent();
  RECT rect;
  rect.left = -1; rect.right = -1; rect.top = -1; rect.bottom = -1;

  wxFindMaxSize(GetHWND(), &rect);

  if (m_staticMin)
    wxFindMaxSize(m_staticMin, &rect);
  if (m_staticMax)
    wxFindMaxSize(m_staticMax, &rect);
  if (m_staticValue)
    wxFindMaxSize(m_staticValue, &rect);

  // Since we now have the absolute screen coords,
  // if there's a parent we must subtract its top left corner
  POINT point;
  point.x = rect.left;
  point.y = rect.top;
  if (parent)
    ::ScreenToClient((HWND) parent->GetHWND(), &point);

  // We may be faking the client origin.
  // So a window that's really at (0, 30) may appear
  // (to wxWin apps) to be at (0, 0).
  if (GetParent())
  {
    wxPoint pt(GetParent()->GetClientAreaOrigin());
    point.x -= pt.x;
    point.y -= pt.y;
  }
  *x = point.x;
  *y = point.y;
}

// TODO one day, make sense of all this horros and replace it with a readable
//      DoGetBestSize()
void wxSlider::DoSetSize(int x, int y, int width, int height, int sizeFlags)
{
  int x1 = x;
  int y1 = y;
  int w1 = width;
  int h1 = height;

  int currentX, currentY;
  GetPosition(&currentX, &currentY);
  if (x == -1 && !(sizeFlags & wxSIZE_ALLOW_MINUS_ONE))
    x1 = currentX;
  if (y == -1 && !(sizeFlags & wxSIZE_ALLOW_MINUS_ONE))
    y1 = currentY;

  AdjustForParentClientOrigin(x1, y1, sizeFlags);

  wxChar buf[300];

  int x_offset = x;
  int y_offset = y;

  int cx;     // slider,min,max sizes
  int cy;
  int cyf;

  wxGetCharSize(GetHWND(), &cx, &cy, this->GetFont());

  if ((m_windowStyle & wxSL_VERTICAL) != wxSL_VERTICAL)
  {
    if ( m_windowStyle & wxSL_LABELS )
    {
    int min_len = 0;

    GetWindowText((HWND) m_staticMin, buf, 300);
    GetTextExtent(buf, &min_len, &cyf,NULL,NULL, & this->GetFont());

    int max_len = 0;

    GetWindowText((HWND) m_staticMax, buf, 300);
    GetTextExtent(buf, &max_len, &cyf,NULL,NULL, & this->GetFont());
    if (m_staticValue)
    {
      int new_width = (int)(wxMax(min_len, max_len));
      int valueHeight = (int)cyf;
#ifdef __WIN32__
      // For some reason, under Win95, the text edit control has
      // a lot of space before the first character
      new_width += 3*cx;
#endif
      MoveWindow((HWND) m_staticValue, x_offset, y_offset, new_width, valueHeight, TRUE);
      x_offset += new_width + cx;
    }

    MoveWindow((HWND) m_staticMin, x_offset, y_offset, (int)min_len, cy, TRUE);
    x_offset += (int)(min_len + cx);

    int slider_length = (int)(w1 - x_offset - max_len - cx);

    int slider_height = cy;

    // Slider must have a minimum/default length/height
    if (slider_length < 100)
      slider_length = 100;

    MoveWindow(GetHwnd(), x_offset, y_offset, slider_length, slider_height, TRUE);
    x_offset += slider_length + cx;

    MoveWindow((HWND) m_staticMax, x_offset, y_offset, (int)max_len, cy, TRUE);
    }
    else
    {
        // No labels
        if ( w1 < 0 )
            w1 = 200;
        if ( h1 < 0 )
            h1 = 20;
        MoveWindow(GetHwnd(), x1, y1, w1, h1, TRUE);
    }
  }
  else
  {
    if ( m_windowStyle & wxSL_LABELS )
    {
    int min_len;
    GetWindowText((HWND) m_staticMin, buf, 300);
    GetTextExtent(buf, &min_len, &cyf,NULL,NULL,& this->GetFont());

    int max_len;
    GetWindowText((HWND) m_staticMax, buf, 300);
    GetTextExtent(buf, &max_len, &cyf,NULL,NULL, & this->GetFont());

    if (m_staticValue)
    {
      int new_width = (int)(wxMax(min_len, max_len));
      int valueHeight = (int)cyf;
/*** Suggested change by George Tasker - remove this block...
#ifdef __WIN32__
      // For some reason, under Win95, the text edit control has
      // a lot of space before the first character
      new_width += 3*cx;
#endif
 ... and replace with following line: */
      new_width += cx;

      MoveWindow((HWND) m_staticValue, x_offset, y_offset, new_width, valueHeight, TRUE);
      y_offset += valueHeight;
    }

    MoveWindow((HWND) m_staticMin, x_offset, y_offset, (int)min_len, cy, TRUE);
    y_offset += cy;

    int slider_length = (int)(h1 - y_offset - cy - cy);

    // Use character height as an estimate of slider width (yes, width)
    int slider_width = cy;

    // Slider must have a minimum/default length
    if (slider_length < 100)
      slider_length = 100;

    MoveWindow(GetHwnd(), x_offset, y_offset, slider_width, slider_length, TRUE);
    y_offset += slider_length;

    MoveWindow((HWND) m_staticMax, x_offset, y_offset, (int)max_len, cy, TRUE);
    }
    else
    {
        // No labels
        if ( w1 < 0 )
            w1 = 20;
        if ( h1 < 0 )
            h1 = 200;
        MoveWindow(GetHwnd(), x1, y1, w1, h1, TRUE);
    }
  }
}

void wxSlider::SetRange(int minValue, int maxValue)
{
  m_rangeMin = minValue;
  m_rangeMax = maxValue;

  ::SetScrollRange(GetHwnd(), SB_CTL, m_rangeMin, m_rangeMax, TRUE);
  wxChar buf[40];
  if ( m_staticMin )
  {
      wxSprintf(buf, wxT("%d"), m_rangeMin);
      SetWindowText((HWND) m_staticMin, buf);
  }

  if ( m_staticMax )
  {
    wxSprintf(buf, wxT("%d"), m_rangeMax);
    SetWindowText((HWND) m_staticMax, buf);
  }
}

/*
WXHBRUSH wxSlider::OnCtlColor(WXHDC pDC, WXHWND pWnd, WXUINT nCtlColor,
            WXUINT message, WXWPARAM wParam, WXLPARAM lParam)
{
  if ( nCtlColor == CTLCOLOR_SCROLLBAR )
    return 0;

  // Otherwise, it's a static
  return wxControl::OnCtlColor(pDC, pWnd, nCtlColor, message, wParam, lParam);
}
*/

void wxSlider::SetPageSize(int pageSize)
{
  m_pageSize = pageSize;
}

int wxSlider::GetPageSize() const
{
  return m_pageSize;
}

void wxSlider::SetLineSize(int lineSize)
{
  m_lineSize = lineSize;
}

int wxSlider::GetLineSize() const
{
  return m_lineSize;
}

// Not yet implemented
void wxSlider::SetThumbLength(int WXUNUSED(lenPixels))
{
}

// Not yet implemented
int wxSlider::GetThumbLength() const
{
    return 0;
}

bool wxSlider::ContainsHWND(WXHWND hWnd) const
{
    return ( hWnd == GetStaticMin() || hWnd == GetStaticMax() || hWnd == GetEditValue() );
}

void wxSlider::Command (wxCommandEvent & event)
{
  SetValue (event.GetInt());
  ProcessCommand (event);
}

bool wxSlider::Show(bool show)
{
    wxWindow::Show(show);

    int cshow;
    if (show)
        cshow = SW_SHOW;
    else
        cshow = SW_HIDE;

    if(m_staticValue)
        ShowWindow((HWND) m_staticValue, (BOOL)cshow);
    if(m_staticMin)
        ShowWindow((HWND) m_staticMin, (BOOL)cshow);
    if(m_staticMax)
        ShowWindow((HWND) m_staticMax, (BOOL)cshow);
    return TRUE;
}
#endif
#ifndef __BORLANDC__
/////////////////////////////////////////////////////////////////////////////
// Name:        src/msw/slider.cpp
// Purpose:     wxSlider, using the Win95 (and later) trackbar control
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: slider95.cpp 41054 2006-09-07 19:01:45Z ABX $
// Copyright:   (c) Julian Smart 1998
//                  Vadim Zeitlin 2004
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_SLIDER

#include "wx/slider.h"

#ifndef WX_PRECOMP
    #include "wx/msw/wrapcctl.h" // include <commctrl.h> "properly"
    #include "wx/brush.h"
#endif

#include "wx/msw/subwin.h"

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// indices of labels in wxSlider::m_labels
enum
{
    SliderLabel_Min,
    SliderLabel_Max,
    SliderLabel_Value,
    SliderLabel_Last
};

// the gap between the slider and the labels, in pixels
static const int HGAP = 5;

// ----------------------------------------------------------------------------
// XTI
// ----------------------------------------------------------------------------

#if wxUSE_EXTENDED_RTTI
WX_DEFINE_FLAGS( wxSliderStyle )

wxBEGIN_FLAGS( wxSliderStyle )
    // new style border flags, we put them first to
    // use them for streaming out
    wxFLAGS_MEMBER(wxBORDER_SIMPLE)
    wxFLAGS_MEMBER(wxBORDER_SUNKEN)
    wxFLAGS_MEMBER(wxBORDER_DOUBLE)
    wxFLAGS_MEMBER(wxBORDER_RAISED)
    wxFLAGS_MEMBER(wxBORDER_STATIC)
    wxFLAGS_MEMBER(wxBORDER_NONE)

    // old style border flags
    wxFLAGS_MEMBER(wxSIMPLE_BORDER)
    wxFLAGS_MEMBER(wxSUNKEN_BORDER)
    wxFLAGS_MEMBER(wxDOUBLE_BORDER)
    wxFLAGS_MEMBER(wxRAISED_BORDER)
    wxFLAGS_MEMBER(wxSTATIC_BORDER)
    wxFLAGS_MEMBER(wxBORDER)

    // standard window styles
    wxFLAGS_MEMBER(wxTAB_TRAVERSAL)
    wxFLAGS_MEMBER(wxCLIP_CHILDREN)
    wxFLAGS_MEMBER(wxTRANSPARENT_WINDOW)
    wxFLAGS_MEMBER(wxWANTS_CHARS)
    wxFLAGS_MEMBER(wxFULL_REPAINT_ON_RESIZE)
    wxFLAGS_MEMBER(wxALWAYS_SHOW_SB )
    wxFLAGS_MEMBER(wxVSCROLL)
    wxFLAGS_MEMBER(wxHSCROLL)

    wxFLAGS_MEMBER(wxSL_HORIZONTAL)
    wxFLAGS_MEMBER(wxSL_VERTICAL)
    wxFLAGS_MEMBER(wxSL_AUTOTICKS)
    wxFLAGS_MEMBER(wxSL_LABELS)
    wxFLAGS_MEMBER(wxSL_LEFT)
    wxFLAGS_MEMBER(wxSL_TOP)
    wxFLAGS_MEMBER(wxSL_RIGHT)
    wxFLAGS_MEMBER(wxSL_BOTTOM)
    wxFLAGS_MEMBER(wxSL_BOTH)
    wxFLAGS_MEMBER(wxSL_SELRANGE)
    wxFLAGS_MEMBER(wxSL_INVERSE)

wxEND_FLAGS( wxSliderStyle )

IMPLEMENT_DYNAMIC_CLASS_XTI(wxSlider, wxControl,"wx/slider.h")

wxBEGIN_PROPERTIES_TABLE(wxSlider)
    wxEVENT_RANGE_PROPERTY( Scroll , wxEVT_SCROLL_TOP , wxEVT_SCROLL_CHANGED , wxScrollEvent )
    wxEVENT_PROPERTY( Updated , wxEVT_COMMAND_SLIDER_UPDATED , wxCommandEvent )

    wxPROPERTY( Value , int , SetValue, GetValue , 0, 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    wxPROPERTY( Minimum , int , SetMin, GetMin, 0 , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    wxPROPERTY( Maximum , int , SetMax, GetMax, 0 , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    wxPROPERTY( PageSize , int , SetPageSize, GetLineSize, 1 , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    wxPROPERTY( LineSize , int , SetLineSize, GetLineSize, 1 , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    wxPROPERTY( ThumbLength , int , SetThumbLength, GetThumbLength, 1 , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    wxPROPERTY_FLAGS( WindowStyle , wxSliderStyle , long , SetWindowStyleFlag , GetWindowStyleFlag , EMPTY_MACROVALUE , 0 /*flags*/ , wxT("Helpstring") , wxT("group")) // style
wxEND_PROPERTIES_TABLE()

wxBEGIN_HANDLERS_TABLE(wxSlider)
wxEND_HANDLERS_TABLE()

wxCONSTRUCTOR_8( wxSlider , wxWindow* , Parent , wxWindowID , Id , int , Value , int , Minimum , int , Maximum , wxPoint , Position , wxSize , Size , long , WindowStyle )
#else
IMPLEMENT_DYNAMIC_CLASS(wxSlider, wxControl)
#endif

// ============================================================================
// wxSlider implementation
// ============================================================================

// ----------------------------------------------------------------------------
// construction
// ----------------------------------------------------------------------------

void wxSlider::Init()
{
    m_labels = NULL;

    m_pageSize = 1;
    m_lineSize = 1;
    m_rangeMax = 0;
    m_rangeMin = 0;
    m_tickFreq = 0;

    m_isDragging = false;
}

bool
wxSlider::Create(wxWindow *parent,
                 wxWindowID id,
                 int value,
                 int minValue,
                 int maxValue,
                 const wxPoint& pos,
                 const wxSize& size,
                 long style,
                 const wxValidator& validator,
                 const wxString& name)
{
    // our styles are redundant: wxSL_LEFT/RIGHT imply wxSL_VERTICAL and
    // wxSL_TOP/BOTTOM imply wxSL_HORIZONTAL, but for backwards compatibility
    // reasons we can't really change it, instead try to infer the orientation
    // from the flags given to us here
    switch ( style & (wxSL_LEFT | wxSL_RIGHT | wxSL_TOP | wxSL_BOTTOM) )
    {
        case wxSL_LEFT:
        case wxSL_RIGHT:
            style |= wxSL_VERTICAL;
            break;

        case wxSL_TOP:
        case wxSL_BOTTOM:
            style |= wxSL_HORIZONTAL;
            break;

        case 0:
            // no specific direction, do we have at least the orientation?
            if ( !(style & (wxSL_HORIZONTAL | wxSL_VERTICAL)) )
            {
                // no, choose default
                style |= wxSL_BOTTOM | wxSL_HORIZONTAL;
            }
    };

    wxASSERT_MSG( !(style & wxSL_VERTICAL) || !(style & wxSL_HORIZONTAL),
                    _T("incompatible slider direction and orientation") );


    // initialize everything
    if ( !CreateControl(parent, id, pos, size, style, validator, name) )
        return false;

    // ensure that we have correct values for GetLabelsSize()
    m_rangeMin = minValue;
    m_rangeMax = maxValue;

    // create the labels first, so that our DoGetBestSize() could take them
    // into account
    //
    // note that we could simply create 3 wxStaticTexts here but it could
    // result in some observable side effects at wx level (e.g. the parent of
    // wxSlider would have 3 more children than expected) and so we prefer not
    // to do it like this
    if ( m_windowStyle & wxSL_LABELS )
    {
        m_labels = new wxSubwindows(SliderLabel_Last);

        HWND hwndParent = GetHwndOf(parent);
        for ( size_t n = 0; n < SliderLabel_Last; n++ )
        {
            (*m_labels)[n] = ::CreateWindow
                               (
                                    wxT("STATIC"),
                                    NULL,
                                    WS_CHILD | WS_VISIBLE | SS_CENTER,
                                    0, 0, 0, 0,
                                    hwndParent,
                                    (HMENU)NewControlId(),
                                    wxGetInstance(),
                                    NULL
                               );
        }

        m_labels->SetFont(GetFont());
    }

    // now create the main control too
    if ( !MSWCreateControl(TRACKBAR_CLASS, wxEmptyString, pos, size) )
        return false;

    // and initialize everything
    SetRange(minValue, maxValue);
    SetValue(value);
    SetPageSize((maxValue - minValue)/10);

    // we need to position the labels correctly if we have them and if
    // SetSize() hadn't been called before (when best size was determined by
    // MSWCreateControl()) as in this case they haven't been put in place yet
    if ( m_labels && size.x != wxDefaultCoord && size.y != wxDefaultCoord )
    {
        SetSize(size);
    }

    return true;
}

WXDWORD wxSlider::MSWGetStyle(long style, WXDWORD *exstyle) const
{
    WXDWORD msStyle = wxControl::MSWGetStyle(style, exstyle);

    // TBS_HORZ, TBS_RIGHT and TBS_BOTTOM are 0 but do include them for clarity
    msStyle |= style & wxSL_VERTICAL ? TBS_VERT : TBS_HORZ;

    if ( style & wxSL_BOTH )
    {
        // this fully specifies the style combined with TBS_VERT/HORZ above
        msStyle |= TBS_BOTH;
    }
    else // choose one direction
    {
        if ( style & wxSL_LEFT )
            msStyle |= TBS_LEFT;
        else if ( style & wxSL_RIGHT )
            msStyle |= TBS_RIGHT;
        else if ( style & wxSL_TOP )
            msStyle |= TBS_TOP;
        else if ( style & wxSL_BOTTOM )
            msStyle |= TBS_BOTTOM;
    }

    if ( style & wxSL_AUTOTICKS )
        msStyle |= TBS_AUTOTICKS;
    else
        msStyle |= TBS_NOTICKS;

    if ( style & wxSL_SELRANGE )
        msStyle |= TBS_ENABLESELRANGE;

    return msStyle;
}

wxSlider::~wxSlider()
{
    delete m_labels;
}

// ----------------------------------------------------------------------------
// event handling
// ----------------------------------------------------------------------------

bool wxSlider::MSWOnScroll(int WXUNUSED(orientation),
                           WXWORD wParam,
                           WXWORD WXUNUSED(pos),
                           WXHWND control)
{
    wxEventType scrollEvent;
    switch ( wParam )
    {
        case SB_TOP:
            scrollEvent = wxEVT_SCROLL_TOP;
            break;

        case SB_BOTTOM:
            scrollEvent = wxEVT_SCROLL_BOTTOM;
            break;

        case SB_LINEUP:
            scrollEvent = wxEVT_SCROLL_LINEUP;
            break;

        case SB_LINEDOWN:
            scrollEvent = wxEVT_SCROLL_LINEDOWN;
            break;

        case SB_PAGEUP:
            scrollEvent = wxEVT_SCROLL_PAGEUP;
            break;

        case SB_PAGEDOWN:
            scrollEvent = wxEVT_SCROLL_PAGEDOWN;
            break;

        case SB_THUMBTRACK:
            scrollEvent = wxEVT_SCROLL_THUMBTRACK;
            m_isDragging = true;
            break;

        case SB_THUMBPOSITION:
            if ( m_isDragging )
            {
                scrollEvent = wxEVT_SCROLL_THUMBRELEASE;
                m_isDragging = false;
            }
            else
            {
                // this seems to only happen when the mouse wheel is used: in
                // this case, as it might be unexpected to get THUMBRELEASE
                // without preceding THUMBTRACKs, we don't generate it at all
                // but generate CHANGED event because the control itself does
                // not send us SB_ENDSCROLL for whatever reason when mouse
                // wheel is used
                scrollEvent = wxEVT_SCROLL_CHANGED;
            }
            break;

        case SB_ENDSCROLL:
            scrollEvent = wxEVT_SCROLL_CHANGED;
            break;

        default:
            // unknown scroll event?
            return false;
    }

    int newPos = ValueInvertOrNot((int) ::SendMessage((HWND) control, TBM_GETPOS, 0, 0));
    if ( (newPos < GetMin()) || (newPos > GetMax()) )
    {
        // out of range - but we did process it
        return true;
    }

    SetValue(newPos);

    wxScrollEvent event(scrollEvent, m_windowId);
    event.SetPosition(newPos);
    event.SetEventObject( this );
    GetEventHandler()->ProcessEvent(event);

    wxCommandEvent cevent( wxEVT_COMMAND_SLIDER_UPDATED, GetId() );
    cevent.SetInt( newPos );
    cevent.SetEventObject( this );

    return GetEventHandler()->ProcessEvent( cevent );
}

void wxSlider::Command (wxCommandEvent & event)
{
    SetValue (event.GetInt());
    ProcessCommand (event);
}

// ----------------------------------------------------------------------------
// geometry stuff
// ----------------------------------------------------------------------------

wxRect wxSlider::GetBoundingBox() const
{
    // take care not to call our own functions which would call us recursively
    int x, y, w, h;
    wxSliderBase::DoGetPosition(&x, &y);
    wxSliderBase::DoGetSize(&w, &h);

    wxRect rect(x, y, w, h);
    if ( m_labels )
    {
        wxRect lrect = m_labels->GetBoundingBox();
        GetParent()->ScreenToClient(&lrect.x, &lrect.y);
        rect.Union(lrect);
    }

    return rect;
}

void wxSlider::DoGetSize(int *width, int *height) const
{
    wxRect rect = GetBoundingBox();

    if ( width )
        *width = rect.width;
    if ( height )
        *height = rect.height;
}

void wxSlider::DoGetPosition(int *x, int *y) const
{
    wxRect rect = GetBoundingBox();

    if ( x )
        *x = rect.x;
    if ( y )
        *y = rect.y;
}

int wxSlider::GetLabelsSize(int *width) const
{
    int cy;

    if ( width )
    {
        // find the max label width
        int wLabelMin, wLabelMax;
        GetTextExtent(Format(m_rangeMin), &wLabelMin, &cy);
        GetTextExtent(Format(m_rangeMax), &wLabelMax, &cy);

        *width = wxMax(wLabelMin, wLabelMax);
    }
    else
    {
        cy = GetCharHeight();
    }

    return EDIT_HEIGHT_FROM_CHAR_HEIGHT(cy);
}

void wxSlider::DoMoveWindow(int x, int y, int width, int height)
{
    // all complications below are because we need to position the labels,
    // without them everything is easy
    if ( !m_labels )
    {
        wxSliderBase::DoMoveWindow(x, y, width, height);
        return;
    }

    // be careful to position the slider itself after moving the labels as
    // otherwise our GetBoundingBox(), which is called from WM_SIZE handler,
    // would return a wrong result and wrong size would be cached internally
    if ( HasFlag(wxSL_VERTICAL) )
    {
        int wLabel;
        int hLabel = GetLabelsSize(&wLabel);

        int xLabel = HasFlag(wxSL_LEFT) ? x + width - wLabel : x;

        // position all labels: min at the top, value in the middle and max at
        // the bottom
        DoMoveSibling((HWND)(*m_labels)[SliderLabel_Min],
                     xLabel, y, wLabel, hLabel);

        DoMoveSibling((HWND)(*m_labels)[SliderLabel_Value],
                     xLabel, y + (height - hLabel)/2, wLabel, hLabel);

        DoMoveSibling((HWND)(*m_labels)[SliderLabel_Max],
                      xLabel, y + height - hLabel, wLabel, hLabel);

        // position the slider itself along the left/right edge
        wxSliderBase::DoMoveWindow(HasFlag(wxSL_LEFT) ? x : x + wLabel + HGAP,
                                   y + hLabel/2,
                                   width - wLabel - HGAP,
                                   height - hLabel);
    }
    else // horizontal
    {
        int wLabel;
        int hLabel = GetLabelsSize(&wLabel);

        int yLabel = HasFlag(wxSL_TOP) ? y + height - hLabel : y;

        // position all labels: min on the left, value in the middle and max to
        // the right
        DoMoveSibling((HWND)(*m_labels)[SliderLabel_Min],
                      x, yLabel, wLabel, hLabel);

        DoMoveSibling((HWND)(*m_labels)[SliderLabel_Value],
                      x + (width - wLabel)/2, yLabel, wLabel, hLabel);

        DoMoveSibling((HWND)(*m_labels)[SliderLabel_Max],
                      x + width - wLabel, yLabel, wLabel, hLabel);

        // position the slider itself along the top/bottom edge
        wxSliderBase::DoMoveWindow(x,
                                   HasFlag(wxSL_TOP) ? y : y + hLabel,
                                   width,
                                   height - hLabel);
    }
}

wxSize wxSlider::DoGetBestSize() const
{
    // these values are arbitrary
    static const int length = 100;
    static const int thumb = 24;
    static const int ticks = 8;

    int *width;
    wxSize size;
    if ( HasFlag(wxSL_VERTICAL) )
    {
        size.x = thumb;
        size.y = length;
        width = &size.x;

        if ( m_labels )
        {
            int wLabel;
            int hLabel = GetLabelsSize(&wLabel);

            // account for the labels
            size.x += HGAP + wLabel;

            // labels are indented relative to the slider itself
            size.y += hLabel;
        }
    }
    else // horizontal
    {
        size.x = length;
        size.y = thumb;
        width = &size.y;

        if ( m_labels )
        {
            // labels add extra height
            size.y += GetLabelsSize();
        }
    }

    // need extra space to show ticks
    if ( HasFlag(wxSL_TICKS) )
    {
        *width += ticks;

        // and maybe twice as much if we show them on both sides
        if ( HasFlag(wxSL_BOTH) )
            *width += ticks;
    }

    return size;
}

// ----------------------------------------------------------------------------
// slider-specific methods
// ----------------------------------------------------------------------------

int wxSlider::GetValue() const
{
    return ValueInvertOrNot(::SendMessage(GetHwnd(), TBM_GETPOS, 0, 0));
}

void wxSlider::SetValue(int value)
{
    ::SendMessage(GetHwnd(), TBM_SETPOS, (WPARAM)TRUE, (LPARAM)ValueInvertOrNot(value));

    if ( m_labels )
    {
        ::SetWindowText((*m_labels)[SliderLabel_Value], Format(value));
    }
}

void wxSlider::SetRange(int minValue, int maxValue)
{
    m_rangeMin = minValue;
    m_rangeMax = maxValue;

    ::SendMessage(GetHwnd(), TBM_SETRANGEMIN, TRUE, m_rangeMin);
    ::SendMessage(GetHwnd(), TBM_SETRANGEMAX, TRUE, m_rangeMax);

    if ( m_labels )
    {
        ::SetWindowText((*m_labels)[SliderLabel_Min], Format(ValueInvertOrNot(m_rangeMin)));
        ::SetWindowText((*m_labels)[SliderLabel_Max], Format(ValueInvertOrNot(m_rangeMax)));
    }
}

void wxSlider::SetTickFreq(int n, int pos)
{
    m_tickFreq = n;
    ::SendMessage( GetHwnd(), TBM_SETTICFREQ, (WPARAM) n, (LPARAM) pos );
}

void wxSlider::SetPageSize(int pageSize)
{
    ::SendMessage( GetHwnd(), TBM_SETPAGESIZE, (WPARAM) 0, (LPARAM) pageSize );
    m_pageSize = pageSize;
}

int wxSlider::GetPageSize() const
{
    return m_pageSize;
}

void wxSlider::ClearSel()
{
    ::SendMessage(GetHwnd(), TBM_CLEARSEL, (WPARAM) TRUE, (LPARAM) 0);
}

void wxSlider::ClearTicks()
{
    ::SendMessage(GetHwnd(), TBM_CLEARTICS, (WPARAM) TRUE, (LPARAM) 0);
}

void wxSlider::SetLineSize(int lineSize)
{
    m_lineSize = lineSize;
    ::SendMessage(GetHwnd(), TBM_SETLINESIZE, (WPARAM) 0, (LPARAM) lineSize);
}

int wxSlider::GetLineSize() const
{
    return (int)::SendMessage(GetHwnd(), TBM_GETLINESIZE, 0, 0);
}

int wxSlider::GetSelEnd() const
{
    return (int)::SendMessage(GetHwnd(), TBM_GETSELEND, 0, 0);
}

int wxSlider::GetSelStart() const
{
    return (int)::SendMessage(GetHwnd(), TBM_GETSELSTART, 0, 0);
}

void wxSlider::SetSelection(int minPos, int maxPos)
{
    ::SendMessage(GetHwnd(), TBM_SETSEL,
                  (WPARAM) TRUE /* redraw */,
                  (LPARAM) MAKELONG( minPos, maxPos) );
}

void wxSlider::SetThumbLength(int len)
{
    ::SendMessage(GetHwnd(), TBM_SETTHUMBLENGTH, (WPARAM) len, (LPARAM) 0);
}

int wxSlider::GetThumbLength() const
{
    return (int)::SendMessage( GetHwnd(), TBM_GETTHUMBLENGTH, 0, 0);
}

void wxSlider::SetTick(int tickPos)
{
    ::SendMessage( GetHwnd(), TBM_SETTIC, (WPARAM) 0, (LPARAM) tickPos );
}

// ----------------------------------------------------------------------------
// composite control methods
// ----------------------------------------------------------------------------

WXHWND wxSlider::GetStaticMin() const
{
    return m_labels ? (WXHWND)(*m_labels)[SliderLabel_Min] : NULL;
}

WXHWND wxSlider::GetStaticMax() const
{
    return m_labels ? (WXHWND)(*m_labels)[SliderLabel_Max] : NULL;
}

WXHWND wxSlider::GetEditValue() const
{
    return m_labels ? (WXHWND)(*m_labels)[SliderLabel_Value] : NULL;
}

WX_FORWARD_STD_METHODS_TO_SUBWINDOWS(wxSlider, wxSliderBase, m_labels)

#endif // wxUSE_SLIDER

#endif