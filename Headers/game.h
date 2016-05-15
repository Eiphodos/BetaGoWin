#ifndef GAME_H
#define GAME_H

#include "go.h"
#include "player.h"
#include <vector>

using namespace std;

class Game
{
private:
	
	Player* opponent;
	Player* winner;
	Player player1;
	Player player2;
	Player player3;
	Player* noPlayer;
	vector<Intersection*> capturedThisTurn;
	
	bool compareState(vector<Color> s1, vector<Color> s2);
	void saveState();
	void nextPlayer();
	vector<int> getIndexes(vector<Intersection*> v);
public:
	vector<int> index_capturedThisTurn;
	Go board;
	Player* currentPlayer;
	vector<vector<Color>> states;
	void nextTurn();
	bool illegalPlacement(int n);
	bool willSelfCapture(Intersection* i, vector<int> v);
	bool isSuperKo(int n, vector<int> i);
	void captureIntersections(int n);
	void placeStone(int n);
	void passTurn();
	void newGame();
	Game();
	~Game();
	
};

#endif // GAME_H