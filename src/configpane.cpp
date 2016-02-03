#include <wx/wx.h>
#include <configpane.h>
#include <frame.h>

ConfigPane::ConfigPane(wxFrame *frame) : wxPanel(frame)
{
    wxString choices[4];
    choices[0] << "Easy";
    choices[1] << "Medium";
    choices[2] << "Hard";
    choices[3] << "Very hard";

    radio = new wxRadioBox(this, wxID_ANY, _T("Difficulty"), wxPoint(10, 10),
                           wxDefaultSize, 4, choices, 1);

    text = new wxTextCtrl(this, wxID_ANY, _T("Name"),
                          wxPoint(10, radio->GetSize().GetHeight() + 20));
    text->SetMaxLength(15);

    int x, y = radio->GetSize().GetHeight() + text->GetSize().GetHeight() + 30;
    x = (400 - (2 * wxButton::GetDefaultSize().GetWidth()) - 40) / 2;

    start = new wxButton(this, wxID_ANY, _T("Start"), wxPoint(x, y));
    start->Bind(wxEVT_BUTTON, &ConfigPane::Start, this);

    x += 20 + wxButton::GetDefaultSize().GetWidth();
    back = new wxButton(this, wxID_ANY, _T("Back"), wxPoint(x + 40, y));
    back->Bind(wxEVT_BUTTON, &ConfigPane::Back, this);
}

ConfigPane::~ConfigPane()
{
    delete radio;
    delete text;
    delete back;
    delete start;
}

void ConfigPane::Start(wxCommandEvent& ev)
{
    Frame::GetFrame()->StartNewGame(radio->GetSelection(),
                                    text->GetLineText(0).ToStdString());
}

void ConfigPane::Back(wxCommandEvent& ev)
{
    Frame::GetFrame()->SetMainPane(1);
}

