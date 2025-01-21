//
// Created by Missqu on 1/21/25.
//

#include "Game.h"
#include <iostream>

#include "Utility.h"

enum Turn;
Game::Game()
{

	tura_=0;
}

void Game::init(std::array<int, 9> _board, int _tura)
{
	board_ = _board;
	tura_ = _tura;

}


void Game::debug_info()
{
	draw_line(7);
	std::cout << "\n";
	int counter = 0;
	for (int i = 0; i < 18; i++) {
		if (counter == 9) {
			std::cout << "shit";
			return;
		}
		if (!(i % 2)) {
			std::cout << "#";
		} else {
			std::cout << draw_sign(board_[counter]);
			counter++;
		}
		const int enter_after = 6;
		if (((i % enter_after) == 0) && i != 0)
			std::cout << "\n#";
	}
	std::cout << "#\n";
	draw_line(6);
	std::cout << "\n";
	std::cout << "Tura: " << tura_ << std::endl;

}

void Game::reset()
{
	// reset rundy
}


void Game::end_game()
{
	//if somebody wins
		Turn enum_turn = czyja_to_byla();
	if(tura_ == 8)//mamy remis
	{
		std::cout << "Remis";
		return;
	}
		if (enum_turn == krzyzyk)
		{
			std::cout << "Wygrał krzyzyk!";
			return;
		}else if (enum_turn == kolko)
		{
			std::cout << "Wygralo kolko!";
			return;
		}
}

bool Game::make_turn(int _wybor) //we return true on sucesful turn
{
	current_wybor_ = _wybor;
	if (wygrana_ == true)
		return false;

		if (is_legal_move(_wybor)==false)
		{
			return false;
		}
		board_[_wybor] = czyja_tura(); //actual move here

	++tura_; //increment tura
	if (check_winner()) //na samym koncu check if there is a winner
	{
		//who won?
		std::cout << "inside check_winner, before end_game()" << std::endl;
		end_game();
		wygrana_ = true;
	}
	debug_info();
	std::cout << "Wybor:" <<  _wybor << std::endl;
	return true;
}

Turn Game::czyja_to_byla()
{
	if (tura_ %2)
	{
		return kolko;
	}else
	{
		return krzyzyk;
	}
}

std::array<int, 9> Game::get_current_board_state() const
{
	return board_;
}

int Game::get_current_turn() const {
	return tura_;
}



void Game::update()
{

}



bool Game::is_legal_move(int _wybor)
{
	if(_wybor<0 || _wybor>=9) //wybor jest poza range od 0-8 włącznie
	{
		return false;
	}
	if (board_[_wybor] != 0) //zajeta kratka juz not legal move
	{
		return false;
	}
	return true;
}

Turn Game::czyja_tura()
{
		if (tura_ %2)
		{
			return krzyzyk;
		}else
		{
			return kolko;
		}
}

bool Game::check_winner() //checks if current board has any winner
{
	/* let 0 - empty, 1 - krzyzyk, 2- kolko
	// [0][0],[1][1],[2][2] //pierwszy diagonal
	// [0][2],[1][1],[2][0] //drugi diagonal
	// [n][0],[n][1],[n][2] //wiersze
	// [0][n],[1][n],[2][n] //kolumny */
	if((board_[0] == board_[4]) && (board_[4] == board_[8]) && board_[0] != 0)
	{
	return true;
	} // if all diagonal equal but not 0 then true
	if ((board_[6] == board_[4]) && (board_[4] == board_[2]) && board_[6] != 0)
	{
	return true;
	} // if all diagonal equal but not 0 then true
	for (int i = 0; i < 7; i = i + 3)
	{
		if (((board_[i] == board_[i + 1]) && (board_[i + 1] == board_[i + 2])) &&
		board_[i] != 0)
		{
			return true; // columns all equal but not 0
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (((board_[i] == board_[i + 3]) && (board_[i + 3] == board_[i + 6])) &&
		board_[i] != 0)
		{
			return true; // row all equal but not 0
		}
	}
	return false; // otherwise no winner
	}

