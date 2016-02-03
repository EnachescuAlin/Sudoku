#include <wx/sizer.h>
#include <wx/wx.h>
#include <frame.h>

using namespace std;

Frame::Frame(void) : wxFrame(NULL, wxID_ANY, _T("Sudoku"), wxDefaultPosition, wxSize(400, 500))
{
    mainPane = new MainPane(this);
    configPane = new ConfigPane(this);
    gamePane = new GamePane(this);
    highscorePane = new HighscorePane(this);
    loadPane = new LoadPane(this);
    sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(mainPane, 1, wxEXPAND);
    sizer->Add(configPane, 1, wxEXPAND);
    sizer->Add(gamePane, 1, wxEXPAND);
    sizer->Add(highscorePane, 1, wxEXPAND);
    sizer->Add(loadPane, 1, wxEXPAND);
    sizer->Hide(loadPane);
    sizer->Hide(highscorePane);
    sizer->Hide(gamePane);
    sizer->Hide(configPane);
    sizer->Layout();

    SetSizer(sizer);
    SetAutoLayout(true);
    Show(true);

    Bind(wxEVT_CLOSE_WINDOW, &Frame::Close, this);
}

Frame* Frame::GetFrame(void)
{
    static Frame *__frame = new Frame();
    return __frame;
}

void Frame::NewGame(void)
{
    sizer->Hide(mainPane);
    sizer->Show(configPane);
    sizer->Layout();

    status = 1;
}

void Frame::StartNewGame(int difficulty, string name)
{
    gamePane->NewGame(difficulty, name);

    sizer->Hide(configPane);
    sizer->Show(gamePane);
    sizer->Layout();

    status = 2;
}

Frame::~Frame(void)
{
    // Segmentation fault
/*
    delete mainPane;
    delete configPane;
    delete gamePane;
    delete highscorePane;
    delete loadPane;
    delete sizer;
*/
}

void Frame::Close(wxCloseEvent& ev)
{
    Destroy();
}

void Frame::Replay(void)
{
    status = 2;

    sizer->Hide(mainPane);
    sizer->Show(gamePane);
    sizer->Layout();

    gamePane->Replay();
}

void Frame::Highscore(void)
{
    status = 4;

    highscorePane->Refresh();

    sizer->Hide(mainPane);
    sizer->Show(highscorePane);
    sizer->Layout();
}

void Frame::Load(void)
{
    status = 3;

    loadPane->Refresh();

    sizer->Hide(mainPane);
    sizer->Show(loadPane);
    sizer->Layout();
}

void Frame::LoadGame(string& fileName)
{
    gamePane->Load(fileName);

    status = 2;

    sizer->Hide(loadPane);
    sizer->Show(gamePane);
    sizer->Layout();

    gamePane->Replay();
}

void Frame::SetMainPane(int currentPane, bool enableReplay)
{
    if (currentPane == 0)
    {
        sizer->Hide(gamePane);
        mainPane->EnableReplay(enableReplay);
        goto end;
    }

    if (currentPane == 1)
    {
        sizer->Hide(configPane);
        goto end;
    }

    if (currentPane == 2)
    {
        sizer->Hide(loadPane);
        goto end;
    }

    if (currentPane == 3)
    {
        sizer->Hide(highscorePane);
        goto end;
    }

end:

    status = 0;

    sizer->Show(mainPane);
    sizer->Layout();
}

