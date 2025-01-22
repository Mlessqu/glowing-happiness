//
// Created by Missqu on 1/21/25.
//

#ifndef ONLINEHOSTSTATE_H
#define ONLINEHOSTSTATE_H

#include "State.h"
#include "../Game.h"
#include"SFML/Network.hpp"
class Game;
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
private:
	Game game_;
	sf::Sprite kolko_sprite_;
	sf::Sprite krzyzyk_sprite_;
	sf::Sprite board_sprite_;
	std::vector<sf::Sprite> sprites_to_draw_;
	sf::Text zwyciezca_tekst_;
	const std::optional<sf::Event> event_;
};


#endif //ONLINEHOSTSTATE_H
