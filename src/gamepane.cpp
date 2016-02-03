#include <wx/wx.h>
#include <wx/timer.h>
#include <gamepane.h>
#include <frame.h>

#include <vector>
#include <fstream>

using namespace std;

GamePane::GamePane(wxFrame *parent) : wxPanel(parent)
{
    timer = new wxTimer(this, 1);

    wxSize size = wxButton::GetDefaultSize();
    back = new wxButton(this, wxID_ANY, _T("Back"),
                        wxPoint(390 - size.GetWidth(), 400));
    save = new wxButton(this, wxID_ANY, _T("Save"),
                        wxPoint(390 - size.GetWidth(),
                                400 + size.GetHeight() + 10));

    back->Bind(wxEVT_BUTTON, &GamePane::Back, this);
    save->Bind(wxEVT_BUTTON, &GamePane::Save, this);

    Bind(wxEVT_PAINT, &GamePane::PaintEvent, this);
    Bind(wxEVT_TIMER, &GamePane::Timer, this);
}

void GamePane::NewGame(int difficulty, string name)
{
    if (sudoku)
        delete sudoku;

    sudoku = new Sudoku();
    sudoku->Generates(difficulty);
    this->name = name;

    timer->Start(1000);
    back->SetFocus();

    Show();
}

GamePane::~GamePane()
{
    if (sudoku)
        delete sudoku;
    delete timer;
    delete back;
    delete save;
}

void GamePane::Show(void)
{
    Bind(wxEVT_CHAR_HOOK, &GamePane::KeyPressed, this);
}

void GamePane::Hide(void)
{
    Unbind(wxEVT_CHAR_HOOK, &GamePane::KeyPressed, this);
}

void GamePane::Back(wxCommandEvent& ev)
{
    timer->Stop();
    Hide();
    Frame::GetFrame()->SetMainPane(0, !sudoku->GetGameStatus());
}

void GamePane::Replay(void)
{
    back->SetFocus();
    Show();
    timer->Start(1000);
}

void GamePane::Save(wxCommandEvent& ev)
{
    ifstream f(".sudoku/.save");
    vector<string> vec;
    string str;

    while (!f.eof())
    {
        f >> str;
        vec.push_back(str);
    }
    vec.pop_back();

    f.close();

    bool found = false;
    for (auto& i : vec)
        if (i == name)
            found = true;

    if (!found)
    {
        ofstream g(".sudoku/.save", ofstream::out | ofstream::app);
        g << name << '\n';
        g.close();
    }

    string fileName = ".sudoku/." + name + ".sudoku";
    ofstream file(fileName.c_str(), ofstream::out | ofstream::binary);

    file.write((const char*)sudoku->GetBoard(), sizeof(Board));

    int posX, posY, difficulty;
    sudoku->GetCoord(posX, posY);
    unsigned long long int time = sudoku->GetTime();
    bool gameOver = sudoku->GetGameStatus();
    bool shown = sudoku->GetShown();

    file.write((const char*)&posX, sizeof(int));
    file.write((const char*)&posY, sizeof(int));
    file.write((const char*)&difficulty, sizeof(int));
    file.write((const char*)&time, sizeof(unsigned long long int));
    file.write((const char*)&gameOver, sizeof(bool));
    file.write((const char*)&shown, sizeof(bool));

    file.close();
}

void GamePane::Load(string& fileName)
{
    name = fileName;
    fileName = ".sudoku/." + fileName;
    fileName += ".sudoku";

    ifstream file(fileName.c_str(), ifstream::in | ifstream::binary);

    if (sudoku)
        delete sudoku;
    sudoku = new Sudoku();

    int posX, posY, difficulty;
    unsigned long long int time;
    bool gameOver, shown;

    file.read((char*)sudoku->GetBoard(), sizeof(Board));
    file.read((char*)&posX, sizeof(int));
    file.read((char*)&posY, sizeof(int));
    file.read((char*)&difficulty, sizeof(int));
    file.read((char*)&time, sizeof(unsigned long long int));
    file.read((char*)&gameOver, sizeof(bool));
    file.read((char*)&shown, sizeof(bool));

    sudoku->SetCoord(posX, posY);
    sudoku->SetDifficulty(difficulty);
    sudoku->SetTime(time);
    sudoku->SetStatus(gameOver);
    sudoku->SetShown(shown);

    file.close();
}

void GamePane::Timer(wxTimerEvent& ev)
{
    if (sudoku->IncrementTime())
        timer->Stop();
    DrawTime();
}

void GamePane::PaintEvent(wxPaintEvent &evt)
{
    if (sudoku == NULL)
        return;
    wxPaintDC dc(this);
    Render(dc);
    DrawTime();
}

void GamePane::DrawTime(void)
{
    wxPaintDC dc(this);
    dc.SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxString str;
    str << "Time:  ";
    str << sudoku->GetTime();

    dc.SetPen(wxNullPen);
    dc.SetBrush(*wxLIGHT_GREY_BRUSH);
    dc.DrawRectangle(10, 430, 200, 50);
    dc.DrawText(str, 10, 430);
}

void GamePane::PaintNow(void)
{
    if (sudoku == NULL)
        return;
    wxPaintDC dc(this);
    Render(dc);
}

void GamePane::GameOver(void)
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

    bool added = false;
    for (auto i = top.begin(); i != top.end(); i++)
        if (i->second > sudoku->GetTime())
        {
            top.insert(i, pair<string, unsigned>(name, sudoku->GetTime()));
            added = true;
            break;
        }

    if (!added)
    {
        top.push_back(pair<string, unsigned>(name, sudoku->GetTime()));
    }

    ofstream g(".sudoku/.highscore");
    int j = 0;
    for (auto i = top.begin(); i != top.end(); i++, j++)
        if (j < 10)
        {
            g << i->first << " " << i->second << "\n";
        }
    g.close();

    wxMessageBox(_T("You win!!!"), _T("Game over"));
}

void GamePane::KeyPressed(wxKeyEvent& ev)
{
    int key = ev.GetKeyCode();
    switch (key)
    {
        case WXK_RIGHT:
            sudoku->Move(1);
            break;
        case WXK_LEFT:
            sudoku->Move(2);
            break;
        case WXK_UP:
            sudoku->Move(3);
            break;
        case WXK_DOWN:
            sudoku->Move(4);
            break;
        case WXK_BACK:
            sudoku->Remove();
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (sudoku->Set(key - '0') && !sudoku->GetShown())
            {
                GameOver();
                sudoku->SetShown(true);
                save->Enable(false);
            }
    }

    PaintNow();
}

void GamePane::Render(wxDC &dc)
{
    DrawBlock(dc, 10, 10);
    DrawBlock(dc, 140, 10);
    DrawBlock(dc, 270, 10);

    DrawBlock(dc, 10, 140);
    DrawBlock(dc, 140, 140);
    DrawBlock(dc, 270, 140);

    DrawBlock(dc, 10, 270);
    DrawBlock(dc, 140, 270);
    DrawBlock(dc, 270, 270);

    dc.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    int x, y = 10, a, b;

    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0 && i != 0)
            y += 10;

        x = 10;
        for (int j = 0; j < 9; j++)
        {
            int type  = sudoku->GetType(i, j);
            int digit = sudoku->GetDigit(i, j);
            bool validation = sudoku->GetValidation(i, j);
            bool color = type == 1 ? true : false;

            if (j % 3 == 0 && j != 0)
                x += 10;

            switch (j % 3)
            {
                case 0:
                    if (i % 3 == 0)
                    {
                        DrawRectangle(dc, x + 3, y + 3, 36, 36, color);
                    }
                    else
                    {
                        if (i % 3 == 1)
                        {
                            DrawRectangle(dc, x + 3, y + 1, 36, 38, color);
                        }
                        else
                        {
                            DrawRectangle(dc, x + 3, y + 1, 36, 37, color);
                        }
                    }
                    break;

                case 1:
                    if (i % 3 == 0)
                    {
                        DrawRectangle(dc, x + 1, y + 3, 38, 36, color);
                    }
                    else
                    {
                        if (i % 3 == 1)
                        {
                            DrawRectangle(dc, x + 1, y + 1, 38, 38, color);
                        }
                        else
                        {
                            DrawRectangle(dc, x + 1, y + 1, 38, 37, color);
                        }
                    }
                    break;
                case 2:
                    if (i % 3 == 0)
                    {
                        DrawRectangle(dc, x + 1, y + 3, 37, 36, color);
                    }
                    else
                    {
                        if (i % 3 == 1)
                        {
                            DrawRectangle(dc, x + 1, y + 1, 37, 38, color);
                        }
                        else
                        {
                            DrawRectangle(dc, x + 1, y + 1, 37, 37, color);
                        }
                    }
                    break;
            }

            if (digit != 0)
            {
                if (validation)
                    dc.SetTextForeground(*wxBLACK);
                else
                    dc.SetTextForeground(*wxRED);

                wxString str;
                str << digit;
                dc.GetTextExtent(str, &a, &b);
                dc.DrawText(str, (40 - a) / 2 + x, (40 - b) / 2 + y);
            }

            x += 40;
        }
        y += 40;
    }

    DrawCurrentPosition(dc);
}

void GamePane::DrawCurrentPosition(wxDC& dc)
{
    int x, y, _x = 10, _y = 10;
    sudoku->GetCoord(x, y);

    if (x < 0 || x > 8 || y < 0 || y > 8)
        return;

    _x += (x / 3) * 10 + x * 40;
    _y += (y / 3) * 10 + y * 40;

    dc.SetPen(wxPen(*wxBLUE, 3));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(_x, _y, 40, 40);
}

void GamePane::DrawBlock(wxDC& dc, int x, int y)
{
    dc.SetPen(wxPen(wxColor(0, 0, 0), 5));

    dc.DrawLine(x, y, x + 120, y);
    dc.DrawLine(x, y, x, y + 120);
    dc.DrawLine(x + 120, y, x + 120, y + 120);
    dc.DrawLine(x, y + 120, x + 120, y + 120);

    dc.SetPen(wxPen(wxColor(0, 0, 0), 2));

    dc.DrawLine(x + 40, y, x + 40, y + 120);
    dc.DrawLine(x + 80, y, x + 80, y + 120);
    dc.DrawLine(x, y + 40, x + 120, y + 40);
    dc.DrawLine(x, y + 80, x + 120, y + 80);
}

void GamePane::DrawRectangle(wxDC& dc, int x, int y, int w, int h, bool color)
{
    if (color)
        dc.SetBrush(*wxGREY_BRUSH);
    else
        dc.SetBrush(*wxWHITE_BRUSH);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(x, y, w, h);
}

