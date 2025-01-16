#pragma once

#include <SFML/Graphics.hpp>

namespace Msq {
struct GameState {
  int board[9] = {0, 0, 0, // tablica
                  0, 0, 0, 0, 0, 0};
  int tura = 0;
  int wybor = 0;
  bool exit_flag = false;
  int score = 0;
};
bool is_end(GameState *_game_state);
int czyja_tura(GameState *_game_state);
bool is_valid_move(GameState *_gamestate);
bool check_winner(int *_board);
void make_move(GameState *_gamestate);
} // namespace Msq