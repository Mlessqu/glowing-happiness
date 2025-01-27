//
// Created by Missqu on 1/16/25.
//

#include "Application.h"

#include <iostream>

#include"states/State.h"
#include "states/MenuState.h"
#include"ResourceManager.h"

Application::Application() =default;

void Application::run()
{ //init and main loop of the program
	//create render window
	window_.create(sf::VideoMode({300,300}),"Tic Tac Toe");
	window_.setFramerateLimit(60);
	resource_manager_ = &ResourceManager::get_instance();
	event_handle_ = &EventHandle::get_instance(state_machine_,window_);
	//initialize state machine
	state_machine_.run(StateMachine::create_new_state<MenuState>(state_machine_,window_));
	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	sf::Time delta_time = sf::Time::Zero;
	//main loop
	while (state_machine_.running())
	{
		delta_time = clock.restart();
		//---------------------------------
		state_machine_.next_state();

		state_machine_.update(delta_time, lag);
		state_machine_.draw();
		//-------------------------------------------
	}
}




