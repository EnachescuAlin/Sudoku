#include "sudoku.h"
#include <cstdlib>
#include <ctime>


Sudoku::Sudoku()
{
    board = new Board();
}

Sudoku::~Sudoku()
{
    delete board;
}

/*
 * 0 - easy
 * 1 - medium
 * 2 - hard
 * 3 - very hard
 */
#define EASY_MIN        36
#define EASY_MAX        40
#define MEDIUM_MIN      32
#define MEDIUM_MAX      35
#define HARD_MIN        28
#define HARD_MAX        31
#define VERYHARD_MIN    22
#define VERYHARD_MAX    27

void Sudoku::Generates(int difficulty)
{
    this->difficulty = difficulty;

    int min, max;
    switch (difficulty)
    {
        case 0:
            min = EASY_MIN;
            max = EASY_MAX;
            break;
        case 1:
            min = MEDIUM_MIN;
            max = MEDIUM_MAX;
            break;
        case 2:
            min = HARD_MIN;
            max = HARD_MAX;
            break;
        case 3:
            min = VERYHARD_MIN;
            max = VERYHARD_MAX;
            break;
    }

    board->Generate();

    srand(time(NULL));
    int cells = 81 - (rand() % (max - min) + min + 1), x, y;
    for (int i = 0; i < cells; i++)
    {
        x = rand() % 9;
        y = rand() % 9;
        if (board->IsFreeCell(x, y))
            i--;
        else
            board->RemoveDigit(x, y, false);
    }

}

int Sudoku::GetDifficulty(void) const
{
    return difficulty;
}

int Sudoku::GetDigit(int& x, int& y) const
{
    return board->GetDigit(x, y);
}

int Sudoku::GetType(int& x, int& y) const
{
    return board->GetType(x, y);
}

bool Sudoku::GetValidation(int& x, int& y) const
{
    return board->GetValidation(x, y);
}

void Sudoku::GetCoord(int& x, int& y) const
{
    x = posX;
    y = posY;
}

void Sudoku::Move(int direction)
{
    if (posX == -1 && posY == -1)
    {
        board->GetFirstPosition(posX, posY);
        return;
    }

    if (direction == 1)
        board->MoveRight(posX, posY);
    if (direction == 2)
        board->MoveLeft(posX, posY);
    if (direction == 3)
        board->MoveUp(posX, posY);
    if (direction == 4)
        board->MoveDown(posX, posY);
}

bool Sudoku::Set(int number)
{
    if (gameOver)
        return true;

    board->PutDigit(number, posY, posX, 0);

    if (board->GameOver())
        gameOver = true;

    return gameOver;
}

void Sudoku::SetShown(bool shown)
{
    this->shown = shown;
}

bool Sudoku::GetShown(void) const
{
    return shown;
}

bool Sudoku::GetGameStatus(void) const
{
    return gameOver;
}

void Sudoku::Remove(void)
{
    board->RemoveDigit(posY, posX);
}

bool Sudoku::IncrementTime(void)
{
    _time++;
    return gameOver;
}

unsigned long long Sudoku::GetTime(void) const
{
    return _time;
}

Board* Sudoku::GetBoard(void) const
{
    return board;
}

void Sudoku::SetStatus(bool gameOver)
{
    this->gameOver = gameOver;
}

void Sudoku::SetCoord(int x, int y)
{
    posX = x;
    posY = y;
}

void Sudoku::SetDifficulty(int difficulty)
{
    this->difficulty = difficulty;
}

void Sudoku::SetTime(unsigned long long time)
{
    _time = time;
}

