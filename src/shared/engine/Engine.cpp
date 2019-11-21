#include "Engine.h"
#include "Order.h"
#include "Move.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;


Engine::Engine(): currentState(){
  this->switchTurn = 0;
}

Engine::~Engine(){

}

state::State& Engine::getState(){
  	state::State& refEtat=currentState;
  	return refEtat;
}

void Engine::playerRequest(RenderEvent& event){

}

void Engine::addOrder (int priorite, std::unique_ptr<Order> ptr_cmd){
	currentOrder[priorite]=move(ptr_cmd);
}

std::vector<std::pair<state::Coord,engine::ActionID>> Engine::authorisedActions(State& state, Coord& current_square){
  std::vector<pair<state::Coord,engine::ActionID>> listAction;
  Coord right_square = {current_square.getX()+1,current_square.getY()};
  Coord left_square = {current_square.getX()-1,current_square.getY()};
  Coord front_square = {current_square.getX(),current_square.getY()-1};
  Coord behind_square = {current_square.getX(),current_square.getY()+1};
  listAction.push_back(make_pair(right_square,SHIFT));
  listAction.push_back(make_pair(left_square,NONE));
  listAction.push_back(make_pair(front_square,NONE));
  listAction.push_back(make_pair(behind_square,NONE));
  return listAction;
}
