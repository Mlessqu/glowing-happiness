//
// Created by Missqu on 1/21/25.
//

#ifndef LOCALGAMESTATE_H
#define LOCALGAMESTATE_H

#include "State.h"

class StateMachine;
namespace sf
{
	class RenderWindow;
}
class LocalGameState final : public State {
public:
	LocalGameState(StateMachine &_machine_ref, sf::RenderWindow &_okno);
	void pause() override;
	void resume() override;
	void update() override;
	void draw() override;
private:

};


#endif //LOCALGAMESTATE_H
