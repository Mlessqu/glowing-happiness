#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
char draw_sign(int _val);
void draw_line(int _ile);
void draw_board(int *_board);
sf::Vector2f relative_mouse_pos(sf::RenderWindow &_okno);
int get_1D_index(int _x, int _y);
sf::Vector2f get_2D_index(int _x);

sf::Vector2f relative_mouse_pos(sf::RenderWindow &_okno)
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(_okno);
    sf::Vector2f worldPos = _okno.mapPixelToCoords(pixelPos);
    return worldPos;
}

void draw_board(int *_board) // drawing board bullshitery
{
    draw_line(7);
    std::cout << "\n";
    int counter = 0;
    for (int i = 0; i < 18; i++)
    {
        if (counter == 9)
        {
            std::cout << "shit";
            return;
        }
        if (!(i % 2))
        {
            std::cout << "#";
        }
        else
        {
            std::cout << draw_sign(_board[counter]);
            counter++;
        }
        const int enter_after = 6;
        if (((i % enter_after) == 0) && i != 0)
            std::cout << "\n#";
    }
    std::cout << "#\n";
    draw_line(6);
    std::cout << "\n";
}

void draw_line(int _ile)
{
    for (int i = 0; i < _ile; i++)
    {
        std::cout << "#";
    }
}
char draw_sign(int _val)
{
    if (_val == 0)
        return '-';
    if (_val == 1)
        return 'X';
    if (_val == 2)
        return 'O';
    return '-';
}

int get_1D_index(int _x, int _y)
{
    const int dlugosc_wiersza = 3;
    return _y * dlugosc_wiersza + _x; // Indexes
}
sf::Vector2f get_2D_index(int _len)
{

    int _y = _len / 3;
    int _x = _len % 3;
    return sf::Vector2f(_x, _y);
}

inline int czyja_tura(int _tura)
{
    if (_tura % 2)
        return 2;
    else
        return 1;
}