//
// Created by Missqu on 1/16/25.
//

#include "StateMachine.h"
#include<SFML/Window.hpp>
#include"State.h"

namespace sf {
	class RenderWindow;
}

StateMachine::StateMachine() : is_running(false), is_paused(false) {}

StateMachine::~StateMachine() = default;


void StateMachine::push_state(std::unique_ptr<State> _state)
{
	states.push(std::move(_state));
}

void StateMachine::pop_state() {
	if (!states.empty())
	{
		states.pop();
	}
}


void StateMachine::update() {
	states.top()->update();
}
void StateMachine::draw()
{
	states.top()->draw();
}

void StateMachine::run(std::unique_ptr<State> _state) {
	is_running = true;
	states.push(std::move(_state));
}

bool StateMachine::running() const
{
	return is_running;
}

void StateMachine::quit()
{
	is_running = false;
}

