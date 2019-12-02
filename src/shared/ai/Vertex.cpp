/*#include "ai.h"
#include "../state/State.h"
#include "Vertex.h"
#include "engine.h"
#include <unistd.h>
#include <iostream>

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;

Vertex::Vertex(Vertex* predecesseur):predecesseur(predecesseur){
	position.setX(0);
	position.setY(0);
	distanceSource=0;
  distanceDestination=0;

}


Vertex::Vertex(){
	new (this) Vertex(NULL);
}

Vertex::~Vertex(){
	//delete predecesseur;
}


state::Coord& Vertex::getCoord(){
	Coord& refCoord = position;
	return refCoord ;
}

void Vertex::setCoord(state::Coord newCoord){
	position.setX(newCoord.getX());
	position.setY(newCoord.getY());
}
Vertex* Vertex::getPredecesseur(){
	return predecesseur;
}

const Vertex* Vertex::getPredecesseurC(){
	const Vertex* constpred=predecesseur;
	return constpred;
}

void Vertex::setPredecesseur(Vertex* newPredecesseur){
	predecesseur = newPredecesseur;
}

void Vertex::setPredecesseurC(const Vertex* newPredecesseur){
	Vertex thing =*newPredecesseur;
	predecesseur = &thing;
}

int Vertex::getDistanceSource(){
	return distanceSource;
}

void Vertex::setDistanceSource(int newDistanceSource){
	distanceSource = newDistanceSource;
}

int Vertex::getDistanceDestination(){
	return distanceDestination;
}

void Vertex::setDistanceDestination(int newDistanceDestination){
	distanceDestination = newDistanceDestination;
}

int Vertex::getTotalCount(){
	return distanceSource + distanceDestination;
}
*/
