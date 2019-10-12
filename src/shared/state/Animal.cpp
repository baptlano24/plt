#ifndef STATE__SQUARE__H
#define STATE__SQUARE__H
#include <iostream>
#include "AnimalStatus.h"
#include "Animal.h"
using namespace std;

namespace state {  /// class Animal -
class Animal{
  private:
    int x;
    int y;
    AnimalStatus status;
    // Operations
  public:
    Animal(int x, int y): x(x),y(y),status(1) {cout << "Animal is created" << endl;};
    AnimalStatus getStatus (){return status};
    void setStatus (AnimalStatus status){ this->status=status;};
    // Setters and Getters


  };
};


#endif
