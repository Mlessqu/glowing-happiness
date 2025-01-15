#pragma once
#include "logic.hpp"
#include "utility.hpp"
extern sf::Text zwyciezca_text;
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
// declarations
void make_move(GameState *_gamestate) {
  if (is_valid_move(_gamestate) == false)
    return;
  _gamestate->board[_gamestate->wybor] = czyja_tura(_gamestate);
  is_end(_gamestate);
  _gamestate->tura++;
}
int czyja_tura(GameState *_game_state) {
  if (_game_state->tura % 2)
    return 2; // kolko
  else
    return 1; // krzyzyk
}
bool is_valid_move(GameState *_gamestate) {
  if (_gamestate->board[_gamestate->wybor] != 0) {
    return false;
  }
  if ((_gamestate->wybor < 0) && (_gamestate->wybor >= 9)) {
    return false;
  }
  return true;
}
bool is_end(GameState *_game_state) {

  if (check_winner(_game_state->board)) // we check for the winner afterwards
  {
    if (czyja_tura(_game_state) == 1) {
      zwyciezca_text.setString("Krzyzyk wygral!");
      _game_state->exit_flag = true;
      return true;
    }
    if (czyja_tura(_game_state) == 2) {
      zwyciezca_text.setString("Kolko wygralo!");
      _game_state->exit_flag = true;
      return true;
    }
  } else if (_game_state->tura > 7) {
    zwyciezca_text.setString("Remis!");
    _game_state->exit_flag = true;
    return true;
  }

  _game_state->exit_flag = false;
  return false;
}
bool check_winner(int *_board) {
  /* let 0 - empty, 1 - krzyzyk, 2- kolko*/
  // [0][0].[1][1],[2][2] //pierwszy diagonal
  // [0][2],[1][1],[2][0] //drugi diagonal
  // [n][0],[n][1],[n][2] //wiersze
  // [0][n],[1][n],[2][n] //kolumny
  if ((_board[0] == _board[4] && _board[4] == _board[8]) && _board[0] != 0) {
    return true;
  } // if all diagonal equal but not 0 then true
  if ((_board[6] == _board[4] && _board[4] == _board[2]) && _board[6] != 0) {
    return true;
  } // if all diagonal equal but not 0 then true
  for (int i = 0; i < 6; i = i + 3) {
    if ((_board[i] == _board[i + 1] && _board[i + 1] == _board[i + 2]) &&
        _board[i] != 0)
      return true; // columns all equal but not 0
  }
  for (int i = 0; i < 3; i++) {
    if ((_board[i] == _board[i + 3] && _board[i + 3] == _board[i + 6]) &&
        _board[i] != 0)
      return true; // row all equal but not 0
  }
  return false; // otherwise no winner
}
} // namespace Msq