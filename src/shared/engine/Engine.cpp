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

bool Engine::getactivePlayer(){
  return this->activePlayer;
}

state::State& Engine::getState(){
  	state::State& refEtat=currentState;
  	return refEtat;
}


Engine::~Engine(){

}

void Engine::addOrder (int priorite, std::unique_ptr<Order> ptr_cmd){
	currentOrder[priorite]=move(ptr_cmd);
}

std::unordered_map<engine::ActionID,state::Coord>& authorisedActions (state::State& state, state::AnimalID AnimalID){
  if (AnimalID == ELEPHANT or CAT or DOG or WOLF){
    if(state.getPlayer1().getAnimals().at(AnimalID).getStatus() == NORMAL){
        Coord Case_actuel = state.getPlayer1().getAnimals().at(AnimalID).getCoord();
        Coord Case_droite = {Case_actuel.getX()+1,Case_actuel.getY()};
        Coord Case_gauche = {Case_actuel.getX()-1,Case_actuel.getY()};
        Coord Case_devant = {Case_actuel.getX(),Case_actuel.getY()-1};
        Coord Case_derriere = {Case_actuel.getX(),Case_actuel.getY()+1};
        if(state.getSquare(Case_droite).getID()!=WATER || NOMAP){


        }
      }

    }

  }
