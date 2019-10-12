#ifndef STATE__SQUARE__H
#define STATE__SQUARE__H
#include <iostream>
#include "SquareID.h"
#include "Square.h"
using namespace std;

namespace state {
  class Square{
  private:
    bool empty;
    SquareID id;
  public:
    Square (bool empty, SquareID id): empty(empty),id(id){ cout << "Square is created" << endl;};
    bool isEmpty (){ return empty;};
    SquareID getID (){return id ;};
  };
};

#endif
