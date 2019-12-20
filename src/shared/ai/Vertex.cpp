#include "ai.h"
#include "../state/State.h"
#include "Vertex.h"
#include "engine.h"
#include <unistd.h>
#include <iostream>
#include "Action.h"
#include <algorithm>
#include <random>

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
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(this->myAnimals), std::end(this->myAnimals), rng);
  std::shuffle(std::begin(this->hisAnimals), std::end(this->hisAnimals), rng);
  /*cout << "  Ally team contains   : ";
  for(auto& myAnimal : this->myAnimals){
    cout << myAnimal.getName() << ", ";
  }
  cout << endl;
  cout << "  Ennemy team contains : ";
  for(auto& hisAnimal : this->hisAnimals){
    cout << hisAnimal.getName() << ", ";
  }
  cout << endl;*/
}

Vertex::Vertex(Vertex* vertex, Action& action):action(action){
  this->parent = vertex;
  this->playing = 1 - vertex->getPlaying();
  this->hisAnimals = *vertex->getMyAnimals();
  Coord actionDestinationCoord = this->action.getCoord();
  Coord actionAnimalCoord = this->action.getAnimal().getCoord();
  Animal* movedAnimal;

  for(auto& hisAnimal : hisAnimals){
    if(hisAnimal.getCoord() == actionAnimalCoord){
      movedAnimal = &hisAnimal;
    }
  }
  switch(this->action.getId())
  {
    case NONE : //It's never the case here
      break;
    case SHIFT :
      movedAnimal->setCoord(actionDestinationCoord);
      this->myAnimals = *vertex->getHisAnimals();
      break;
    case ATTACK :
      for(auto& hisAnimal : *vertex->getHisAnimals()){
        if(hisAnimal.getCoord() != actionDestinationCoord){
          this->myAnimals.push_back(hisAnimal);
        }
      }
      movedAnimal->setCoord(actionDestinationCoord);
      break;
    case JUMP :
      this->myAnimals = *vertex->getHisAnimals();
      movedAnimal->setCoord(actionDestinationCoord);
      break;
    case SHIFT_TRAPPED :
      this->myAnimals = *vertex->getHisAnimals();
      movedAnimal->setCoord(actionDestinationCoord);
      break;
    case SHIFT_VICTORY :
      this->myAnimals = *vertex->getHisAnimals();
      movedAnimal->setCoord(actionDestinationCoord);
      break;
  }
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(this->myAnimals), std::end(this->myAnimals), rng);
  std::shuffle(std::begin(this->hisAnimals), std::end(this->hisAnimals), rng);
  vertex->addChild(this);

  /*cout << "  Ally team contains   : ";
  for(auto& myAnimal : this->myAnimals){
    cout << myAnimal.getName() << ", ";
  }
  cout << endl;
  cout << "  Ennemy team contains : ";
  for(auto& hisAnimal : this->hisAnimals){
    cout << hisAnimal.getName() << ", ";
  }
  cout << endl;*/
  //cout << "\033[1;34m     -new vertex team "<< this->playing <<" from " << this->action.getAnimal().getName() << " (" << this->action.getAnimal().getCoord().getX() << "," << this->action.getAnimal().getCoord().getY() << ") go in (" << this->action.getCoord().getX() << "," << this->action.getCoord().getY() << ") to ID "<< this->action.getId() <<" with score "<< this->action.getScore() << "\033[0m" << endl;

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
