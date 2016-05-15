// Implementation of the Intersection class.

#include "../Headers/intersection.h"
#include <vector>

using namespace std;

Intersection::Intersection()
{
	hasStone = false;
	Intersection* intersectionNorth = nullptr;
	Intersection* intersectionSouth = nullptr;
	Intersection* intersectionWest = nullptr;
	Intersection* intersectionEast = nullptr;
}

bool Intersection::hasLiberty()
{
	bool connectedLiberty = true;
	bool libN = false;
	bool libS = false;
	bool libE = false;
	bool libW = false;
	isChecked = true;
	if (intersectionNorth) {
		if (!(intersectionNorth->hasStone)) {
			isChecked = false;
			return connectedLiberty;
		}
		if (!(intersectionNorth->isChecked) && intersectionNorth->hasFriendlyStone(owner))
			libN = intersectionNorth->hasLiberty();
	}
	if (intersectionSouth) {
		if (!(intersectionSouth->hasStone)) {
			isChecked = false;
			return connectedLiberty;
		}
		if (!(intersectionSouth->isChecked) && intersectionSouth->hasFriendlyStone(owner))
			libS = intersectionSouth->hasLiberty();
	}
	if (intersectionEast) {
		if (!(intersectionEast->hasStone)) {
			isChecked = false;
			return connectedLiberty;
		}
		if (!(intersectionEast->isChecked) && intersectionEast->hasFriendlyStone(owner))
			libE = intersectionEast->hasLiberty();
	}
	if (intersectionWest) {
		if (!(intersectionWest->hasStone)) {
			isChecked = false;
			return connectedLiberty;
		}
		if (!(intersectionWest->isChecked) && intersectionWest->hasFriendlyStone(owner))
			libW = intersectionWest->hasLiberty();
	}
	connectedLiberty = libN || libS || libE || libW;
	isChecked = false;
	return connectedLiberty;
}

bool Intersection::hasFriendlyStone(Player* p)
{
	return (hasStone && (owner == p));
}

bool Intersection::hasEnemyStone(Player* p)
{
	if (p->color == White)
		return (hasStone && owner->color == Black);
	if (p->color == Black)
		return (hasStone && owner->color == White);
	else
		return false;
}

void Intersection::captureIntersection(Player* noPlayer)
{
	owner = noPlayer;
	hasStone = false;
}

vector<Intersection*> Intersection::capturedConnections()
{
	vector<Intersection*> connectedCaptures;
	vector<Intersection*> temp;
	isChecked = true;
	connectedCaptures.push_back(this);
	if (intersectionNorth) {
		if (intersectionNorth->hasFriendlyStone(owner) && !(intersectionNorth->isChecked)) {
			temp = intersectionNorth->capturedConnections();
			connectedCaptures.insert(connectedCaptures.end(), temp.begin(), temp.end());
		}
	}
	if (intersectionSouth) {
		if (intersectionSouth->hasFriendlyStone(owner) && !(intersectionSouth->isChecked)) {
			temp = intersectionSouth->capturedConnections();
			connectedCaptures.insert(connectedCaptures.end(), temp.begin(), temp.end());
		}
	}
	if (intersectionEast) {
		if (intersectionEast->hasFriendlyStone(owner) && !(intersectionEast->isChecked)) {
			temp = intersectionEast->capturedConnections();
			connectedCaptures.insert(connectedCaptures.end(), temp.begin(), temp.end());
		}
	}
	if (intersectionWest){
		if (intersectionWest->hasFriendlyStone(owner) && !(intersectionWest->isChecked)) {
			temp = intersectionWest->capturedConnections();
			connectedCaptures.insert(connectedCaptures.end(), temp.begin(), temp.end());
		}
	}
	return connectedCaptures;
}

vector<Intersection*> Intersection::captureTest(Player* p, Player* noPlayer) {
	vector<Intersection*> willBeCaptured;
	vector<Intersection*> temp;
	owner = p;
	hasStone = true;
	if (intersectionNorth) {
		if (intersectionNorth->hasEnemyStone(owner) && !intersectionNorth->hasLiberty()) {
			temp = intersectionNorth->capturedConnections();
			willBeCaptured.insert(willBeCaptured.end(), temp.begin(), temp.end());
		}
	}
	if (intersectionSouth) {
		if (intersectionSouth->hasEnemyStone(owner) && !intersectionSouth->hasLiberty()) {
			temp = intersectionSouth->capturedConnections();
			willBeCaptured.insert(willBeCaptured.end(), temp.begin(), temp.end());
		}
	}
	if (intersectionEast) {
		if (intersectionEast->hasEnemyStone(owner) && !intersectionEast->hasLiberty()) {
			temp = intersectionEast->capturedConnections();
			willBeCaptured.insert(willBeCaptured.end(), temp.begin(), temp.end());
		}
	}
	if (intersectionWest) {
		if (intersectionWest->hasEnemyStone(owner) && !intersectionWest->hasLiberty()) {
			temp = intersectionWest->capturedConnections();
			willBeCaptured.insert(willBeCaptured.end(), temp.begin(), temp.end());
		}
	}
	for (int i = 0; i < willBeCaptured.size(); i++){
		willBeCaptured[i]->isChecked = false;
	}
	owner = noPlayer;
	hasStone = false;
	return willBeCaptured;
}