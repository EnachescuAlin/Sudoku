#ifndef SUDOKU_LOAD_PANE
#define SUDOKU_LOAD_PANE

class LoadPane : public wxPanel
{
    public:
        LoadPane(wxFrame*);
        virtual~ LoadPane();
        void Load(wxCommandEvent&);
        void Back(wxCommandEvent&);
        void Refresh(void);

    private:
        wxButton *load, *back;
        wxListBox *list;
};

#endif

