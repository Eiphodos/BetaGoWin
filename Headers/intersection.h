// Header for the Intersection class.

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "player.h"
#include <vector>
#include <memory>

using namespace std;

class Intersection: enable_shared_from_this<Intersection>
{
public:
	Player* owner;
	shared_ptr<Intersection> intersectionNorth;
	shared_ptr<Intersection> intersectionSouth;
	shared_ptr<Intersection> intersectionWest;
	shared_ptr<Intersection> intersectionEast;
	shared_ptr<Intersection> intersectionSelf;
	bool hasStone;
	bool isChecked;
	bool hasLiberty();
	bool hasFriendlyStone(Player* p);
	bool hasEnemyStone(Player* p);
	void captureIntersection(Player* noPlayer);
	vector<shared_ptr<Intersection>> captureTest(Player* p, Player* noPlayer);
	vector<shared_ptr<Intersection>> capturedConnections();
	Intersection();
};

#endif // INTERSECTION_H