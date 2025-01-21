//
// Created by Missqu on 1/16/25.
//

#include "Application.h"
#include"State.h"
#include "MenuState.h"


Application::Application() =default;

void Application::run() { //init and main loop of the program
	//create render window
	window_.create(sf::VideoMode({800,600}),"Tic Tac Toe");
	window_.setFramerateLimit(60);
	//initialize state machine
	state_machine_.run(StateMachine::create_new_state<MenuState>(state_machine_,window_));

	while (state_machine_.running())
	{
			process_events();
			update();
			render();
	}
}

void Application::process_events() {
	while (const std::optional event = window_.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window_.close();
		}
	}

}

void Application::update() {
}

void Application::render() {
	window_.clear();
	//window_.draw();
	window_.display();
}

