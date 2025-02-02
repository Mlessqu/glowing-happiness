//
// Created by Missqu on 1/21/25.
//

#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "State.h"
#include "../gui/Button.h"
class StateMachine;
namespace sf
{
	class RenderWindow;
}
class MenuState final : public State {
	public:
	MenuState(StateMachine &_machine_ref, sf::RenderWindow &_okno);
	 void pause() override;
	 void resume() override;
	 void update(sf::Time& _delta_time, sf::Time& _lag) override;
	 void draw() override;
private:
	std::vector<std::unique_ptr<Button>> buttons_;
};



#endif //MENUSTATE_H
