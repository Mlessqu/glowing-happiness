#pragma once
#include <vector>
#include "logic.hpp"
#include "resources.hpp"
int ai_agent(Msq::GameState *_game_state)
{
    std::vector<Msq::GameState> game_states;
    Msq::GameState temp = {};
    for (int i = 0; i < 9; i++)
    {
        if (_game_state->board[i] != 0)
            continue;
        else
            return i;
    }
    return 1;
}

int calculate_score_for_move(Msq::GameState *_game_state)
{
    if (Msq::check_winner(_game_state->board)) // we check for the winner afterwards
    {

        if (czyja_tura(_game_state) == 1) // krzyzyk
        {
            return -10;
        }
        else // kolko
        {
            return 10;
        }
    }
    else if (_game_state->tura > 7)
    {
        std::cout << "Remis!" << std::endl;
        zwyciezca_text.setString("Remis!");
        return 0;
    }
    return -1;
}
