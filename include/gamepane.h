#ifndef SUDOKU_GAME_PANE
#define SUDOKU_GAME_PANE

#include <sudoku.h>
#include <string>

class GamePane : public wxPanel
{
    public:
        GamePane(wxFrame*);
        virtual~ GamePane();
        void PaintEvent(wxPaintEvent&);
        void Render(wxDC&);
        void PaintNow(void);
        void KeyPressed(wxKeyEvent&);
        void Timer(wxTimerEvent&);
        void Back(wxCommandEvent&);
        void Save(wxCommandEvent&);
        void Load(std::string&);
        void Replay(void);
        void NewGame(int, std::string);

    private:
        void DrawBlock(wxDC&, int, int);
        void DrawRectangle(wxDC&, int, int, int, int, bool = false);
        void DrawCurrentPosition(wxDC&);
        void DrawTime(void);
        void GameOver(void);
        void Show(void);
        void Hide(void);

        wxButton *back = NULL, *save = NULL;
        wxTimer *timer = NULL;
        Sudoku *sudoku = NULL;
        std::string name;
};

#endif

