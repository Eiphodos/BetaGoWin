// Implementation of the Game class.

#include "../Headers/go.h"
#include "../Headers/game.h"
#include "../Headers/player.h"
#include <vector>

using namespace std;

Game::Game()
{
	player1 = Player(Black, 0, 0);
	player2 = Player(White, 0, 6.5);
	player3 = Player(Neutral, 0, 0);
	currentPlayer = &player1;
	opponent = &player2;
	noPlayer = &player3;
	board = Go(noPlayer);
	saveState();
}

void Game::nextPlayer()
{
	if (currentPlayer->color == Black) {
		currentPlayer = &player2;
		opponent = &player1;
	}
	else if (currentPlayer->color == White) {
		currentPlayer = &player1;
		opponent = &player2;
	}

}

void Game::nextTurn()
{
	saveState();
	nextPlayer();
}

bool Game::illegalPlacement(int n)
{
	Intersection* i = board.tiles[n];
	if (i->hasStone)
		return true;
	vector<Intersection*> temp = i->captureTest(currentPlayer, noPlayer);
	vector<int> indexes = getIndexes(temp);
	bool illegal = isSuperKo(n, indexes) || willSelfCapture(i, indexes);
	if (!illegal) {
		capturedThisTurn.clear();
		capturedThisTurn.insert(capturedThisTurn.begin(), temp.begin(), temp.end());
		index_capturedThisTurn.clear();
		index_capturedThisTurn.insert(index_capturedThisTurn.begin(), indexes.begin(), indexes.end());
	}
	return illegal;
}

bool Game::willSelfCapture(Intersection* i, vector<int> v) {
	i->hasStone = true;
	i->owner = currentPlayer;
	bool selfCapture = !(i->hasLiberty() || v.size() != 0);
	i->hasStone = false;
	i->owner = noPlayer;
	return selfCapture;
}

bool Game::isSuperKo(int n, vector<int> i)
{
	bool superKo = false;
	vector<Color> newState = states.back();
	newState[n] = currentPlayer->color;
	for (int s = 0; s < i.size(); s++) {
		newState[i[s]] = Neutral;
	}
	for (int p = 0; p < states.size(); p++) {
		superKo = superKo || compareState(newState, states[p]);
	}
	return superKo;
}

bool Game::compareState(vector<Color> s1, vector<Color> s2) {
	bool sameState = true;
	for (int n = 0; n < s1.size(); n++) {
		sameState = sameState && s1[n] == s2[n];
	}
	return sameState;
}

void Game::placeStone(int n)
{
	currentPlayer->passed = false;
	board.placeStone(n, currentPlayer);
}

void Game::captureIntersections(int n)
{
	placeStone(n);
	for (int i = 0; i < capturedThisTurn.size(); i++) {
		capturedThisTurn[i]->captureIntersection(noPlayer);
	}
}

void Game::saveState()
{
	vector<Color> currentState;
	for (int n = 0; n < board.tiles.size(); n++)
	{
		currentState.push_back(board.tiles[n]->owner->color);
	}
	states.push_back(currentState);
}

void Game::passTurn() {
	currentPlayer->passed = true;
	nextTurn();
}

void Game::newGame() {

}

vector<int> Game::getIndexes(vector<Intersection*> v) {
	vector<int> indexes;
	int s;
	for (int i = 0; i < v.size(); i++)
	{
		auto it = find(board.tiles.begin(), board.tiles.end(), v[i]);
		s = distance(board.tiles.begin(), it);
		indexes.push_back(s);
	}
	return indexes;
}