#ifndef SUDOKU_FRAME
#define SUDOKU_FRAME

#include <mainpane.h>
#include <gamepane.h>
#include <configpane.h>
#include <highscorepane.h>
#include <loadpane.h>

#include <string>

class Frame : public wxFrame
{
    public:
        virtual~ Frame(void);
        void Close(wxCloseEvent&);
        static Frame* GetFrame(void);
        void NewGame(void);
        void Replay(void);
        void StartNewGame(int, std::string);
        void Highscore(void);
        void Load(void);
        void LoadGame(std::string&);

        /*
         * The first parameter represents the current pane:
         *      0 - gamePane
         *      1 - configPane
         *      2 - loadPane
         *      3 - highscorePane
         */
        void SetMainPane(int, bool = true);

    private:
        /*
         * 0 - mainPane
         * 1 - configPane
         * 2 - gamePain
         * 3 - loadPane
         * 4 - highscorePane
         */
        int status = 0;
        static Frame *__frame;
        wxBoxSizer *sizer = NULL;
        MainPane *mainPane = NULL;
        GamePane *gamePane = NULL;
        ConfigPane *configPane = NULL;
        HighscorePane *highscorePane = NULL;
        LoadPane *loadPane = NULL;

        Frame(void);
        Frame(Frame const& copy);
        Frame& operator=(Frame const& copy);
};

#endif

