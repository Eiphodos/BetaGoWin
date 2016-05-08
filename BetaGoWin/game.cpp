// Implementation of the Game class.

#include "../Headers/go.h"
#include "../Headers/game.h"
#include "../Headers/player.h"

Game::Game()
{
	player1 = Player(Black, 0, 0);
	player2 = Player(White, 0, 6.5);
	currentPlayer = &player1;
	board = Go();
//	Intersection* lastStoneCaptured; // Used for Ko rules.
//	int numberOfStonesLastCaptured;  // Used for Ko rules.
}

void Game::nextPlayer()
{
	if ((*currentPlayer).getColor() == Black)
		currentPlayer = &player2;
	else if ((*currentPlayer).getColor() == White)
		currentPlayer = &player1;

}

Player* Game::getCurrentPlayer()
{
	return currentPlayer;
}

bool Game::isLegalPlacement(int n, Player* p)
{
/*	Intersection* i = board.getIntersection(n);
	(*i).hasStone;
	(*i).getOwner() == nullptr;*/
	return true;
}