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
  this->playing = CurrentState.getPlaying();
  if(this->playing == 0){
    this->myAnimals = CurrentState.getPlayer1().getAliveAnimals();
    this->hisAnimals = CurrentState.getPlayer2().getAliveAnimals();
  } else {
    this->myAnimals = CurrentState.getPlayer2().getAliveAnimals();
    this->hisAnimals = CurrentState.getPlayer1().getAliveAnimals();
  }
}

Vertex::Vertex(Vertex* vertex, Action& action):action(action){
  this->parent = vertex;
  this->playing = 1 - vertex->getPlaying();
  this->myAnimals = *vertex->getMyAnimals();
  this->hisAnimals = *vertex->getHisAnimals();
  Coord actionDestinationCoord = this->action.getCoord();
  Coord actionAnimalCoord = this->action.getAnimal().getCoord();
  Animal* movedAnimal;

  for(auto& myAnimal : myAnimals){
    if(myAnimal.getCoord() == actionAnimalCoord){
      movedAnimal = &myAnimal;
    }
  }
  /*if(movedAnimal){
    cout << "     Animal is a "<< movedAnimal->getName()<< " and wants to go in (" << actionDestinationCoord.getX() << "," << actionDestinationCoord.getY() << ")" << endl;
  }
  cout<<"       create vertex with ActionID "<<this->action.getId()<<endl;*/
  switch(this->action.getId())
  {
    case NONE :
      break;
    case SHIFT :
      movedAnimal->setCoord(actionDestinationCoord);
      break;
    case ATTACK :
      for(int i=0; i<(int)this->hisAnimals.size();i++){
        if(this->hisAnimals[i].getCoord() == actionDestinationCoord){
          this->hisAnimals.erase(this->hisAnimals.begin()+i);
        }
      }
      movedAnimal->setCoord(actionDestinationCoord);
      break;
    case JUMP :
      movedAnimal->setCoord(actionDestinationCoord);
      break;
    case SHIFT_TRAPPED :
      movedAnimal->setCoord(actionDestinationCoord);
      break;
    case SHIFT_VICTORY :
      movedAnimal->setCoord(actionDestinationCoord);
      break;
  }
  vertex->addChild(this);
  /*cout << "       Ally team contains   : ";
  for(auto& myAnimal : myAnimals){
    cout << myAnimal.getName() << ", ";
  }
  cout << endl;
  cout << "       Ennemy team contains : ";
  for(auto& myAnimal : myAnimals){
    cout << myAnimal.getName() << ", ";
  }
  cout << endl;
  cout << "       There is now " << vertex->getChildren()->size() << " children vertex"<< endl;*/
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

Action Vertex::getAction (){
  return this->action;
}

int Vertex::getPlaying (){
  return this->playing;
}

void Vertex::setAction(ai::Action newaction){
   this->action = newaction;
}

void Vertex::setActionScore(double score){
   this->action.setScore(score);
}
