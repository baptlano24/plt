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

Engine::~Engine(){

}

bool Engine::getactivePlayer(){
  return this->activePlayer;
}

state::State& Engine::getState(){
  	state::State& refEtat=currentState;
  	return refEtat;
}

void Engine::playerRequest(RenderEventID event){}


void Engine::addOrder (int priorite, std::unique_ptr<Order> ptr_cmd){
	currentOrder[priorite]=move(ptr_cmd);
}

std::vector<pair<state::Coord, engine::ActionID>> authorisedActions (state::State& state, state::Coord current_square){
  std::vector<pair<state::Coord,engine::ActionID>> listAction;
  Coord right_square = {current_square.getX()+1,current_square.getY()};
  Coord left_square = {current_square.getX()-1,current_square.getY()};
  Coord front_square = {current_square.getX(),current_square.getY()-1};
  Coord behind_square = {current_square.getX(),current_square.getY()+1};
  listAction.push_back(make_pair(right_square,NONE));
  listAction.push_back(make_pair(left_square,NONE));
  listAction.push_back(make_pair(front_square,NONE));
  listAction.push_back(make_pair(behind_square,NONE));
  if ( state.getSelection(current_square).first->getID() == ELEPHANT || state.getSelection(current_square).first->getID() ==  CAT || state.getSelection(current_square).first->getID() == DOG || state.getSelection(current_square).first->getID() == WOLF){
    if(state.getSelection(current_square).first->getStatus() == NORMAL){
      for (int i ; i<=4 ;i++) {
        if(state.getSquare(listAction[i].first).getID()!=WATER){
          if(state.getSelection(listAction[i].first).first){
            if(state.getSelection(listAction[i].first).second == state.getSelection(current_square).second){
              listAction[i].second = NONE;
            }
            else{
              if(state.getSelection(current_square).first->getID()>state.getSelection(listAction[i].first).first->getID()){
                  listAction[i].second = ATTACK;
                }
                else{
                  listAction[i].second = NONE;
                }
            }

          }else{
            if((state.getSquare(listAction[i].first).getID() == TRAPJ1 && state.getSelection(current_square).second == 0 )||(state.getSquare(listAction[i].first).getID() == TRAPJ2 && state.getSelection(current_square).second == 1)){
              listAction[i].second = SHIFT;
            }
            else if((state.getSquare(listAction[i].first).getID() == TRAPJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first).getID() == TRAPJ2 && state.getSelection(current_square).second == 0)){
              listAction[i].second = SHIFT_TRAPPED;
            }
            else if((state.getSquare(listAction[i].first).getID() == THRONEJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first).getID() == THRONEJ2 && state.getSelection(current_square).second == 0)){
              listAction[i].second = SHIFT_VICTORY;
            }

          }
        }
      }
    }



  }
}
