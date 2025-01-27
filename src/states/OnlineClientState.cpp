//
// Created by Missqu on 1/21/25.
//

#include "OnlineClientState.h"
#include "../ResourceManager.h"
#include <iostream>
#include "../Utility.h"
#include "../StateMachine.h"
#include "../EventHandle.h"
#include "../NetworkData.h"
OnlineClientState::OnlineClientState(StateMachine &_machine_ref, sf::RenderWindow &_okno) :
	State { _machine_ref,_okno},
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


	sf::Socket::Status socket_status = socket_.connect(sf::IpAddress::LocalHost,53000);
	if (socket_status!=sf::Socket::Status::Done)
	{
		std::cerr << "Failed to connect" << std::endl;
	}else
	{
		std::cerr << "Successfully connected to the server" << std::endl;
	}
}

void OnlineClientState::draw()
{
	okno_ref_.clear();
	for ( auto& sprite : sprites_to_draw_ )
	{
		okno_ref_.draw(sprite);
	}
	okno_ref_.display();
}

void OnlineClientState::pause()
{

}
/*TODO
 *Obecnie sockety blockuja input, co nie przeszkadza podczas odbierania pakietu, ale nie mozna wprowadzic inputu
 *dla socketa ktory wysyla.
 *1.Set socket blocking true gdy
 */
void OnlineClientState::update(sf::Time& _delta_time, sf::Time& _lag)
{
	event_handle_ref_.handle_events();
    if (my_turn == true) //ruch klienta ruchacza
    {
        int wybor_gracza = -1;
        if (event_handle_ref_.input_data_.left_mouse_pressed == true) //was it left one?
        {
            sf::Vector2i mouse_pos = event_handle_ref_.input_data_.mouse_pos_on_left_click;
            wybor_gracza = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); //calculate at which field was clicked
        }
        //---------------------------------------------------
        //---------------
        if (game_.logic(wybor_gracza, kolko)) //
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
        }
        my_turn = true;
    	socket_.setBlocking(false);
    }
    //---------------------------------------------------
    if (my_turn == false) //ruch hosta oponenta
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
        //---------------------------------------------------
        if (game_.logic(wybor_oponenta, kolko))
        {
            sf::Vector2f temp_pos = {get_2D_index(wybor_oponenta).x * 100.f, get_2D_index(wybor_oponenta).y * 100.f};
            kolko_sprite_.setPosition(temp_pos);
            sprites_to_draw_.push_back(kolko_sprite_);
        }

        my_turn = false; //change it to ruch hosta ruchacza
    	socket_.setBlocking(false);
    }
	//-------------------------------------------------
	if (event_handle_ref_.input_data_.right_mouse_pressed == true)
	{
		socket_.disconnect();
		machine_ref_.pop_state();
	}
    //-------------------------------------------------
}

void OnlineClientState::resume()
{

}

