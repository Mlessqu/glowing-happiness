//
// Created by Missqu on 1/21/25.
//

#ifndef ONLINECLIENTSTATE_H
#define ONLINECLIENTSTATE_H
#include "State.h"


class StateMachine;
namespace sf
{
	class RenderWindow;
}

class OnlineClientState : public State{
public:
	OnlineClientState(StateMachine &_machine_ref, sf::RenderWindow &_okno);
	void pause() override;
	void resume() override;
	void update() override;
	void draw() override;
};



#endif //ONLINECLIENTSTATE_H
