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

std::vector<pair<state::Coord, engine::ActionID>> authorisedActions (state::State& state, state::AnimalID animalID){
  std::vector<pair<state::Coord,engine::ActionID>> listAction;
  Coord Case_actuel = state.getPlayer1().getAnimals().at(animalID).getCoord();
  Coord Case_droite = {Case_actuel.getX()+1,Case_actuel.getY()};
  Coord Case_gauche = {Case_actuel.getX()-1,Case_actuel.getY()};
  Coord Case_devant = {Case_actuel.getX(),Case_actuel.getY()-1};
  Coord Case_derriere = {Case_actuel.getX(),Case_actuel.getY()+1};
  listAction.push_back(make_pair(Case_droite,NONE));
  listAction.push_back(make_pair(Case_gauche,NONE));
  listAction.push_back(make_pair(Case_devant,NONE));
  listAction.push_back(make_pair(Case_derriere,NONE));
  if (animalID == ELEPHANT || animalID ==  CAT || animalID == DOG || animalID == WOLF){
    if(state.getPlayer1().getAnimals().at(animalID).getStatus() == NORMAL){
      for (int i ; i<=4 ;i++) {
        if(state.getSquare(listAction[i].first).getID()!=WATER){
          if(state.getSelection(listAction[i].first).second){
              
            //if(animalID>state.getSelection(listAction[i].first).first.getID()){
              //listAction[i].second = ATTACK;
            }
            //else{
              //listAction[i].second = NONE;
            //}


          }
        }
      }
    }



  }
