#ifndef SUDOKU_HIGHSCORE_PANE
#define SUDOKU_HIGHSCORE_PANE

#include <wx/statline.h>

class HighscorePane : public wxPanel
{
    public:
        HighscorePane(wxFrame*);
        virtual~ HighscorePane();
        void Refresh(void) const;
        void Back(wxCommandEvent&);

    private:
        wxStaticText *staticText[20] = {NULL}, *highscore = NULL;
        wxButton *back = NULL;
        wxStaticLine *staticLine1 = NULL, *staticLine2 = NULL;
};

#endif
