#ifndef GAME_H
#define GAME_H

#include "go.h"
#include "player.h"


class Game
{
private:
	Player* currentPlayer;
	Player* winner;
	Player player1;
	Player player2;
	Go board;
	bool isLegalPlacement(int n, Player* p);

public:
	void nextPlayer();
	Player* getCurrentPlayer();
	Game();
};

#endif // GAME_H