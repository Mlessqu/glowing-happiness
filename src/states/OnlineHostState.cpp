//
// Created by Missqu on 1/21/25.
//

#include "OnlineHostState.h"
#include "../ResourceManager.h"
#include <iostream>
#include "../Utility.h"
#include "../StateMachine.h"
class ResourceManager;
class StateMachine;

void OnlineHostState::pause()
{
}

void OnlineHostState::resume()
{
}

void OnlineHostState::update()
{
    while (const std::optional event = okno_ref_.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            okno_ref_.close();
        }
        if (const auto* mouse_pressed = event->getIf<sf::Event::MouseButtonPressed>()) //was mouse button pressed?
        {
            if (mouse_pressed->button == sf::Mouse::Button::Left) //was it left one?
            {
                auto mouse_pos = relative_mouse_pos(okno_ref_); // get relative mouse cords to window
                int wybor = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); //calculate at which field was clicked


                if (game_.make_turn(wybor, game_.czyja_tura())) //jezeli tura zostala wykonana to trzeba narysowac
                {
                    sf::Vector2f temp_pos = {get_2D_index(wybor).x * 100.f, get_2D_index(wybor).y * 100.f};
                    if (game_.czyja_tura() == krzyzyk)
                    {
                        krzyzyk_sprite_.setPosition(temp_pos);
                        sprites_to_draw_.push_back(krzyzyk_sprite_);
                    }
                    else if (game_.czyja_tura() == kolko)
                    {
                        kolko_sprite_.setPosition(temp_pos);
                        sprites_to_draw_.push_back(kolko_sprite_);
                    }
                }
            }
            else if (mouse_pressed->button == sf::Mouse::Button::Right)
            {
                machine_ref_.pop_state(); // quit here
            }
        }
    }
}

void OnlineHostState::draw()
{
    okno_ref_.clear();
    for (auto& sprite : sprites_to_draw_)
    {
        okno_ref_.draw(sprite);
    }
    okno_ref_.display();
}

OnlineHostState::OnlineHostState(StateMachine& _machine_ref, sf::RenderWindow& _okno):
    State{_machine_ref, _okno},
    kolko_sprite_(resource_manager_ref_.get_o()),
    krzyzyk_sprite_(resource_manager_ref_.get_x()),
    board_sprite_(resource_manager_ref_.get_board()),
    zwyciezca_tekst_(resource_manager_ref_.get_font()),
    game_(true)
{
    sprites_to_draw_.push_back(board_sprite_);
    okno_ref_.clear();
    okno_ref_.draw(board_sprite_);
    okno_ref_.display();
    std::cout << "LocalGameState::LocalGameState()" << std::endl;
    zwyciezca_tekst_.setOutlineColor(sf::Color::White);
    zwyciezca_tekst_.setFillColor(sf::Color::Green);
    zwyciezca_tekst_.setString(std::string("LocalGameState::zwyciezca_tekst_"));
}
