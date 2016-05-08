// Implementation of the Go class.

#include "../Headers/intersection.h"
#include "../Headers/go.h"

Go::Go()
{
	Intersection* temp;
	for (int i = 0; i < 361; i++)
	{
		temp = new Intersection();
		tiles.push_back(temp);
	}
	for (int n = 0; n < 361; n++)
	{
		temp = tiles[n];
		if (n > 18)
			temp->setIntersectionNorth(tiles[n - 19]);
		if ( n < 342)
			temp->setIntersectionSouth(tiles[n + 19]);
		if (n % 19)
			temp->setIntersectionWest(tiles[n - 1]);
		if ((n +1) % 19)
			temp->setIntersectionEast(tiles[n + 1]);
	}
}

void Go::placeStone(int x, int y, Player* p)
{
	(*tiles[x + y * 19]).setStone();
	(*tiles[x + y * 19]).setOwner(p);
}

Intersection* Go::getIntersection(int n)
{
	return tiles[n];
}