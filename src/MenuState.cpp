//
// Created by Missqu on 1/21/25.
//

#include "MenuState.h"
#include "button.hpp"
#include <iostream>

MenuState::MenuState(StateMachine &_machine_ref, sf::RenderWindow &_okno) : State { _machine_ref,_okno}
{
		std::cout << "Menu state intialized" << std::endl;

}
void MenuState::draw()
{

}

void MenuState::update()
{

}

void MenuState::pause()
{

}

void MenuState::resume()
{

}


