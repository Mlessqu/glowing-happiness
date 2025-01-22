//
// Created by Missqu on 1/21/25.
//

#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"

enum Turn { pusto,krzyzyk,kolko};

class Game
{
public:
	Game(bool _czy_krzyzyk);
	void end_game();
	bool make_turn(int _wybor,Turn);
	Turn czyja_tura();
	bool check_winner();
	bool is_legal_move(int _wybor);
	void logic(int _wybor);
	bool player1 = true;
	private:
	int tura_=0;
	std::array<int,9> board_ = {};
	bool wygrana_ = false;
	bool player2 = false;


};



#endif //GAME_H
