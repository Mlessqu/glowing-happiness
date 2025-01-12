#pragma once
#include "logic.hpp"
#include "utility.hpp"
namespace Msq
{
    struct GameState
    {
        int board[9] = {0, 0, 0, // tablica
                        0, 0, 0,
                        0, 0, 0};
        int tura = 0;
        int wybor = 0;
    };
    int czyja_tura(GameState *_game_state);
    bool is_valid_move(GameState *_gamestate);

    // declarations
    void make_move(GameState *_gamestate)
    {
        if (!is_valid_move(_gamestate))
            return;
        _gamestate->board[_gamestate->wybor] = czyja_tura(_gamestate);
        _gamestate->tura++;
    }
    int czyja_tura(GameState *_game_state)
    {
        if (_game_state->tura % 2)
            return 2; // kolko
        else
            return 1; // krzyzyk
    }
    bool is_valid_move(GameState *_gamestate)
    {
        if (_gamestate->board[_gamestate->wybor] != 0)
        {
            return false;
        }
        if (_gamestate->wybor < 0 && _gamestate->wybor >= 9)
        {
            return false;
        }
        return true;
    }
}