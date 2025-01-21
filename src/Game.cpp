//
// Created by Missqu on 1/21/25.
//

#include "Game.h"
#include <iostream>

enum Turn;
Game::Game()
{
	for (int i =0;i < PLACES;i++)
	{
		board_[i]=0;
	}
	tura_=0;
}


void Game::end_game()
{
	//if somebody wins
	if (check_winner())
	{
		if (czyja_tura() == krzyzyk)
		{
			std::cout << "Wygrał krzyzyk!";
		}else if (czyja_tura() == kolko)
		{
			std::cout << "Wygralo kolko!";
		}else if(tura_ == 8)//mamy remis
		{
				std::cout << "Remis";
		}
	}
}

bool Game::make_turn(int _wybor) //we return true on sucesful turn
{
		if (is_legal_move(_wybor)==false)
		{
			return false;
		}
		board_[_wybor] = czyja_tura();
	++tura_;
	return true;
}

Turn Game::czyja_to_byla(int _wybor)
{
	if (tura_ %2)
	{
		return kolko;
	}else
	{
		return krzyzyk;
	}
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
	// [0][0].[1][1],[2][2] //pierwszy diagonal
	// [0][2],[1][1],[2][0] //drugi diagonal
	// [n][0],[n][1],[n][2] //wiersze
	// [0][n],[1][n],[2][n] //kolumny */
	if ((board_[0] == board_[4] && board_[4] == board_[8]) && board_[0] != 0)
		{
	return true;
	} // if all diagonal equal but not 0 then true
	if ((board_[6] == board_[4] && board_[4] == board_[2]) && board_[6] != 0)
	{
	return true;
	} // if all diagonal equal but not 0 then true
	for (int i = 0; i < 6; i = i + 3)
	{
		if ((board_[i] == board_[i + 1] && board_[i + 1] == board_[i + 2]) &&
		board_[i] != 0)
		{
			return true; // columns all equal but not 0
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if ((board_[i] == board_[i + 3] && board_[i + 3] == board_[i + 6]) &&
		board_[i] != 0)
		{
			return true; // row all equal but not 0
		}
	}
	return false; // otherwise no winner
	}

