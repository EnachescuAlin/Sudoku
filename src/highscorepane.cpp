#include <wx/wx.h>
#include <highscorepane.h>
#include <frame.h>

#include <vector>
#include <string>
#include <fstream>

using namespace std;

HighscorePane::HighscorePane(wxFrame *frame) : wxPanel(frame)
{
    for (int i = 0; i < 10; i++)
    {
        staticText[i] = new wxStaticText(this, wxID_ANY, _T(""), wxPoint(25, 80 + i * 25));
        staticText[i + 10] = new wxStaticText(this, wxID_ANY, _T(""), wxPoint(220, 80 + i * 25));
    }

    staticLine1 = new wxStaticLine(this, wxID_ANY, wxPoint(25, 50), wxSize(350, 1));
    staticLine2 = new wxStaticLine(this, wxID_ANY, wxPoint(25, 360), wxSize(350, 1));

    staticLine1->SetBackgroundColour("black");
    staticLine2->SetBackgroundColour("black");

    highscore = new wxStaticText(this, wxID_ANY, _T("Highscore"), wxPoint(30, 15));
    wxFont font(15, wxDEFAULT, wxNORMAL, wxBOLD);
    highscore->SetFont(font);

    back = new wxButton(this, wxID_ANY, _T("Back"), wxPoint(30, 370));
    back->Bind(wxEVT_BUTTON, &HighscorePane::Back, this);
}

HighscorePane::~HighscorePane()
{
    for (int i = 0; i < 10; i++)
    {
        delete staticText[i];
        delete staticText[i + 10];
    }

    delete staticLine1;
    delete staticLine2;
    delete highscore;
    delete back;
}

void HighscorePane::Refresh() const
{
    vector<pair<string, unsigned>> top;
    string str;
    unsigned time;
    ifstream f(".sudoku/.highscore");

    while (!f.eof())
    {
        f >> str;
        f >> time;
        top.push_back(pair<string, unsigned>(str, time));
    }
    top.pop_back();

    f.close();

    wxString wxstr;

    for (size_t i = 0; i < top.size(); i++)
    {
        wxstr = "";
        wxstr << i + 1 << ". " << top[i].first;
        staticText[i]->SetLabel(wxstr);

        wxstr = "";
        wxstr << top[i].second;
        staticText[i + 10]->SetLabel(wxstr);
    }

    for (size_t i = top.size(); i < 10; i++)
    {
        wxstr = "";
        staticText[i + 10]->SetLabel(wxstr);
        wxstr << i + 1 << ". ";
        staticText[i]->SetLabel(wxstr);
    }

}

void HighscorePane::Back(wxCommandEvent& ev)
{
    Frame::GetFrame()->SetMainPane(3);
}

