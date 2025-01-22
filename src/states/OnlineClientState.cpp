//
// Created by Missqu on 1/21/25.
//

#include "OnlineClientState.h"
#include "../ResourceManager.h"
#include <iostream>
#include "../Utility.h"
#include "../StateMachine.h"
#include "../EventHandle.h"
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

void OnlineClientState::update()
{
	event_handle_ref_.handle_events();
	int wybor_gracza = -1;
	if (event_handle_ref_.input_data_.left_pressed == true) //was it left one?
	{
		sf::Vector2i mouse_pos = event_handle_ref_.input_data_.mouse_pos_on_left_click;
		wybor_gracza = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); //calculate at which field was clicked
	}
	//---------------------------------------------------
	if (game_.logic(wybor_gracza,game_.czyja_tura())) // if game logic iteration succesful return true else false
	{
		sf::Vector2f temp_pos = {get_2D_index(wybor_gracza).x * 100.f, get_2D_index(wybor_gracza).y * 100.f};
		if (game_.czyja_tura() == kolko) //na odwrot bo tura juz byla zrobiona
		{
			krzyzyk_sprite_.setPosition(temp_pos);
			sprites_to_draw_.push_back(krzyzyk_sprite_);
		}
		else if (game_.czyja_tura() == krzyzyk)
		{
			kolko_sprite_.setPosition(temp_pos);
			sprites_to_draw_.push_back(kolko_sprite_);
		}
	}
	if (event_handle_ref_.input_data_.right_pressed == true)
	{
		machine_ref_.pop_state();
	}
}

void OnlineClientState::resume()
{

}

class StateMachine;

class ResourceManager;