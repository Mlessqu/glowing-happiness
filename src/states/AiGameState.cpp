//
// Created by Missqu on 1/21/25.
//

#include "AiGameState.h"

#include <iostream>

#include "../ResourceManager.h"
#include "../Utility.h"
#include "../StateMachine.h"
#include "../EventHandle.h"
#include <stdlib.h>
#include <time.h>
class ResourceManager;
class StateMachine;
class Game;
AiGameState::AiGameState(StateMachine &_machine_ref, sf::RenderWindow &_okno) :
State{_machine_ref,_okno},
game_(true),
kolko_sprite_(resource_manager_ref_.get_o()),
krzyzyk_sprite_(resource_manager_ref_.get_x()),
board_sprite_(resource_manager_ref_.get_board()),
zwyciezca_tekst_(resource_manager_ref_.get_font())
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

void AiGameState::update(sf::Time& _delta_time, sf::Time& _lag)
{
	event_handle_ref_.handle_events();
	int wybor_gracza = -1;
	if (event_handle_ref_.input_data_.left_mouse_pressed == true) //was it left one?
	{
		sf::Vector2i mouse_pos = event_handle_ref_.input_data_.mouse_pos_on_left_click;
		wybor_gracza = get_1D_index(mouse_pos.x / 100, mouse_pos.y / 100); //calculate at which field was clicked
	}
	//---------------------------------------------------
	//---------------
	if (game_.logic(wybor_gracza,krzyzyk)) // if game logic iteration succesful return true else false
	{
		sf::Vector2f temp_pos = {get_2D_index(wybor_gracza).x * 100.f, get_2D_index(wybor_gracza).y * 100.f};
			krzyzyk_sprite_.setPosition(temp_pos);
			sprites_to_draw_.push_back(krzyzyk_sprite_);
	}
	//---------------------------------------------------
	int wybor_bota = -1;
	srand (time(NULL));
	wybor_bota= rand()%9;
	// std::cout << "wybor_bota: " << wybor_bota << std::endl;
	//---------------------------------------------------
	if (game_.logic(wybor_bota,kolko))
	{
		sf::Vector2f temp_pos = {get_2D_index(wybor_bota).x * 100.f, get_2D_index(wybor_bota).y * 100.f};
		kolko_sprite_.setPosition(temp_pos);
		sprites_to_draw_.push_back(kolko_sprite_);
	}
	if (event_handle_ref_.input_data_.right_mouse_pressed == true)
	{
		machine_ref_.pop_state();
	}
}

void AiGameState::draw()
{
	okno_ref_.clear();
	for ( auto& sprite : sprites_to_draw_ )
	{
		okno_ref_.draw(sprite);
	}
	okno_ref_.display();
}

void AiGameState::pause()
{
std::cout << std::endl << "Paused" << std::endl;
}

void AiGameState::resume()
{
	std::cout << std::endl << "Resuming" << std::endl;
}
