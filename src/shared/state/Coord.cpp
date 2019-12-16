#include "Coord.h"
#include <iostream>
using namespace std;
using namespace state;

Coord::Coord(int x, int y): x(x),y(y){}

Coord::Coord(){
    new (this) Coord(0,0);
}

int Coord::getX()
{
    return this->x;
}

int Coord::getY()
{
    return this->y;
}

void Coord::setY(int y)
{
    this->y = y;
}

void Coord::setX(int x)
{
    this->x = x;
}

bool Coord::operator==(const Coord &otherCoord) {
    return ( this->x == otherCoord.x && this->y == otherCoord.y );
}
bool Coord::operator!=(const Coord &otherCoord) {
    return ( this->x != otherCoord.x || this->y != otherCoord.y );
}
