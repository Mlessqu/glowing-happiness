//
// Created by Missqu on 1/21/25.
//

#ifndef AIGAMESTATE_H
#define AIGAMESTATE_H

#include "State.h"

class StateMachine;
namespace sf
{
	class RenderWindow;
}
class AiGameState final : public State {
public:
	AiGameState(StateMachine &_machine_ref, sf::RenderWindow &_okno);
	void pause() override;
	void resume() override;
	void update() override;
	void draw() override;

};


#endif //AIGAMESTATE_H
