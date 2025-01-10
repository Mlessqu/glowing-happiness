#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <bits/stdc++.h>
#include "utility.hpp"
#include "ai.hpp"
#include "button.hpp"
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
void menu_loop(sf::RenderWindow &_okno);
void co_op_game_loop(sf::RenderWindow &_okno);
void winner_loop(sf::RenderWindow &_okno);
void ai_game_loop(sf::RenderWindow &_okno);
void network_loop(sf::RenderWindow &_okno);

void menu_loop(sf::RenderWindow &_okno)
{
    // menu initialization here
    /*sf::RectangleShape start_button({150, 50});
    start_button.setFillColor(sf::Color::Green);
    // start_button.setOrigin({100, 50});
    start_button.setPosition({150, 50});
    sf::Text start_text(font);
    start_text.setFillColor(sf::Color::Blue);
    start_text.setStyle(sf::Text::Bold);
    start_text.setPosition(start_button.getPosition());
    start_text.setString("CO-OP");
    start_text.setCharacterSize(24); */
    Button start_button({150, 50}, {0, 50}, "Mleko");
    sf::RectangleShape vs_ai_button({150, 50});
    vs_ai_button.setFillColor(sf::Color::Green);
    // vs_ai_button.setOrigin({100, 50});
    vs_ai_button.setPosition({150, 150});
    sf::Text vs_ai_text(font);
    vs_ai_text.setFillColor(sf::Color::Blue);
    vs_ai_text.setStyle(sf::Text::Bold);
    vs_ai_text.setPosition(vs_ai_button.getPosition());
    vs_ai_text.setString("VS AI");
    vs_ai_text.setCharacterSize(24);
    // loop proper
    while (_okno.isOpen())
    {
        while (const std::optional _event = _okno.pollEvent())
        {
            if (_event->is<sf::Event::Closed>())
            {
                _okno.close();
            }
            if (const auto *mouseButtonPressed = _event->getIf<sf::Event::MouseButtonPressed>())
            {

                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    if (start_button.button_body.getGlobalBounds().contains(relative_mouse_pos(_okno)))
                    {
                        // start game loop
                        co_op_game_loop(_okno);
                        // cleanup here
                        zwyciezca_text.setString("");
                    }
                    if (vs_ai_button.getGlobalBounds().contains(relative_mouse_pos(_okno)))
                    {
                        // start  ai game loop
                        ai_game_loop(_okno);
                        // cleanup here
                        zwyciezca_text.setString("");
                    }
                }
            }
        }
        _okno.clear();
        _okno.draw(start_button);
        //_okno.draw(start_text);
        _okno.draw(vs_ai_button);
        _okno.draw(vs_ai_text);
        _okno.draw(zwyciezca_text);
        _okno.display();
    }
}

void co_op_game_loop(sf::RenderWindow &_okno)
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
        while (const std::optional _event = _okno.pollEvent()) // poll events
        {
            if (_event->is<sf::Event::Closed>())
            {
                _okno.close();
            }
            //-----------------
            if (const auto *mouseButtonPressed = _event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mouse_pos = relative_mouse_pos(_okno);
                    int wybor = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); // translate mouse cord into 1D array 0-8
                    if (board[wybor] != 0)
                    {
                        break;
                    }
                    if (tura % 2)
                    {

                        the_o_sp.setPosition({get_2D_index(wybor).x * 100.f, get_2D_index(wybor).y * 100.f});
                        sprites_to_draw.push_back(the_o_sp);
                        // kolkos
                    }
                    else
                    {

                        the_x_sp.setPosition({get_2D_index(wybor).x * 100.f, get_2D_index(wybor).y * 100.f});
                        sprites_to_draw.push_back(the_x_sp);
                        // krzyzyks
                    }
                    if (logika_co_op(wybor, board, tura))
                    {
                        EXIT_FLAG = true;
                        // winner_loop(_okno);
                        //  EXIT GAME LOOP HERE
                    }
                    tura++;
                    // draw_board(board);
                }
            }
        }
        _okno.clear(sf::Color::Green);
        _okno.draw(board_sp);
        for (auto itr = sprites_to_draw.begin(); itr != sprites_to_draw.end(); itr++) // we loop over things to draw here
        {
            _okno.draw(*itr);
        }
        _okno.draw(zwyciezca_text);
        _okno.display();
        if (EXIT_FLAG)
        {
            winner_loop(_okno);
            return;
        }
    }
}

void ai_game_loop(sf::RenderWindow &_okno)
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
        while (const std::optional _event = _okno.pollEvent()) // poll events
        {
            if (_event->is<sf::Event::Closed>())
            {
                _okno.close();
            }
            //-----------------
            if (const auto *mouseButtonPressed = _event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mouse_pos = relative_mouse_pos(_okno);
                    int wybor = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); // translate mouse cord into 1D array 0-8
                    if (board[wybor] != 0)
                    {
                        break;
                    }
                    if (tura % 2)
                    {
                        // tutaj musi sie znajdowac logika AI
                        wybor = ai_agent(board);
                        the_o_sp.setPosition({get_2D_index(wybor).x * 100.f, get_2D_index(wybor).y * 100.f});
                        sprites_to_draw.push_back(the_o_sp);
                        // kolkos
                    }
                    else
                    {

                        the_x_sp.setPosition({get_2D_index(wybor).x * 100.f, get_2D_index(wybor).y * 100.f});
                        sprites_to_draw.push_back(the_x_sp);
                        // krzyzyks
                    }
                    if (logika_ai(wybor, board, tura))
                    {
                        EXIT_FLAG = true;
                        // winner_loop(_okno);
                        //  EXIT GAME LOOP HERE
                    }
                    tura++;
                    // draw_board(board);
                }
            }
        }
        _okno.clear(sf::Color::Green);
        _okno.draw(board_sp);
        for (auto itr = sprites_to_draw.begin(); itr != sprites_to_draw.end(); itr++) // we loop over things to draw here
        {
            _okno.draw(*itr);
        }
        _okno.draw(zwyciezca_text);
        _okno.display();
        if (EXIT_FLAG)
        {
            winner_loop(_okno);
            return;
        }
    }
}

void winner_loop(sf::RenderWindow &_okno)
{
    while (_okno.isOpen())
    {
        while (const std::optional _event = _okno.pollEvent())
        {
            if (_event->is<sf::Event::Closed>())
            {
                _okno.close();
            }
            if (const auto *mouseButtonPressed = _event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Right)
                {
                    return;
                }
            }
        }
    }
}