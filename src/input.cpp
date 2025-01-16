#include "input.hpp"
#include "utility.hpp"
#include <SFML/Graphics.hpp>

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
