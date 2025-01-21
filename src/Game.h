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
	Game();
	void end_game();
	bool make_turn(int _wybor);
	Turn czyja_to_byla(int _wybor);
	void update();
private:

	const int PLACES = 9;
	bool is_legal_move(int _wybor);
	Turn czyja_tura();
	int tura_=0;
	int board_[9]{};
	bool check_winner();




};



#endif //GAME_H
