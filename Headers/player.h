// Header for the Player class.

#ifndef PLAYER_H
#define PLAYER_H

enum Color { Black, White, Neutral };

class Player
{
private:
	int handicap;
	int capturedStones;
	double score;
	double komi;
public:
	Color color;
	double getScore();
	Player(Color c, int h, double k);
	Player();
};

#endif // PLAYER_H