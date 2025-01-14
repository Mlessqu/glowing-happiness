#pragma once
#include "utility.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
struct input {
  sf::Vector2f mouse_pos;
  bool left_mouse = false;
  bool right_mouse = false;
};
static input input_data;

void update_input(sf::RenderWindow &_okno) {
  input_data.mouse_pos = relative_mouse_pos(_okno);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    input_data.left_mouse = true;
  else
    input_data.left_mouse = false;
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    input_data.right_mouse = true;
  else
    input_data.right_mouse = false;
  
}