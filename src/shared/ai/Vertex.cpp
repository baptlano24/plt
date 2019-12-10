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
  this->playing = CurrentState.getPlaying();
  if(this->playing == 0){
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

Vertex::Vertex(Vertex* vertex, Action action){
  this->parent = vertex;
  this->myAnimals = *vertex->getMyAnimals();
  this->hisAnimals = *vertex->getHisAnimals();
  this->playing = 1 - vertex->getPlaying();
  Animal* movedAnimal;
  for(int i; i<=(int)this->myAnimals.size();i++){
    if(this->myAnimals[i].getCoord() == action.getAnimal()->getCoord()){
      movedAnimal = &this->myAnimals[i];
    }
  }
  switch(action.getId())
  {
    case NONE :
      break;
    case SHIFT :
      movedAnimal->setCoord(*action.getCoord());
      break;
    case ATTACK :
      for(int i; i<=(int)this->hisAnimals.size();i++){
        if(this->hisAnimals[i].getCoord() == *action.getCoord()){
          this->hisAnimals.erase(this->hisAnimals.begin()+i);
        }
      }
      movedAnimal->setCoord(*action.getCoord());
      break;
    case JUMP :
      movedAnimal->setCoord(*action.getCoord());
      break;
    case SHIFT_TRAPPED :
      movedAnimal->setCoord(*action.getCoord());
      break;
    case SHIFT_VICTORY :
      movedAnimal->setCoord(*action.getCoord());
      break;
  }
  vertex->addChild(this);
}

Vertex::~Vertex(){
	//delete himself;
}

void Vertex::addChild(Vertex* child){
  this->children.push_back(child);
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

Action Vertex:: getAction (){
  return this->action;
}

int Vertex:: getPlaying (){
  return this->playing;
}

void Vertex::setAction (ai::Action newaction){
   this->action = newaction;
}

pair<Animal*, int> Vertex::getSelection(Vertex* vertex, Coord coord)
{
  pair<Animal*, int> selection;
  selection.first = NULL;
  selection.second = 666;
  std::vector<state::Animal>* myAnimals = vertex->getMyAnimals();
  std::vector<state::Animal>* hisAnimals = vertex->getHisAnimals();

  for (int i = 0; i<=(int)myAnimals->size(); i++) {
    if (myAnimals->at(i).getCoord() == coord ) {
      selection.first = &myAnimals->at(i);
      if(vertex->getPlaying() == 0){
        selection.second = 0;
      } else {
        selection.second = 1;
      }
    }
  }
  for (int i= 0; i<=(int)hisAnimals->size(); i++) {
    if (hisAnimals->at(i).getCoord() == coord ) {
      selection.first = &hisAnimals->at(i);
      if(vertex->getPlaying() == 0){
        selection.second = 1;
      } else {
        selection.second = 0;
      }
    }
  }
  return selection;
}
