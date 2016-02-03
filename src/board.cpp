#include <board.h>
#include <algorithm>
#include <cmath>
#include <ctime>

#include <iostream>
using namespace std;

Board::Board()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            _type[i][j] = 1;
            _isRight[i][j] = true;
        }
}

Board::~Board()
{

}

void Board::SearchMistakes()
{
    int frequency[10], frequency2[10];

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            _isRight[i][j] = true;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            frequency[j]  = -1;
            frequency2[j] = -1;
        }

        for (int j = 0; j < 9; j++)
        {
            if (frequency[_board[i][j]] == -1)
            {
                if (_board[i][j] != 0)
                    frequency[_board[i][j]] = j;
            }
            else
            {
                _isRight[i][j] = false;
                _isRight[i][frequency[_board[i][j]]] = false;
            }

            if (frequency2[_board[j][i]] == -1)
            {
                if (_board[j][i] != 0)
                    frequency2[_board[j][i]] = j;
            }
            else
            {
                _isRight[j][i] = false;
                _isRight[frequency2[_board[j][i]]][i] = false;
            }
        }
    }

    int z;
    for (int k = 0; k < 9; k++)
    {
        int x = k / 3 * 3, y = k % 3 * 3;
        for (int i = 0; i < 10; i++)
            frequency[i] = -1;
        for (int i = x; i < x + 3; i++)
            for (int j = y; j < y + 3; j++)
                if (frequency[_board[i][j]] == -1)
                {
                    if (_board[i][j] != 0)
                        frequency[_board[i][j]] = i * 9 + j;
                }
                else
                {
                    z = frequency[_board[i][j]];
                    _isRight[i][j] = false;
                    _isRight[z / 9][z % 9] = false;
                }
    }
}

void Board::PutDigit(int number, int x, int y, int type)
{
    if (x < 0 || x > 8 || y < 0 || y > 8)
        return;
    if (_board[x][y] == 0)
        freeCells--;

    _board[x][y] = number;
    _type[x][y]  = type;
    _isRight[x][y] = true;
    SearchMistakes();
}

bool Board::GameOver(void) const
{
    if (freeCells)
        return false;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!_isRight[i][j])
                return false;

    return true;
}

bool Board::IsFreeCell(int& x, int& y) const
{
    return _board[x][y] == 0;
}

void Board::RemoveDigit(int x, int y, bool user)
{
    freeCells++;
    _board[x][y] = 0;
    _type[x][y]  = 0;
    _isRight[x][y] = true;

    if (user)
        SearchMistakes();
}
int Board::GetDigit(int x, int y) const
{
    return _board[x][y];
}

int Board::GetType(int x, int y) const
{
    return _type[x][y];
}

bool Board::GetValidation(int x, int y) const
{
    return _isRight[x][y];
}

void Board::GetFirstPosition(int& x, int& y) const
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (_type[i][j] == 0)
            {
                x = j;
                y = i;
                return;
            }
}

void Board::MoveRight(int& x, int &y) const
{
    for (int i = x + 1; i < 9; i++)
        if (_type[y][i] == 0)
        {
            x = i;
            return;
        }

    for (int i = 0; i < x; i++)
        if (_type[y][i] == 0)
        {
            x = i;
            return;
        }
}

void Board::MoveLeft(int& x, int& y) const
{
    for (int i = x - 1; i >= 0; i--)
        if (_type[y][i] == 0)
        {
            x = i;
            return;
        }

    for (int i = 8; i > x; i--)
        if (_type[y][i] == 0)
        {
            x = i;
            return;
        }
}

void Board::MoveUp(int& x, int& y) const
{
    for (int i = y - 1; i >= 0; i--)
        if (_type[i][x] == 0)
        {
            y = i;
            return;
        }

    for (int i = 8; i > y; i--)
        if (_type[i][x] == 0)
        {
            y = i;
            return;
        }
}

void Board::MoveDown(int& x, int& y) const
{
    for (int i = y + 1; i < 9; i++)
        if (_type[i][x] == 0)
        {
            y = i;
            return;
        }

    for (int i = 0; i < y; i++)
        if (_type[i][x] == 0)
        {
            y = i;
            return;
        }
}

bool Board::Generate(void)
{
    unsigned candidates[9][9][9], row[9] = {0}, col[9] = {0}, box[9] = {0};
    srand(time(NULL));

    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
        {
            for (int i = 0; i < 9; i++)
                candidates[r][c][i] = 1 << i;

            random_shuffle(candidates[r][c], candidates[r][c] + 9);
        }

    bool b = Solve(-1, 8, candidates, row, col, box);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (_board[i][j] > 1)
                _board[i][j] = log2(_board[i][j]) + 1;

    return b;
}

bool Board::Solve(int r, int c, unsigned candidates[9][9][9], unsigned row[9],
                  unsigned col[9], unsigned box[9])
{
    c++;
    if (c == 9)
    {
        r++;
        c = 0;
        if (r == 9)
            return true;
    }

    if (_board[r][c])
        return Solve(r, c, candidates, row, col, box);

    int b = r - r % 3 + c / 3;
    unsigned free = 511 ^ (row[r] | col[c] | box[b]);
    if (!free)
        return false;

    for (int i = 0; i < 9; i++)
    {
        if (candidates[r][c][i] & free)
        {
            row[r] |= candidates[r][c][i];
            col[c] |= candidates[r][c][i];
            box[b] |= candidates[r][c][i];
            _board[r][c] = candidates[r][c][i];

            if (Solve(r, c, candidates, row, col, box))
                return true;

            row[r] ^= candidates[r][c][i];
            col[c] ^= candidates[r][c][i];
            box[b] ^= candidates[r][c][i];
            _board[r][c] = 0;
        }
    }

    return false;
}

