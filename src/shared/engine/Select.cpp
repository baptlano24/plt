#include "../state/State.h"
#include "Engine.h"
#include "Order.h"
#include "Select.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;


Select::Select(Animal* targetAnimal, Coord& targetCoord):targetAnimal(targetAnimal), targetCoord(targetCoord){
    this->ID = SELECT;
    this->player = 0;
}

void Select::execute(Engine* engine)
{
  cout<<"Début du tour numéro : " << engine->getState().getTurn() << endl;
  cout<<"Case SELECT : (" << this->targetCoord.getX()<< "," << this->targetCoord.getX() << ")"<< endl;
}
