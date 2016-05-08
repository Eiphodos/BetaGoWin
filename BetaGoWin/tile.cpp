// Implementation of the Intersection class.

#include "../Headers/intersection.h"

Intersection::Intersection()
{
	hasStone = false;
	isSurrounded = false;
	isCaptured = false;
	Intersection* intersectionNorth = nullptr;
	Intersection* intersectionSouth = nullptr;
	Intersection* intersectionWest = nullptr;
	Intersection* intersectionEast = nullptr;
}


bool Intersection::inAtari()
{
	return true;
}

void Intersection::setStone()
{
	hasStone = true;
}

void Intersection::setOwner(Player* p)
{
	owner = p;
}

void Intersection::setIntersectionNorth(Intersection* t)
{
	intersectionNorth = t;
}

void Intersection::setIntersectionSouth(Intersection* t)
{
	intersectionSouth = t;
}

void Intersection::setIntersectionEast(Intersection* t)
{
	intersectionEast = t;
}

void Intersection::setIntersectionWest(Intersection* t)
{
	intersectionWest = t;
}

Player* Intersection::getOwner()
{
	return owner;
}