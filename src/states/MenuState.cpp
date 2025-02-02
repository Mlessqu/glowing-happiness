//
// Created by Missqu on 1/21/25.
//

#include "MenuState.h"
#include "../gui/Button.h"
#include <iostream>

#include "AiGameState.h"
#include "LocalGameState.h"
#include "OnlineClientState.h"
#include "OnlineHostState.h"

#include "../EventHandle.h"
#include "../ResourceManager.h"
#include "../StateMachine.h"
class LocalGameState;
class OnlineClientState;
class OnlineHostState;
class AiGameState;

MenuState::MenuState(StateMachine &_machine_ref, sf::RenderWindow &_okno) : State { _machine_ref,_okno}
{
		std::cout << "Menu state intialized" << std::endl;

	Button start_button({200, 30}, {150, 50}, "CO OP", resource_manager_ref_.get_font(), _okno,
											[&]
											{
												machine_ref_.run(StateMachine::create_new_state<LocalGameState>(machine_ref_,okno_ref_));
											});

	Button vs_ai_button({200, 30}, {150, 100}, "VS AI",resource_manager_ref_.get_font(), _okno,
											[&]
											{
												machine_ref_.run(StateMachine::create_new_state<AiGameState>(machine_ref_,okno_ref_));
											});

	Button over_network_client({200, 50}, {150, 150}, "network as client",resource_manager_ref_.get_font(), _okno,
														 [&]
														 {
														 	machine_ref_.run(StateMachine::create_new_state<OnlineClientState>(machine_ref_,okno_ref_));
														 });
	Button over_network_host({200, 50}, {150, 200}, "network as host",resource_manager_ref_.get_font(), _okno,
													 [&]
													 {
													 	machine_ref_.run(StateMachine::create_new_state<OnlineHostState>(machine_ref_,okno_ref_));
													 });
	buttons_.push_back(std::make_unique<Button>(over_network_client));
	buttons_.push_back(std::make_unique<Button>(over_network_host));
	buttons_.push_back(std::make_unique<Button>(vs_ai_button));
	buttons_.push_back(std::make_unique<Button>(start_button));
	// loop proper

}
void MenuState::draw()
{
	okno_ref_.clear();
	for(auto& button : buttons_)
	{

		okno_ref_.draw(*button);
	}
	okno_ref_.display();
}

void MenuState::update(sf::Time& _delta_time, sf::Time& _lag)
{
	event_handle_ref_.handle_events();
	if (event_handle_ref_.input_data_.left_mouse_pressed==true)
	{
		for(auto& button : buttons_)
		{
			button->update();
		}
	}
}

void MenuState::pause()
{

}

void MenuState::resume()
{

}


