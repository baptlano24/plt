#include "ai.h"
#include "../state/State.h"
#include "Vertex.h"
#include "engine.h"
#include <unistd.h>
#include <iostream>
#include "Action.h"

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;

Vertex::Vertex(state::State& CurrentState){
  this->parent = NULL;
  this->children = std::vector<Vertex*>();
  this->myAnimals = std::vector<state::Animal>();
  this->hisAnimals = std::vector<state::Animal>();
  if(CurrentState.getPlaying() == 0){
    for (int i =0; i<=(int)CurrentState.getPlayer1().getAnimals().size(); i++){
      if(CurrentState.getPlayer1().getAnimals()[i].getStatus()==NORMAL)
      {
        this->myAnimals.push_back(CurrentState.getPlayer1().getAnimals()[i]);
      }
    }
    for (int j=0; j<=(int)CurrentState.getPlayer2().getAnimals().size();j++){
      if(CurrentState.getPlayer2().getAnimals()[j].getStatus()==NORMAL)
      {
        this->hisAnimals.push_back(CurrentState.getPlayer2().getAnimals()[j]);
      }
    }
  }

  else{
    for (int i =0; i<=(int)CurrentState.getPlayer2().getAnimals().size(); i++){
      if(CurrentState.getPlayer2().getAnimals()[i].getStatus()==NORMAL)
      {
        this->myAnimals.push_back(CurrentState.getPlayer2().getAnimals()[i]);
      }}
    for (int j=0; j<=(int)CurrentState.getPlayer1().getAnimals().size();j++)
    {
      if(CurrentState.getPlayer1().getAnimals()[j].getStatus()==NORMAL)
      {
        this->hisAnimals.push_back(CurrentState.getPlayer1().getAnimals()[j]);
      }

    }
  }
}

Vertex::~Vertex(){
	//delete predecesseur;
}

Vertex* Vertex:: getParent(){
  return this->parent;
}

std::vector<state::Animal>* Vertex:: getMyAnimals (){
  return &this->myAnimals;
}

std::vector<state::Animal>* Vertex:: getHisAnimals (){
  return &this->hisAnimals;
}

std::vector<Vertex*> Vertex:: getChildren (){
  return this->children;
}

ai::Action Vertex:: getAction (){
  return this->action;
}

void Vertex::setAction (ai::Action newaction){
   this->action = newaction;
}

/*state::Coord& Vertex::getCoord(){
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
