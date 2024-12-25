#pragma once
#include <SFML/Graphics.hpp>
#include "utility.hpp"
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
void menu_loop(sf::RenderWindow &_okno, sf::Event &_event);
void game_loop(sf::RenderWindow &_okno, sf::Event &_event);
void winner_loop(sf::RenderWindow &_okno, sf::Event &_event);
void menu_loop(sf::RenderWindow &_okno, sf::Event &_event)
{
    // menu initialization here
    sf::RectangleShape start_button(sf::Vector2f(200, 100));
    start_button.setFillColor(sf::Color::Green);
    start_button.setOrigin({100,50});
    start_button.setPosition({150, 150});
    sf::Text start_text;
    start_text.setFont(font);
    start_text.setFillColor(sf::Color::Blue);
    start_text.setStyle(sf::Text::Bold);
    start_text.setPosition(start_button.getPosition());
    start_text.setString("START");
    start_text.setCharacterSize(24);
    while (_okno.isOpen())
    {
        while (_okno.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
            {
                _okno.close();
            }
            if (_event.type == sf::Event::MouseButtonPressed)
            {
                if (_event.mouseButton.button == sf::Mouse::Left)
                {
                    if (start_button.getGlobalBounds().contains(relative_mouse_pos(_okno)))
                    {
                        // start game loop
                        game_loop(_okno, _event);
                        winner_loop(_okno, _event);
                        // cleanup here
                        zwyciezca_text.setString("");
                    }
                }
            }
        }
        _okno.clear();
        _okno.draw(start_button);
        _okno.draw(start_text);
        _okno.draw(zwyciezca_text);
        _okno.display();
    }
}

void game_loop(sf::RenderWindow &_okno, sf::Event &_event)
{
    // game loop initialization here
    std::vector<sf::Sprite> sprites_to_draw;
    bool EXIT_FLAG = false;
    sprites_to_draw.push_back(board_sp);
    _okno.clear();
    _okno.draw(board_sp);
    _okno.display();
    int board[9] = {0, 0, 0, // tablica
                    0, 0, 0,
                    0, 0, 0};
    int tura = 0;
    while (_okno.isOpen())
    {
        while (_okno.pollEvent(_event)) // poll events
        {
            if (_event.type == sf::Event::Closed)
            {
                _okno.close();
            }
            //-----------------
            if (_event.type == sf::Event::MouseButtonPressed)
            {
                if (_event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mouse_pos = relative_mouse_pos(_okno);
                    int wybor = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); // translate mouse cord into 1D array 0-8
                    if (tura % 2)
                    {

                        the_o_sp.setPosition(get_2D_index(wybor).x * 100, get_2D_index(wybor).y * 100);
                        sprites_to_draw.push_back(the_o_sp);
                        // kolkos
                    }
                    else
                    {
                        the_x_sp.setPosition(get_2D_index(wybor).x * 100, get_2D_index(wybor).y * 100);
                        sprites_to_draw.push_back(the_x_sp);
                        // krzyzyks
                    }
                    if (logika(wybor, board, tura))
                    {
                        EXIT_FLAG = true;
                         // EXIT GAME LOOP HERE
                    }
                    tura++;
                    draw_board(board);
                }
            }
        }
        _okno.clear();
        for (auto itr = sprites_to_draw.begin(); itr != sprites_to_draw.end(); itr++) // we loop over things to draw here
        {
            _okno.draw(*itr);
        }
        _okno.draw(zwyciezca_text);
        _okno.display();
        if(EXIT_FLAG) return;
    }
}

void winner_loop(sf::RenderWindow &_okno, sf::Event &_event)
{
    while (_okno.isOpen())
    {
        while (_okno.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
            {
                _okno.close();
            }
            if (_event.type == sf::Event::MouseButtonPressed)
            {
                if (_event.mouseButton.button == sf::Mouse::Left)
                {
                    return;
                }
            }
        }
    }
}