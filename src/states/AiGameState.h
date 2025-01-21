//
// Created by Missqu on 1/21/25.
//

#ifndef AIGAMESTATE_H
#define AIGAMESTATE_H

#include "State.h"
#include "../Game.h"
class StateMachine;
class Game;
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
private:
	Game game_;
	sf::Sprite kolko_sprite_;
	sf::Sprite krzyzyk_sprite_;
	sf::Sprite board_sprite_;
	std::vector<sf::Sprite> sprites_to_draw_;
	sf::Text zwyciezca_tekst_;
};


#endif //AIGAMESTATE_H
