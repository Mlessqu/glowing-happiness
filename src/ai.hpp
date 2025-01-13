#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include "logic.hpp"
#include "resources.hpp"
int ai_random_move(Msq::GameState *_game_state)
{
    std::vector<int> lista;
    for (int i = 0; i < 9; i++)
    {
        if (_game_state->board[i] != 0)
            continue;
        else
            lista.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(lista.begin(), lista.end(), g);
    return lista[0];
}
Msq::GameState ai_move(Msq::GameState *_game_state)
{
    std::vector<Msq::GameState> moves;
    int best_score;
    if (Msq::check_winner(_game_state->board))
    {
        if (Msq::czyja_tura(_game_state) == 1)
        {
            _game_state->score = -10;
            return *_game_state;
        }
        if (Msq::czyja_tura(_game_state) == 2)
        {
            _game_state->score = 10;
            return *_game_state;
        }
        if (_game_state->tura > 7)
        {
            _game_state->score = 0;
            return *_game_state;
        }
    }
    else
    {
        for (int i = 0; i < 9; i++)
        {
            if (_game_state->board[i] != 0)
                continue;
            else
            {
                Msq::GameState temp;
                temp.wybor = i; // move
                Msq::make_move(&temp);
                temp.score = temp.score + ai_move(_game_state).score;
                moves.push_back(temp); // score of said move
            }
        }
        for (auto itr = moves.begin(); itr != moves.end(); itr++)
        {
            if (Msq::czyja_tura(&(*itr)) == 1) // minimalizujemy
            {
                if ((*itr).score < best_score)
                {
                    best_score = (&(*itr))->score;
                }
            }
            if (Msq::czyja_tura(&(*itr)) == 2) // maximalizowac
            {
                if ((*itr).score > best_score)
                {
                    best_score = (&(*itr))->score;
                }
            }
        }
        for (auto itr = moves.begin(); itr != moves.end(); itr++)
        {
            if ((*itr).score == best_score) // zwracamy strukture z najlepszym scorem
            {
                Msq::GameState temp = (*itr);
                return temp;
            }
        }
    }
    return moves[0];
}
