// Header for the Intersection class.

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "player.h"

class Intersection
{
private:
	Player* owner;
	Intersection* intersectionNorth;
	Intersection* intersectionSouth;
	Intersection* intersectionWest;
	Intersection* intersectionEast;
public:
	bool inAtari();
	bool hasStone;
//	bool isLibertyTo(Intersection* t1, Intersection* t2);
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
