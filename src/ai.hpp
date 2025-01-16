#pragma once
#include "resources.hpp"
#include <algorithm>
#include <random>
#include <vector>

int ai_random_move(Msq::GameState *_game_state);
Msq::GameState ai_move(Msq::GameState *_game_state);