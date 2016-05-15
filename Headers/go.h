// Header for the Go class.

#ifndef GO_H
#define GO_H

#include <vector>
#include "intersection.h"
#include "player.h"
#include <memory>

class Go
{
public:
	std::vector<shared_ptr<Intersection>> tiles;
	void placeStone(int n, Player* p);
	Go(Player* p);
	Go();
	Go(Go&&) = default;
	Go(const Go&) = default;
	Go& operator=(const Go&) = default;
	~Go();
};

#endif // GO_H