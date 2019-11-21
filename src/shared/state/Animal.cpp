#include "Animal.h"
#include "AnimalStatus.h"
#include <iostream>
using namespace std;
using namespace state;

Animal :: Animal(Coord coord, AnimalStatus status, AnimalID id): coord(coord), status(status), id(id){}

Animal :: Animal(){
    new (this) Animal({0,0}, NORMAL, RAT);
}

AnimalStatus Animal::getStatus() const
{
    return this->status;
}

Coord& Animal::getCoord()
{
    Coord& refCoord = this->coord;
    return refCoord;
}

void Animal::setStatus(AnimalStatus status)
{
    this->status = status;
}

void Animal::setCoord(Coord coord)
{
    this->coord = coord;
}

void Animal::setID(AnimalID newID)
{
  this->id = newID;
}

AnimalID Animal::getID()
{
  return this->id;
}
