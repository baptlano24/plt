#include "Animal.h"
#include "AnimalStatus.h"
#include <iostream>
using namespace std;
using namespace state;

Animal::Animal(Coord coord, AnimalStatus status): coord(coord), status(status){}

AnimalStatus Animal::getStatus()
{
    return this->status;
}

Coord Animal::getCoord()
{
    return this->coord;
}

void Animal::setStatus(AnimalStatus status)
{
    this->status = status;
}

void Animal::setCoord(Coord coord)
{
    this->coord = coord;
}
