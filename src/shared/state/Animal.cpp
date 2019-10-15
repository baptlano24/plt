#include "Animal.h"
#include "AnimalStatus.h"
#include <iostream>
using namespace std;
using namespace state;

Animal::Animal(int x, int y, AnimalStatus status): x(x), y(y), status(status){}

AnimalStatus Animal::getStatus()
{
    return this->status;
}

int Animal::getX()
{
    return this->x;
}

int Animal::getY()
{
    return this->y;
}

void Animal::setStatus(AnimalStatus status)
{
    this->status = status;
}

void Animal::setX(int x)
{
    this->x = x;
}

void Animal::setY(int y)
{
    this->y = y;
}
