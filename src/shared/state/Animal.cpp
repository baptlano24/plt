#include "Animal.h"
#include "AnimalStatus.h"
#include <iostream>
using namespace std;
using namespace state;

Animal :: Animal(Coord coord, AnimalStatus status, AnimalID id): coord(coord), status(status), id(id){
  switch(id)
  {
    case RAT :
      this->name = "RAT";
      break;
    case CAT :
      this->name = "CAT";
      break;
    case DOG :
      this->name = "DOG";
      break;
    case WOLF :
      this->name = "WOLF";
      break;
    case LEOPARD :
      this->name = "LEOPARD";
      break;
    case TIGER :
      this->name = "TIGER";
      break;
    case LION :
      this->name = "LION";
      break;
    case ELEPHANT :
      this->name = "ELEPHANT";
      break;
  }
}

Animal :: Animal(){
    new (this) Animal({0,0}, NORMAL, WOLF);
}

AnimalStatus Animal::getStatus() const
{
    return this->status;
}

std::string Animal::getName()
{
    return this->name;
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
