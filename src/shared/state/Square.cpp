#include "Square.h"
#include "SquareID.h"
using namespace state;
using namespace std;

Square::Square(): id(EARTH), highlight(0) {}

Square::Square(SquareID id): id(id), highlight(0) {}

SquareID Square:: getID()
{
    return this->id;
};

void Square:: setID(SquareID newID)
{
  this->id = newID;
}
