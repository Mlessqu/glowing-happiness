//
// Created by Missqu on 1/21/25.
//

#ifndef ONLINECLIENTSTATE_H
#define ONLINECLIENTSTATE_H
#include "State.h"
#include  "../Game.h"
class Game;
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
private:
	Game game_;
	sf::Sprite kolko_sprite_;
	sf::Sprite krzyzyk_sprite_;
	sf::Sprite board_sprite_;
	std::vector<sf::Sprite> sprites_to_draw_;
	sf::Text zwyciezca_tekst_;
};



#endif //ONLINECLIENTSTATE_H
