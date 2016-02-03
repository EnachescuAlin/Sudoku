#include <wx/wxprec.h>
#include <wx/wx.h>

#include <frame.h>
#include <main.h>

IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    SetTopWindow(Frame::GetFrame());

    return true;
}

