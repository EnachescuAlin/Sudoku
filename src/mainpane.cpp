#include <wx/wx.h>

#include <mainpane.h>
#include <frame.h>

MainPane::MainPane(wxFrame *frame) : wxPanel(frame)
{
    wxSize a = wxButton::GetDefaultSize();
    int h = a.GetHeight(), w = a.GetWidth();
    int x = (400 - w) / 2, y = (470 - 4 * h) / 2;

    h += 10;

    replay = new wxButton(this, wxID_ANY, _T("Replay"), wxPoint(x, y));
    replay->Enable(false);
    replay->Bind(wxEVT_BUTTON, &MainPane::Replay, this);

    start = new wxButton(this, wxID_ANY, _T("New game"), wxPoint(x, y + h));
    start->Bind(wxEVT_BUTTON, &MainPane::Start, this);

    load = new wxButton(this, wxID_ANY, _T("Load"), wxPoint(x, y + 2 * h));
    load->Bind(wxEVT_BUTTON, &MainPane::Load, this);

    highscore = new wxButton(this, wxID_ANY, _T("Highscore"), wxPoint(x, y + 3 * h));
    highscore->Bind(wxEVT_BUTTON, &MainPane::Highscore, this);
}

MainPane::~MainPane()
{
    delete start;
    delete load;
    delete highscore;
    delete replay;
}

void MainPane::EnableReplay(bool status)
{
    replay->Enable(status);

    if (status)
        replay->SetFocus();
    else
        start->SetFocus();
}

void MainPane::Replay(wxCommandEvent& ev)
{
    Frame::GetFrame()->Replay();
}

void MainPane::Start(wxCommandEvent& ev)
{
    Frame::GetFrame()->NewGame();
}

void MainPane::Load(wxCommandEvent& ev)
{
    Frame::GetFrame()->Load();
}

void MainPane::Highscore(wxCommandEvent& ev)
{
    Frame::GetFrame()->Highscore();
}

