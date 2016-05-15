// Header for the Intersection class.

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "player.h"
#include <vector>

using namespace std;

class Intersection
{
public:
	Player* owner;
	Intersection* intersectionNorth;
	Intersection* intersectionSouth;
	Intersection* intersectionWest;
	Intersection* intersectionEast;
	bool hasStone;
	bool isChecked;
	bool hasLiberty();
	bool hasFriendlyStone(Player* p);
	bool hasEnemyStone(Player* p);
	void captureIntersection(Player* noPlayer);
	vector<Intersection*> captureTest(Player* p, Player* noPlayer);
	vector<Intersection*> capturedConnections();
	Intersection();
};

#endif // INTERSECTION_H