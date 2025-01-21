//
// Created by Missqu on 1/16/25.
//

#include "State.h"

#include "ResourceManager.h"


State::State(StateMachine &_machine_ref, sf::RenderWindow &_okno):
machine_ref_{_machine_ref},
okno_ref_{_okno},
resource_manager_ref_{ResourceManager::get_instance()}
{

}

std::unique_ptr<State> State::next_state()
{
	return std::move(next_state_ptr_);
}