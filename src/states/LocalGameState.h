//
// Created by Missqu on 1/21/25.
//

#ifndef LOCALGAMESTATE_H
#define LOCALGAMESTATE_H

#include "../Game.h"
#include "State.h"
class Game;
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
	Game game_;
	sf::Sprite kolko_sprite_;
	sf::Sprite krzyzyk_sprite_;
	sf::Sprite board_sprite_;
	std::vector<sf::Sprite> sprites_to_draw_;

};


#endif //LOCALGAMESTATE_H
