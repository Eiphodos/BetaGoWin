// Header for the Player class.

#ifndef PLAYER_H
#define PLAYER_H

enum Color { Black, White };

class Player
{
private:
	Color color;
	int handicap;
	int capturedStones;
	double score;
	double komi;
public:
	double getScore();
	Color getColor();
	Player(Color c, int h, double k);
	Player();
};

#endif // PLAYER_H