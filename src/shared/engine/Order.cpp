
#include "Order.h"
#include "Engine.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;

OrderID Order::getOrderID() const {
  return this->ID;
};
