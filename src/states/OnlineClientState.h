//
// Created by Missqu on 1/21/25.
//

#ifndef ONLINECLIENTSTATE_H
#define ONLINECLIENTSTATE_H
#include "State.h"
#include  "../Game.h"
#include <SFML/Network.hpp>
#include <thread>
#include "../NetworkData.h"
class Game;
class StateMachine;
namespace sf
{
	class TcpSocket;
	class RenderWindow;
}

class OnlineClientState : public State{
public:
	OnlineClientState(StateMachine &_machine_ref, sf::RenderWindow &_okno);
	void pause() override;
	void resume() override;
	void update(sf::Time& _delta_time, sf::Time& _lag) override;
	void draw() override;
	void send_packet();
private:
	Game game_;
	sf::Sprite kolko_sprite_;
	sf::Sprite krzyzyk_sprite_;
	sf::Sprite board_sprite_;
	std::vector<sf::Sprite> sprites_to_draw_;
	sf::Text zwyciezca_tekst_;
	sf::TcpSocket socket_;
	bool my_turn = false;
	NetworkData network_data_;
	sf::Packet network_packet_;
};



#endif //ONLINECLIENTSTATE_H
