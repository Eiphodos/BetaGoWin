// Implementation of the Go class.

#include "../Headers/intersection.h"
#include "../Headers/go.h"
#include "../Headers/player.h"

Go::Go(Player* p)
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
		temp->owner = p;
		if (n > 18)
			temp->intersectionNorth = tiles[n - 19];
		if ( n < 342)
			temp->intersectionSouth = tiles[n + 19];
		if (n % 19)
			temp->intersectionWest = tiles[n - 1];
		if ((n +1) % 19)
			temp->intersectionEast = tiles[n + 1];
	}
}

Go::Go(){}

void Go::placeStone(int n, Player* p)
{
	tiles[n]->hasStone = true;
	tiles[n]->owner = p;
}