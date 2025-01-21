//
// Created by Missqu on 1/16/25.
//

#include "StateMachine.h"
#include<SFML/Window.hpp>
#include"State.h"

namespace sf {
	class RenderWindow;
}

StateMachine::StateMachine() : is_running(false), is_popped(false) {}

StateMachine::~StateMachine() = default;

void StateMachine::next_state()
{
	if (is_popped)
	{
		//cleanup
		if (!states.empty())
		{
			states.top()->pause(); // clean up in pause
			states.pop();
		}
		if (!states.empty())
		{
			states.top()->resume();
		}
		is_popped = false;
	}

}

void StateMachine::pop_state() {
	is_popped = true; //we set flag to pop the state and quit to previous one
}


void StateMachine::update() {
	states.top()->update();
}
void StateMachine::draw()
{
	if (states.empty())
		return;
	states.top()->draw();

}

void StateMachine::run(std::unique_ptr<State> _state) {
	if(!states.empty())
	{
		states.top()->pause();
	}
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

