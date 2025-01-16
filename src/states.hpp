#pragma once
#include <SFML/Graphics.hpp>
extern sf::Font font;
extern sf::Text zwyciezca_text;
extern sf::Texture board_texture; // tekstura boardu
extern sf::Sprite board_sp;
//---------------------
extern sf::Texture the_o;
extern sf::Sprite the_o_sp;
//---------------------
extern sf::Texture the_x;
extern sf::Sprite the_x_sp;

void co_op_game_loop(sf::RenderWindow &_okno);
void winner_loop(sf::RenderWindow &_okno);
void ai_game_loop(sf::RenderWindow &_okno);
void network_loop_client(sf::RenderWindow &_okno);
void network_loop_host(sf::RenderWindow &_okno);
void menu_loop(sf::RenderWindow &_okno);
