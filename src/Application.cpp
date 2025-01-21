//
// Created by Missqu on 1/16/25.
//

#include "Application.h"

#include <iostream>

#include"State.h"
#include "MenuState.h"
#include"ResourceManager.h"

Application::Application() =default;

void Application::run() { //init and main loop of the program
	ResourceManager::init();
	//create render window
	window_.create(sf::VideoMode({300,300}),"Tic Tac Toe");
	window_.setFramerateLimit(60);

	//initialize state machine
	state_machine_.run(StateMachine::create_new_state<MenuState>(state_machine_,window_));

	//main loop
	while (state_machine_.running())
	{
			state_machine_.next_state();
			state_machine_.update();
		state_machine_.draw();
	}
}




