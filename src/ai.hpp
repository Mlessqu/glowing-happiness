#pragma once
#include <vector>
#include "logic.hpp"
#include "resources.hpp"
int min_max(Msq::GameState *_game_state);

int ai_move(Msq::GameState *_game_state)
{
    std::vector<Msq::GameState> game_states;
    Msq::GameState temp = {};

    for (int i = 0; i < 9; i++)
    {
        if (_game_state->board[i] != 0)
            continue;
        else
            temp.wybor = i;
        Msq::make_move(temp);
        if (Msq::is_end(temp))
        {
        }
        game_states.push_back(temp);
    }
    return 1;
}
int min_max(Msq::GameState *_game_state)
{

    for (int i = 0; i < 9; i++)
    {
        if (_game_state->board[i] != 0)
            continue;
        else
            moves.push_back(i); // available moves
    }

    if (Msq::check_winner(_game_state))
    {
        return _game_state->score;
    }
}
int calculate_score_for_move(Msq::GameState *_game_state)
{
    if (Msq::check_winner(_game_state->board)) // we check for the winner afterwards
    {

        if (czyja_tura(_game_state) == 1) // krzyzyk
        {
            score = score - 10;
            return score;
        }
        if (czyja_tura(_game_state) == 2)
        {
            score = score + 10;
            return score;
        }
    }
    else if (_game_state->tura > 7)
    {
        std::cout << "Remis!" << std::endl;
        zwyciezca_text.setString("Remis!");
        return score;
    }
}