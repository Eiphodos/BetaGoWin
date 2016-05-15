// Header for the Go class.

#ifndef GO_H
#define GO_H

#include <vector>
#include "intersection.h"
#include "player.h"

class Go
{
public:
	std::vector<Intersection*> tiles;
	void placeStone(int n, Player* p);
	Go(Player* p);
	Go();
};

#endif // GO_H