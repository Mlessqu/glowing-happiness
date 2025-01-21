//
// Created by Missqu on 1/21/25.
//

#ifndef ONLINEHOSTSTATE_H
#define ONLINEHOSTSTATE_H

#include "State.h"

class StateMachine;
namespace sf
{
	class RenderWindow;
}

class OnlineHostState : public State{
public:
	OnlineHostState(StateMachine &_machine_ref, sf::RenderWindow &_okno);
	void pause() override;
	void resume() override;
	void update() override;
	void draw() override;
};


#endif //ONLINEHOSTSTATE_H
