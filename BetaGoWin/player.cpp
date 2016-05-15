// Implementation of the Go class.

#include "../Headers/player.h"

Player::Player()
{
	handicap = 0;
	komi = 0;
	score = 0;
	capturedStones = 0;
}

Player::Player(Color c, int h, double k)
{
	color = c;
	handicap = h;
	komi = k;
	score = 0 + komi;
	capturedStones = 0;
}