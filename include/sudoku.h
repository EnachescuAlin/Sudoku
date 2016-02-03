#ifndef SUDOKU
#define SUDOKU

#include <board.h>

class Sudoku
{
    public:
        Sudoku();
        virtual~ Sudoku();
        void Generates(int);
        int GetDigit(int&, int&) const;
        int GetType(int&, int&) const;
        bool GetValidation(int&, int&) const;
        void GetCoord(int&, int&) const;
        bool IncrementTime(void);
        unsigned long long GetTime(void) const;
        bool GetShown(void) const;
        bool GetGameStatus(void) const;
        Board* GetBoard(void) const;
        int GetDifficulty(void) const;

        void SetCoord(int, int);
        void SetDifficulty(int);
        void SetTime(unsigned long long);
        void SetStatus(bool);
        void SetShown(bool);

        /*
         * 1 -> right
         * 2 -> left
         * 3 -> up
         * 4 -> down
         */
        void Move(int);
        bool Set(int);
        void Remove(void);

    private:
        Board *board;
        int posX = -1, posY = -1, difficulty;
        unsigned long long _time = 0;
        bool gameOver = false, shown = false;
};

#endif

