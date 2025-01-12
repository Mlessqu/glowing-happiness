#pragma once
#include <iostream>
#include "utility.hpp"
extern sf::Text zwyciezca_text;
bool logika_co_op(int _wybor, int *_board, int _tura);
bool check_winner(int *_board);
void menu_loop(sf::RenderWindow &_okno);
void co_op_game_loop(sf::RenderWindow &_okno);
bool logika_ai(int _wybor, int *_board, int _tura);

//-0-------
bool logika_co_op(int _wybor, int *_board, int _tura)
{
    _board[_wybor] = czyja_tura(_tura);

    if (check_winner(_board)) // we check for the winner afterwards
    {

        std::cout << "Gratulujemy wygral:";
        if (!(_tura % 2))
        {
            std::cout << "Krzyzyk";
            zwyciezca_text.setString("Krzyzyk wygral!");
        }
        else
        {
            std::cout << "Kolko";
            zwyciezca_text.setString("Kolko wygralo!");
        }
        return true;
    }
    else if (_tura > 7)
    {
        std::cout << "Remis!" << std::endl;
        zwyciezca_text.setString("Remis!");
        return true;
    }
    return false;
}

bool logika_ai(int _wybor, int *_board, int _tura)
{
    if (czyja_tura(_tura) == 1) // even turn for xes
    {
        _board[_wybor] = 1; // gracz
    }
    else // odd turn for o's
    {
        _board[_wybor] = 2; // AI
    }
    if (check_winner(_board)) // we check for the winner afterwards
    {

        std::cout << "Gratulujemy wygral:";
        if (!(_tura % 2))
        {
            std::cout << "Krzyzyk";
            zwyciezca_text.setString("Krzyzyk wygral!");
        }
        else
        {
            std::cout << "Kolko";
            zwyciezca_text.setString("Kolko wygralo!");
        }
        return true;
    }
    else if (_tura > 7)
    {
        std::cout << "Remis!" << std::endl;
        zwyciezca_text.setString("Remis!");
        return true;
    }
    return false;
}

bool check_winner(int *_board)
{
    /* let 0 - empty, 1 - krzyzyk, 2- kolko*/
    // [0][0].[1][1],[2][2] //pierwszy diagonal
    // [0][2],[1][1],[2][0] //drugi diagonal
    // [n][0],[n][1],[n][2] //wiersze
    // [0][n],[1][n],[2][n] //kolumny
    if ((_board[0] == _board[4] && _board[4] == _board[8]) && _board[0] != 0)
    {
        return true;
    } // if all diagonal equal but not 0 then true
    if ((_board[6] == _board[4] && _board[4] == _board[2]) && _board[6] != 0)
    {
        return true;
    } // if all diagonal equal but not 0 then true
    for (int i = 0; i < 6; i = i + 3)
    {
        if ((_board[i] == _board[i + 1] && _board[i + 1] == _board[i + 2]) && _board[i] != 0)
            return true; // columns all equal but not 0
    }
    for (int i = 0; i < 3; i++)
    {
        if ((_board[i] == _board[i + 3] && _board[i + 3] == _board[i + 6]) && _board[i] != 0)
            return true; // row all equal but not 0
    }
    return false; // otherwise no winner
}
