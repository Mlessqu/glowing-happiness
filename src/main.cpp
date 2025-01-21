
#include "states.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include "Application.h"
sf::Font font;
sf::Text zwyciezca_text(font);
sf::Texture board_texture("board.png"); // tekstura boardu
sf::Sprite board_sp(board_texture);
//---------------------
sf::Texture the_o("o.png");
sf::Sprite the_o_sp(the_o);
//---------------------
sf::Texture the_x("x.png");
sf::Sprite the_x_sp(the_x);
int main() {
  Application app;
  app.run();
  //---------------------
  // #####@@@@@@@@@@@@@@@@@@@@@@
  // inicjalizacja
  auto window = sf::RenderWindow(sf::VideoMode({300u, 300u}), "Tic-tac-toe");
  window.setFramerateLimit(10);

  //---------------------
  if (!board_texture.loadFromFile("board.png")) {
    assert(false);
    std::cout << "Nie załadowano board.png";
  } else // ładowanie boarda
    board_sp.setTexture(board_texture);
  //---------------------
  if (!the_o.loadFromFile("o.png")) {
    assert(false);
    std::cout << "Nie załadowano o.png";
    // error...
  } else
    the_o_sp.setTexture(the_o);
  //---------------------
  if (!the_x.loadFromFile("x.png")) {
    std::cout << "Nie załadowano x.png";
  } else
    the_x_sp.setTexture(the_x);
  //---------------------
  // load font
  if (!font.openFromFile("arial.ttf")) {
    assert(false);
    std::cout << "Nie załadowano arial.ttf";
  }
  //---------------
  // select the font
  zwyciezca_text.setFont(font);
  zwyciezca_text.setCharacterSize(24);
  zwyciezca_text.setFillColor(sf::Color::Red);
  zwyciezca_text.setStyle(sf::Text::Bold);
  // #####@@@@@@@@@@@@@@@@@@@@@@
  // MAIN LOOP

  menu_loop(window);

  return 0;
}
