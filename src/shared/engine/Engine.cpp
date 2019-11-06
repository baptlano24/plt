#include "Engine.h"
#include "Order.h"
#include "Move.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;


Engine::Engine(): currentState(){
  this->switchTurn = 0;
  this->activePlayer = 0;
}

int Engine::getactivePlayer(){
  return this->activePlayer;
}

state::State Engine::getState(){
  return this->currentState;
}

void Engine::addOrder (int priorite, std::unique_ptr<Order> ptr_cmd){
	currentOrder[priorite]=move(ptr_cmd);

}
