//
// Created by Missqu on 1/21/25.
//

#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "State.h"
#include<SFML/Graphics.hpp>
class StateMachine;
namespace sf
{
	class RenderWindow;
}
class MenuState : public State {
	public:
	MenuState(StateMachine &_machine_ref, sf::RenderWindow &_okno);
	 void pause() override;
	 void resume() override;
	 void update() override;
	 void draw() override;
private:

};



#endif //MENUSTATE_H
