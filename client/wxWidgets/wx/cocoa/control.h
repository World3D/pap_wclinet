/////////////////////////////////////////////////////////////////////////////
// Name:        wx/cocoa/control.h
// Purpose:     wxControl class
// Author:      David Elliott
// Modified by:
// Created:     2003/02/15
// RCS-ID:      $Id: 
// Copyright:   (c) 2003 David Elliott
// Licence:   	wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef __WX_COCOA_CONTROL_H__
#define __WX_COCOA_CONTROL_H__

#include "wx/cocoa/NSControl.h"

// ========================================================================
// wxControl
// ========================================================================

class WXDLLEXPORT wxControl : public wxControlBase, public wxCocoaNSControl
{
    DECLARE_ABSTRACT_CLASS(wxControl)
    WX_DECLARE_COCOA_OWNER(NSControl,NSView,NSView)
    DECLARE_EVENT_TABLE()
// ------------------------------------------------------------------------
// initialization
// ------------------------------------------------------------------------
public:
    wxControl() {}
    wxControl(wxWindow *parent, wxWindowID winid,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxControlNameStr)
    {
        Create(parent, winid, pos, size, style, validator, name);
    }

    bool Create(wxWindow *parent, wxWindowID winid,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxControlNameStr);
    virtual ~wxControl();

// ------------------------------------------------------------------------
// Implementation
// ------------------------------------------------------------------------
public:

    // implementation from now on
    // --------------------------

    void OnEraseBackground(wxEraseEvent& event);
   
    virtual void Command(wxCommandEvent& event) { ProcessCommand(event); }

    // Calls the callback and appropriate event handlers
    bool ProcessCommand(wxCommandEvent& event);

    // Enables the control
    virtual void CocoaSetEnabled(bool enable);
protected:
    virtual wxSize DoGetBestSize() const;
};

#endif // __WX_COCOA_CONTROL_H__
