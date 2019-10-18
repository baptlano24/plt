#include "Square.h"
#include "SquareID.h"
using namespace state;
using namespace std;

Square::Square(): id(EARTH) {}

Square::Square(SquareID id): id(id) {}

SquareID Square:: getID()
{
    return this->id;
};

void Square:: setID(SquareID newID)
{
  this->id = newID;
}
