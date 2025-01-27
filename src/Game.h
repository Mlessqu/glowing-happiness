//
// Created by Missqu on 1/21/25.
//

#ifndef GAME_H
#define GAME_H
#include "NetworkData.h"

#include "SFML/Graphics.hpp"

enum Turn { pusto,krzyzyk,kolko};

class Game
{
public:
	explicit Game(bool _czy_krzyzyk);
	void end_game();
	bool make_turn(int _wybor,Turn _tura);
	Turn czyja_tura();
	bool check_winner();
	bool is_legal_move(int _wybor);
	bool logic(int _wybor,Turn _who_attempts);
	NetworkData get_data_for_network();
	private:
	int tura_=0;
	std::array<int,9> board_ = {};
	bool wygrana_ = false;
	bool player2 = false;
	bool player1 = false;

};



#endif //GAME_H
