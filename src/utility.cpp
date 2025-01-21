#include "utility.hpp"
#include <iostream>
sf::Vector2f relative_mouse_pos(sf::RenderWindow &_okno) {
  sf::Vector2i pixelPos = sf::Mouse::getPosition(_okno);
  sf::Vector2f worldPos = _okno.mapPixelToCoords(pixelPos);
  return worldPos;
}



void draw_line(int _ile) {
  for (int i = 0; i < _ile; i++) {
    std::cout << "#";
  }
}
char draw_sign(int _val) {
  if (_val == 0)
    return '-';
  if (_val == 1)
    return 'X';
  if (_val == 2)
    return 'O';
  return '-';
}

int get_1D_index(int _x, int _y) {
  const int dlugosc_wiersza = 3;
  return _y * dlugosc_wiersza + _x; // Indexes
}
sf::Vector2f get_2D_index(int _len) {

  int _y = _len / 3;
  int _x = _len % 3;
  return sf::Vector2f(_x, _y);
}

std::string debug_string(int _tura, int _wybor) {
  std::string str_tura = std::to_string(_tura);
  std::string str_wybor = std::to_string(_wybor);
  std::string final = "Tura: " + str_tura + " Wybor:" + str_wybor;
  return final;
}

int get_1D_index(sf::Vector2f _pos)
{
  const int dlugosc_wiersza = 3;
  const int wysokosc_wiersza = 100;
  const int szerokosc_wiersza = 100;
  return (_pos.y/100) * dlugosc_wiersza + (_pos.x/100); // Indexes
}