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
    this->myAnimals = CurrentState.getPlayer1().getAliveAnimals();
    this->hisAnimals = CurrentState.getPlayer2().getAliveAnimals();
  } else {
    this->myAnimals = CurrentState.getPlayer2().getAliveAnimals();
    this->hisAnimals = CurrentState.getPlayer1().getAliveAnimals();
  }
}

Vertex::Vertex(Vertex* vertex, Action action){
  this->parent = vertex;
  this->children = std::vector<Vertex*>();
  this->myAnimals = *vertex->getMyAnimals();
  this->hisAnimals = *vertex->getHisAnimals();
  this->playing = 1 - vertex->getPlaying();
  this->action = action;

  Animal* movedAnimal;
  for(auto& myAnimal : myAnimals){
    if(myAnimal.getCoord() == action.getAnimal()->getCoord()){
      movedAnimal = &myAnimal;
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
      for(int i=0; i<(int)this->hisAnimals.size();i++){
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
  killChildren(this);
}

void Vertex::killChildren(Vertex* vertex){
  if((int)this->children.size() == 0){
    for(auto& child : this->children){
      delete &child;
    }
  }
}

void Vertex::addChild(Vertex* child){
  this->children.push_back(child);
}

Vertex* Vertex:: getParent(){
  return this->parent;
}

std::vector<state::Animal>* Vertex::getMyAnimals (){
  return &this->myAnimals;
}

std::vector<state::Animal>* Vertex::getHisAnimals (){
  return &this->hisAnimals;
}

std::vector<Vertex*>* Vertex:: getChildren (){
  return &this->children;
}

Action* Vertex::getAction (){
  return &this->action;
}

int Vertex::getPlaying (){
  return this->playing;
}

void Vertex::setAction(ai::Action newaction){
   this->action = newaction;
}
