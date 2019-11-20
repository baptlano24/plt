#include "../state/State.h"
#include "Engine.h"
#include "Order.h"
#include "Move.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;


Move::Move(Animal* targetAnimal, Coord& targetCoord):targetAnimal(targetAnimal),targetCoord(targetCoord){
    this->ID = MOVE;
    this->player = 0;
}

void Move::execute(State& state)
{
  cout<<"Début du tour numéro : " << state.getTurn() << endl;
  cout<<"Anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
  cout<<"Nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;

  this->targetAnimal->setCoord(this->targetCoord);
  cout<<"Nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;

  state.setTurn(state.getTurn()+1);
  cout<<"Passage au tour numéro : " << state.getTurn() << endl;
}
