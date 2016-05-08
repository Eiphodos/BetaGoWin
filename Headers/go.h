// Header for the Go class.

#ifndef GO_H
#define GO_H

#include <vector>
#include "intersection.h"
#include "player.h"


class Go
{
private:
	std::vector<Intersection*> tiles;
public:
	void placeStone(int x, int y, Player* p);
	Intersection* getIntersection(int n);
	Go();
};

#endif // GO_H