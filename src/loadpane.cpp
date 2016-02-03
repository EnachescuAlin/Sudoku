#include <wx/wx.h>
#include <loadpane.h>
#include <frame.h>

#include <fstream>
#include <vector>
#include <string>

using namespace std;

LoadPane::LoadPane(wxFrame *frame) : wxPanel(frame)
{
    back = new wxButton(this, wxID_ANY, _T("Back"), wxPoint(250, 25));
    load = new wxButton(this, wxID_ANY, _T("Load"), wxPoint(250, 75));

    back->Bind(wxEVT_BUTTON, &LoadPane::Back, this);
    load->Bind(wxEVT_BUTTON, &LoadPane::Load, this);

    list = new wxListBox(this, wxID_ANY, wxPoint(25, 25), wxSize(200, 425));
    list->Bind(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, &LoadPane::Load, this);
}

LoadPane::~LoadPane()
{
    delete back;
    delete load;
    delete list;
}

void LoadPane::Back(wxCommandEvent& ev)
{
    Frame::GetFrame()->SetMainPane(2);
}

void LoadPane::Load(wxCommandEvent& ev)
{
    int n = list->GetSelection();

    if (n == wxNOT_FOUND)
        return;

    string str(list->GetString(n).mb_str());
    Frame::GetFrame()->LoadGame(str);
}

void LoadPane::Refresh(void)
{
    list->Clear();

    ifstream f(".sudoku/.save");
    vector<string> vec;
    string str;
    wxString wxstr;

    while (!f.eof())
    {
        f >> str;
        vec.push_back(str);
    }
    vec.pop_back();

    f.close();

    for (auto& i : vec)
    {
        wxstr = "";
        wxstr << i.c_str();
        list->Append(wxstr);
    }
}

