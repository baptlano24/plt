#include "Action.h"
#include <unistd.h>
#include <iostream>
#include "../state/State.h"
#include "engine.h"

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;



Action::Action(double score, state::Animal* animal, state::Coord* coord, engine::ActionID Id):
score(score),animal(animal), coord(coord), actionID(Id){}

Action::Action(){
  new (this) Action(0,NULL,NULL,NONE);
}
double Action::getScore(){
  return this->score;
}

state::Animal* Action::getAnimal(){
  return this->animal;
}

state::Coord* Action::getCoord(){
  return this->coord;
}

engine::ActionID Action::getId(){
  return this->actionID;
}

void Action::setScore(double score){
  this->score = score;
}
