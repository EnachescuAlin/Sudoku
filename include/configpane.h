#ifndef SUDOKU_CONFIG_PANE
#define SUDOKU_CONFIG_PANE

class ConfigPane : public wxPanel
{
    public:
        ConfigPane(wxFrame*);
        virtual~ ConfigPane();
        void Start(wxCommandEvent&);
        void Back(wxCommandEvent&);

    private:
        wxRadioBox *radio;
        wxButton *start, *back;
        wxTextCtrl *text;
};

#endif

