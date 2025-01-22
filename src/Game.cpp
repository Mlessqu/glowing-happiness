//
// Created by Missqu on 1/21/25.
//

#include "Game.h"
#include <iostream>

#include "Utility.h"

enum Turn;

Game::Game(bool _czy_krzyzyk)
{
    //init game object
    std::array<int, 9> temp = {0};
    board_ = temp;
    tura_ = 0;
    wygrana_ = false;
    if (_czy_krzyzyk) //krzyzyk zaczyna
    {
        player1 = true;
        player2 = false;
    }
    else //kolka zaczynaja
    {
        player1 = false;
        player2 = true;
    }
}


bool Game::logic(int _wybor, const Turn _who_attempts)
{
    if (!this->is_legal_move(_wybor)) // out of bounds
        return false;
    if (wygrana_==true) //guard for if already won
        return false;

    if (player1==true && _who_attempts == krzyzyk) //if the one making input is actually matching with person supposed to make a move
    {
        make_turn(_wybor, krzyzyk);
        if (check_winner())
        {
            std::cout << "Player 1 wins!" << std::endl;
            bool wygrana = true;
        }
        player1 = false;
        player2 = true;
        return true;
    }
    else if (player2 == true && _who_attempts==kolko)
    {
        make_turn(_wybor, kolko);
        if (check_winner())
        {
            std::cout << "Player 2 wins!" << std::endl;
            bool wygrana = true;
        }
        player1 = true;
        player2 = false;
        return true;
    }
    return false; //nobody took a turn return false
}


bool Game::make_turn(int _wybor, Turn _turn) //we return true on sucesful turn
{
    if (wygrana_ == true)
        return false; //if someone won we cease to make any turns

    if (is_legal_move(_wybor) == false) //not a legal move
    {
        return false;
    }
    if (_turn == krzyzyk)
    {
        board_[_wybor] = 1; //X
    }
    else if (_turn == kolko)
    {
        board_[_wybor] = 2; //O
    }
    ++tura_; //increment tura
    if (check_winner()) //na samym koncu check if there is a winner
    {
        //who won?
        // std::cout << "inside check_winner, before end_game()" << std::endl;
        wygrana_ = true;
    }

    // debug_info();
    std::cout << "Wybor:" << _wybor << std::endl;
    return true;
}


bool Game::is_legal_move(int _wybor)
{
    if (_wybor < 0 || _wybor >= 9) //wybor jest poza range od 0-8 włącznie
    {
        return false;
    }
    if (board_[_wybor] != 0) //zajeta kratka juz not legal move
    {
        return false;
    }
    return true;
}

Turn Game::czyja_tura()
{
    if (player1 == true)
        return krzyzyk;
    if (player2 == true)
        return kolko;
}

bool Game::check_winner() //checks if current board has any winner
{
    /* let 0 - empty, 1 - krzyzyk, 2- kolko
    // [0][0],[1][1],[2][2] //pierwszy diagonal
    // [0][2],[1][1],[2][0] //drugi diagonal
    // [n][0],[n][1],[n][2] //wiersze
    // [0][n],[1][n],[2][n] //kolumny */
    if ((board_[0] == board_[4]) && (board_[4] == board_[8]) && board_[0] != 0)
    {
        return true;
    } // if all diagonal equal but not 0 then true
    if ((board_[6] == board_[4]) && (board_[4] == board_[2]) && board_[6] != 0)
    {
        return true;
    } // if all diagonal equal but not 0 then true
    for (int i = 0; i < 7; i = i + 3)
    {
        if (((board_[i] == board_[i + 1]) && (board_[i + 1] == board_[i + 2])) &&
            board_[i] != 0)
        {
            return true; // columns all equal but not 0
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (((board_[i] == board_[i + 3]) && (board_[i + 3] == board_[i + 6])) &&
            board_[i] != 0)
        {
            return true; // row all equal but not 0
        }
    }
    return false; // otherwise no winner
}
