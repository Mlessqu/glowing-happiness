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
	void init(std::array<int,9> _board,int _tura);
	void end_game();
	bool make_turn(int _wybor);
	Turn czyja_to_byla();
	std::array<int,9> get_current_board_state() const;
	int get_current_turn() const;
	void update();
	void debug_info();
	void reset();
	int get_current_wybor() const { return current_wybor_;}
private:

	int current_wybor_;
	bool is_legal_move(int _wybor);
	Turn czyja_tura();
	int tura_=0;
	std::array<int,9> board_ = {};
	bool check_winner();
	bool wygrana_ = false;



};



#endif //GAME_H
