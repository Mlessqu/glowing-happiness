#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "utility.hpp"
#include "ai.hpp"
#include "button.hpp"
#include "resources.hpp"
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

    Button start_button({150, 50}, {150, 50}, "CO OP");
    Button vs_ai_button({150, 50}, {150, 150}, "VS AI");
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
                    if (vs_ai_button.button_body.getGlobalBounds().contains(relative_mouse_pos(_okno)))
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
        _okno.draw(vs_ai_button);
        _okno.draw(zwyciezca_text);
        _okno.display();
    }
}

void co_op_game_loop(sf::RenderWindow &_okno)
{
    // game loop initialization here
    std::vector<sf::Sprite> sprites_to_draw;
    sprites_to_draw.push_back(board_sp);
    _okno.clear();
    _okno.draw(board_sp);
    _okno.display();
    Msq::GameState original_game_state = {};
    sf::Text debug_text(font);
    debug_text.setFillColor(sf::Color::Red);
    debug_text.setStyle(sf::Text::Bold);
    debug_text.setPosition({20, 20});
    debug_text.setCharacterSize(24);
    while (_okno.isOpen())
    {
        while (const std::optional _event = _okno.pollEvent()) // poll events
        {
            debug_text.setString(debug_string(original_game_state.tura, original_game_state.wybor));
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
                    original_game_state.wybor = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); // translate mouse cord into 1D array 0-8
                    if (Msq::is_valid_move(&original_game_state))
                    {

                        if (Msq::czyja_tura(&original_game_state) == 2)
                        {

                            the_o_sp.setPosition({get_2D_index(original_game_state.wybor).x * 100.f, get_2D_index(original_game_state.wybor).y * 100.f});
                            sprites_to_draw.push_back(the_o_sp);
                            // kolkos
                        }
                        else
                        {

                            the_x_sp.setPosition({get_2D_index(original_game_state.wybor).x * 100.f, get_2D_index(original_game_state.wybor).y * 100.f});
                            sprites_to_draw.push_back(the_x_sp);
                            // krzyzyks
                        }
                        Msq::make_move(&original_game_state);
                    }
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
        _okno.draw(debug_text);
        _okno.draw(zwyciezca_text);
        _okno.display();
        if (original_game_state.exit_flag == true)
        {
            winner_loop(_okno);
            return;
        }
    }
}

void ai_game_loop(sf::RenderWindow &_okno)
{
    // game loop initialization here
    // game loop initialization here
    std::vector<sf::Sprite> sprites_to_draw;
    sprites_to_draw.push_back(board_sp);
    _okno.clear();
    _okno.draw(board_sp);
    _okno.display();
    Msq::GameState original_game_state = {};
    sf::Text debug_text(font);
    debug_text.setFillColor(sf::Color::Red);
    debug_text.setStyle(sf::Text::Bold);
    debug_text.setPosition({20, 20});
    debug_text.setCharacterSize(24);
    while (_okno.isOpen())
    {
        while (const std::optional _event = _okno.pollEvent()) // poll events
        {
            debug_text.setString(debug_string(original_game_state.tura, original_game_state.wybor));
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
                    original_game_state.wybor = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); // translate mouse cord into 1D array 0-8, division by 100, because it is 100pixels wide and high
                    if (Msq::czyja_tura(&original_game_state) == 1)
                    {
                        //----------------------------------------------------
                        the_x_sp.setPosition({get_2D_index(original_game_state.wybor).x * 100.f, get_2D_index(original_game_state.wybor).y * 100.f});
                        sprites_to_draw.push_back(the_x_sp);
                        //--------------------------------
                        Msq::make_move(&original_game_state);
                        if (original_game_state.exit_flag == true)
                        {
                            break;
                        }
                    }

                    // krzyzyks

                    if (Msq::czyja_tura(&original_game_state) == 2)
                    {
                        original_game_state.wybor = ai_move(&original_game_state);
                        the_o_sp.setPosition({get_2D_index(original_game_state.wybor).x * 100.f, get_2D_index(original_game_state.wybor).y * 100.f});
                        sprites_to_draw.push_back(the_o_sp);
                        Msq::make_move(&original_game_state);
                        if (original_game_state.exit_flag == true)
                        {
                            break;
                        }
                        // kolkos
                    }
                }
            }
            // draw_board(board);
        }

        _okno.clear(sf::Color::Green);
        _okno.draw(board_sp);
        for (auto itr = sprites_to_draw.begin(); itr != sprites_to_draw.end(); itr++) // we loop over things to draw here
        {
            _okno.draw(*itr);
        }
        _okno.draw(zwyciezca_text);
        _okno.draw(debug_text);
        _okno.display();
        if (original_game_state.exit_flag == true)
        {
            winner_loop(_okno);
            return; // exit function, effectively exit state
            // we exit it only here!
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