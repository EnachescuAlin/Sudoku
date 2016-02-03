#ifndef SUDOKU_BOARD
#define SUDOKU_BOARD

class Board
{
    public:
        Board();
        virtual~ Board();
        void PutDigit(int number, int x, int y, int type = 0);
        void RemoveDigit(int x, int y, bool user = true);
        int GetDigit(int x, int y) const;
        int GetType(int x, int y) const;
        bool GetValidation(int x, int y) const;
        bool IsFreeCell(int& x, int& y) const;
        void GetFirstPosition(int&, int&) const;
        void MoveRight(int&, int&) const;
        void MoveLeft(int&, int&) const;
        void MoveUp(int&, int&) const;
        void MoveDown(int&, int&) const;
        bool Generate(void);
        bool GameOver(void) const;

    private:
        int _board[9][9] = {{0}};
        int _type[9][9], freeCells = 0;
        bool _isRight[9][9];

        void SearchMistakes();
        bool Solve(int, int, unsigned [9][9][9], unsigned [9],
                   unsigned [9], unsigned [9]);
};

#endif

