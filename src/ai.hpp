#pragma once
#include "logic.hpp"
int ai_agent(int *_board)
{
    for (int i = 0; i < 9; i++)
    {
        if (_board[i] == 0)
            return i;
    }
}

int calculate_score_for_move(int *_board, int move, int _tura)
{
    int copy_board[9];
    for (int i = 0; i < 9; i++)
    {
        copy_board[i] = _board[i];
    }

    return 1;
}