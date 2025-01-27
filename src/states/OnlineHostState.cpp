//
// Created by Missqu on 1/21/25.
//

#include "OnlineHostState.h"
#include "../ResourceManager.h"
#include <iostream>
#include "../Utility.h"
#include "../StateMachine.h"
#include "../EventHandle.h"
#include <SFML/Network.hpp>
class ResourceManager;
class StateMachine;

void OnlineHostState::pause()
{
}

void OnlineHostState::resume()
{
}

void OnlineHostState::update(sf::Time& _delta_time, sf::Time& _lag)
{
    event_handle_ref_.handle_events();
    //-----------------------------------------------
    if (my_turn==true)
    {
        int wybor_gracza = -1;
        if (event_handle_ref_.input_data_.left_mouse_pressed == true) //was it left one?
        {
            sf::Vector2i mouse_pos = event_handle_ref_.input_data_.mouse_pos_on_left_click;
            wybor_gracza = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); //calculate at which field was clicked
        }
        //---------------------------------------------------
        //---------------
        if (game_.logic(wybor_gracza, krzyzyk)) //
        {
            network_data_ = game_.get_data_for_network();
            network_packet_ << network_data_; // writing data into packet
            while (socket_.send(network_packet_) != sf::Socket::Status::Done)
            {
            }
            //------------------------------------------
            sf::Vector2f temp_pos = {get_2D_index(wybor_gracza).x * 100.f, get_2D_index(wybor_gracza).y * 100.f};
            krzyzyk_sprite_.setPosition(temp_pos);
            sprites_to_draw_.push_back(krzyzyk_sprite_);
            my_turn=false;
            socket_.setBlocking(true);
        }

    }
    //---------------------------------------------------
    if (my_turn==false)
    {
        int wybor_oponenta = -1;
        while (socket_.receive(network_packet_) != sf::Socket::Status::Done)
        {
        } // receive network packet from client
        if (network_packet_ >> network_data_) //reading received data
        {
            std::cout << "Reading host data success." <<
                "\nKto: " << network_data_.kto <<
                "\nTura:" << network_data_.turn <<
                "\nWybor:" << network_data_.wybor << std::endl;
        }
        else
        {
            std::cerr << "Reading host data failed.\n";
            return; //
        }
        wybor_oponenta = network_data_.wybor;
        //---------------------------------------------------
        if (game_.logic(wybor_oponenta, kolko))
        {

            sf::Vector2f temp_pos = {get_2D_index(wybor_oponenta).x * 100.f, get_2D_index(wybor_oponenta).y * 100.f};
            kolko_sprite_.setPosition(temp_pos);
            sprites_to_draw_.push_back(kolko_sprite_);
            my_turn=true;
            socket_.setBlocking(false);
        }

    }
    if (event_handle_ref_.input_data_.right_mouse_pressed == true)
    {
        machine_ref_.pop_state();
    }
    //-------------------------------------------------
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
#pragma region inicjalizacja
    sprites_to_draw_.push_back(board_sprite_);
    okno_ref_.clear();
    okno_ref_.draw(board_sprite_);
    okno_ref_.display();
    zwyciezca_tekst_.setOutlineColor(sf::Color::White);
    zwyciezca_tekst_.setFillColor(sf::Color::Green);
    zwyciezca_tekst_.setString(std::string("LocalGameState::zwyciezca_tekst_"));
#pragma endregion
#pragma region network
    if (listener_.listen(53000) != sf::Socket::Status::Done)
    {
        //error
    }
    //accept new connection
    if (listener_.accept(socket_) != sf::Socket::Status::Done)
    {
        //error
    }
    socket_.setBlocking(false);
#pragma endregion
}