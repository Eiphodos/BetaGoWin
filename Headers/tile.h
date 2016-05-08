// Header for the Intersection class.

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "player.h"

class Intersection
{
private:
	Player* owner;
	bool hasStone;
	bool isSurrounded;
	bool isCaptured;
	Intersection* intersectionNorth;
	Intersection* intersectionSouth;
	Intersection* intersectionWest;
	Intersection* intersectionEast;
public:
	bool inAtari();
	void setStone();
	void setOwner(Player* p);
	void setIntersectionNorth(Intersection* t);
	void setIntersectionSouth(Intersection* t);
	void setIntersectionWest(Intersection* t);
	void setIntersectionEast(Intersection* t);
	Player* getOwner();
	Intersection();
};

#endif // INTERSECTION_H
