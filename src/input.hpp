#pragma once
#include <SFML/Graphics.hpp>
struct input {
  sf::Vector2f mouse_pos;
  bool left_mouse = false;
  bool right_mouse = false;
};
static input input_data;

void update_input(sf::RenderWindow &_okno);