#include "Engine.h"
#include "Order.h"
#include "Move.h"
#include <iostream>
#include <utility>
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
  std::vector<pair<state::Coord, engine::ActionID>> listAction;
  Coord right_square(current_square.getX()+1,current_square.getY());
  Coord left_square(current_square.getX()-1,current_square.getY());
  Coord front_square(current_square.getX(),current_square.getY()-1);
  Coord behind_square(current_square.getX(),current_square.getY()+1);
  listAction.push_back(make_pair(right_square,NONE));
  listAction.push_back(make_pair(left_square,NONE));
  listAction.push_back(make_pair(front_square,NONE));
  listAction.push_back(make_pair(behind_square,NONE));

  if (state.getSelection(current_square).first->getID() == ELEPHANT || state.getSelection(current_square).first->getID() ==  CAT || state.getSelection(current_square).first->getID() == DOG || state.getSelection(current_square).first->getID() == WOLF){
    cout << "ELEPHANT or CAT or DOG or WOLF!" << endl;
    if(state.getSelection(current_square).first->getStatus() == NORMAL){
      //cout << "NORMAL!" << endl;

      for (int i = 0; i<=3 ;i++) {
        if(state.getSquare(listAction[i].first)->getID() != WATER){
          //cout << "NOWATER!" << endl;
          if(state.getSelection(listAction[i].first).first && state.getSelection(listAction[i].first).first->getStatus() != DEAD ){
            cout << "SOMEONE!" << endl;
            cout << state.getSelection(current_square).second << endl;
            cout << state.getSelection(listAction[i].first).second << endl;
            if(state.getSelection(listAction[i].first).second == state.getSelection(current_square).second){
              cout << "COPAIN!" << endl;
              listAction[i].second = NONE;
            }
            else{
              if(state.getSelection(current_square).first->getID() >= state.getSelection(listAction[i].first).first->getID()){
                  cout << "A L'ATTAQUE!" << endl;
                  listAction[i].second = ATTACK;
                }
                else{
                  cout <<"TROP FORT"<< endl;
                  listAction[i].second = NONE;
                }
            }
          } else {
            if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 0 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 1)){
              cout <<"TRAP ALLIE" << endl;
              listAction[i].second = SHIFT;
            }
            else if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 0)){
              cout <<"TRAPPED" << endl;
              listAction[i].second = SHIFT_TRAPPED;
            }
            else if((state.getSquare(listAction[i].first)->getID() == THRONEJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == THRONEJ2 && state.getSelection(current_square).second == 0)){
            cout <<  "VICTORY SOON" << endl;
              listAction[i].second = SHIFT_VICTORY;
            } else {
            cout <<  "MOVE" << endl;
              listAction[i].second = SHIFT;
            }

          }
        }
        else if (state.getSquare(listAction[i].first)->getID() != WATER) {
          cout <<"WATER"<< endl;
          listAction[i].second = NONE;
        }
      }
    }
    return listAction;
  } else if (state.getSelection(current_square).first->getID() == RAT) {
    cout << "RAT" << endl;
    if(state.getSelection(current_square).first->getStatus() == NORMAL){
      //cout << "NORMAL!" << endl;
      for (int i = 0; i<=3 ;i++) {
      if(state.getSelection(listAction[i].first).first){
          cout << "SOMEONE!" << endl;
      if(state.getSelection(listAction[i].first).second == state.getSelection(current_square).second){
        cout << "COPAIN!" << endl;
        listAction[i].second = NONE;
      } else if(state.getSquare(listAction[i].first)->getID() != WATER){
          if(state.getSelection(listAction[i].first).first->getID() == ELEPHANT || state.getSelection(listAction[i].first).first->getID() == RAT){
            cout << "A L'ATTAQUE!" << endl;
            listAction[i].second = ATTACK;
          }
          else if(!(state.getSelection(listAction[i].first).first->getID() == ELEPHANT || state.getSelection(listAction[i].first).first->getID() == RAT) && ((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 0) || (state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 1)) ){
            cout << " PIEGE ET A L'ATTAQUE!" << endl;
            listAction[i].second = ATTACK;
            }
           else{
             cout << "MOVE TRAP ALLIE" << endl;
             listAction[i].second = SHIFT;
           }
          }
        else if((state.getSquare(listAction[i].first)->getID() == SHORE) && (state.getSelection(listAction[i].first).first)){
          cout <<"Can't MOVE from WATER" << endl;
          listAction[i].second = NONE;

        }
        else{
          cout <<"Can Move from Water" << endl;
          listAction[i].second = SHIFT;
        }}
      else {
        if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 0)){
        cout <<"TRAPPED" << endl;
        listAction[i].second = SHIFT_TRAPPED;
      }
      else if((state.getSquare(listAction[i].first)->getID() == THRONEJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == THRONEJ2 && state.getSelection(current_square).second == 0)){
      cout <<  "VICTORY SOON" << endl;
        listAction[i].second = SHIFT_VICTORY;
      }
      else{
      //cout <<  "MOVE" << endl;
        listAction[i].second = SHIFT;
      }
        return listAction;
        }
      }
      return listAction;//next RAT*/
    }
    return listAction;
  } else if(state.getSelection(current_square).first->getID() == TIGER || state.getSelection(current_square).first->getID() == LEOPARD || state.getSelection(current_square).first->getID() == LION){
    cout<<"LION or TIGER or LEOPARD" << endl;
    if(state.getSelection(current_square).first->getStatus() == NORMAL){
      //cout << "NORMAL!" << endl;
      for (int i = 0; i<=3 ;i++) {
        if(state.getSquare(listAction[i].first)->getID() != WATER){
          //cout << "NOWATER!" << endl;
          if(state.getSelection(listAction[i].first).first){
            cout << "SOMEONE!" << endl;
            if(state.getSelection(listAction[i].first).second == state.getSelection(current_square).second){
              cout << "COPAIN!" << endl;
              listAction[i].second = NONE;
            }
            else{
              if(state.getSelection(current_square).first->getID()>state.getSelection(listAction[i].first).first->getID()){
                  cout << "A L'ATTAQUE!" << endl;
                  listAction[i].second = ATTACK;
                }
                else{
                  cout <<"TROP FORT"<< endl;
                  listAction[i].second = NONE;
                }
            }

          }else{
            if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 0 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 1)){
              cout <<"TRAP ALLIE" << endl;
              listAction[i].second = SHIFT;
            }
            else if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 0)){
              cout <<"TRAPPED" << endl;
              listAction[i].second = SHIFT_TRAPPED;
            }
            else if((state.getSquare(listAction[i].first)->getID() == THRONEJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == THRONEJ2 && state.getSelection(current_square).second == 0)){
            cout <<  "VICTORY SOON" << endl;
              listAction[i].second = SHIFT_VICTORY;
            }
            else{
            //cout <<  "MOVE" << endl;
              listAction[i].second = SHIFT;
            }

          }
        }else{
          //Jump
        }
      }
      return listAction;
    }else{
      return listAction;
    }

  } else{
    return listAction;
  }
  return listAction;
}
