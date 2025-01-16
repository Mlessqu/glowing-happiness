#pragma once
#include <SFML/Graphics.hpp>
#include <string>
char draw_sign(int _val);
void draw_line(int _ile);
void draw_board(int *_board);
sf::Vector2f relative_mouse_pos(sf::RenderWindow &_okno);
int get_1D_index(int _x, int _y);
sf::Vector2f get_2D_index(int _x);
std::string debug_string(int _tura, int _wybor);
