#ifndef SUDOKU_MAIN_FRAME
#define SUDOKU_MAIN_FRAME

class MainPane : public wxPanel
{
    public:
        MainPane(wxFrame*);
        virtual~ MainPane();
        void Start(wxCommandEvent&);
        void Load(wxCommandEvent&);
        void Highscore(wxCommandEvent&);
        void Replay(wxCommandEvent&);
        void EnableReplay(bool);
    private:
        wxButton *start, *highscore, *load, *replay;
};

#endif

