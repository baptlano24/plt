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
  this->stateHistoric.push_back(this->currentState);
}

state::State& Engine::getState(){
  	state::State& refEtat=currentState;
  	return refEtat;
}

void Engine::setState (state::State& state){
  this->currentState = state;
}

void Engine::playerRequest(RenderEvent& event){

}

void Engine::undo (){
  if((int)this->stateHistoric.size()>1){
  setState(this->stateHistoric[int(this->stateHistoric.size()-1)]);

  this->stateHistoric.pop_back();
}
  State& state = getState();
  StateEvent animalChangedEvent(ANIMALS_CHANGED);
  StateEvent& refAnimalChangedEvent = animalChangedEvent;
  StateEvent infosChangedEvent(INFOS_CHANGED);
  StateEvent& refInfosChangedEvent = infosChangedEvent;
  state.notifyObservers(refAnimalChangedEvent, state);
  state.notifyObservers(refInfosChangedEvent, state);

}


void Engine::addState (state::State newState){
  this->stateHistoric.push_back(newState);
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


    if(state.getSelection(current_square).first->getStatus() == NORMAL){
      //cout << "NORMAL!" << endl;

      for (int i = 0; i<=3 ;i++) {
        if(state.getSquare(listAction[i].first)){
          if(state.getSquare(listAction[i].first)->getID() != WATER){
            //cout << "NOWATER!" << endl;
            if(state.getSelection(listAction[i].first).first && state.getSelection(listAction[i].first).first->getStatus() != DEAD ){
              //cout << "SOMEONE!" << endl;
              if(state.getSelection(listAction[i].first).second == state.getSelection(current_square).second){
                //cout << "COPAIN!" << endl;
                listAction[i].second = NONE;
              }
              else{
                if((state.getSelection(current_square).first->getID()>=state.getSelection(listAction[i].first).first->getID())||((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(listAction[i].first).second == 1 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(listAction[i].first).second == 0))){
                    //cout << "A L'ATTAQUE!" << endl;
                    listAction[i].second = ATTACK;
                  }
                  else{
                    //cout <<"TROP FORT"<< endl;
                    listAction[i].second = NONE;
                  }
              }
            } else {
              if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 0 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 1)){
                //cout <<"TRAP ALLIE" << endl;
                listAction[i].second = SHIFT;
              }
              else if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 0)){
                //cout <<"TRAPPED" << endl;
                listAction[i].second = SHIFT_TRAPPED;
              }
              else if((state.getSquare(listAction[i].first)->getID() == THRONEJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == THRONEJ2 && state.getSelection(current_square).second == 0)){
              //cout <<  "VICTORY SOON" << endl;
                listAction[i].second = SHIFT_VICTORY;
              }
              else if((state.getSquare(listAction[i].first)->getID() == THRONEJ1 && state.getSelection(current_square).second == 0 )||(state.getSquare(listAction[i].first)->getID() == THRONEJ2 && state.getSelection(current_square).second == 1)){
              //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                listAction[i].second = NONE;
              }
              else {
              //cout <<  "MOVE" << endl;
                listAction[i].second = SHIFT;
              }

            }
          }
          else if (state.getSquare(listAction[i].first)->getID() == WATER) {
            //cout <<"WATER"<< endl;
            listAction[i].second = NONE;
          }
        }
      } // end for
    }

  } else if (state.getSelection(current_square).first->getID() == RAT) {

    if(state.getSelection(current_square).first->getStatus() == NORMAL){
        for (int i = 0; i<=3 ;i++) {
          if(state.getSquare(listAction[i].first)){

            if(state.getSelection(listAction[i].first).first){
                //cout << "SOMEONE!" << endl;
              if(state.getSelection(listAction[i].first).second == state.getSelection(current_square).second){
                //cout << "COPAIN!" << endl;
                listAction[i].second = NONE;
              } else if(state.getSquare(current_square)->getID() != WATER){
                  if(state.getSelection(listAction[i].first).first->getID() == ELEPHANT || state.getSelection(listAction[i].first).first->getID() == RAT){
                    //cout << "A L'ATTAQUE!" << endl;
                    listAction[i].second = ATTACK;
                  }
                  else if((state.getSelection(listAction[i].first).second != state.getSelection(current_square).second)
                       && ((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 0) || (state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 1)) ){
                    //cout << " PIEGE ET A L'ATTAQUE!" << endl;
                    listAction[i].second = ATTACK;
                    }
                   else{
                     //cout << "MOVE TRAP ALLIE OCCUPE" << endl;
                     listAction[i].second = NONE;
                   }
              } else {
                if (state.getSquare(listAction[i].first)->getID() == WATER) {
                  //cout << "ATTACK" << endl;
                  listAction[i].second = ATTACK;
                } else {
                  //cout <<"Can't MOVE from WATER" << endl;
                  listAction[i].second = NONE;
                }
              }
            } else {
              if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 0)){
                //cout <<"TRAPPED" << endl;
                listAction[i].second = SHIFT_TRAPPED;
              }
              else if((state.getSquare(listAction[i].first)->getID() == THRONEJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == THRONEJ2 && state.getSelection(current_square).second == 0)){
                //cout <<  "VICTORY SOON" << endl;
                listAction[i].second = SHIFT_VICTORY;
              }
              else if((state.getSquare(listAction[i].first)->getID() == THRONEJ1 && state.getSelection(current_square).second == 0 )||(state.getSquare(listAction[i].first)->getID() == THRONEJ2 && state.getSelection(current_square).second == 1)){
                //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                listAction[i].second = NONE;
              }
              else{
                //cout <<  "MOVE" << endl;
                listAction[i].second = SHIFT;
              }
            }
          }
        } //end for
      }
  } else if(state.getSelection(current_square).first->getID() == TIGER || state.getSelection(current_square).first->getID() == LEOPARD || state.getSelection(current_square).first->getID() == LION) {

    if(state.getSelection(current_square).first->getStatus() == NORMAL){
      for (int i = 0; i<=3 ;i++) {
        if(state.getSquare(listAction[i].first)){
            if(state.getSquare(listAction[i].first)->getID() != WATER){
              //cout << "NOWATER!" << endl;
              if(state.getSelection(listAction[i].first).first){
                //cout << "SOMEONE!" << endl;
                if(state.getSelection(listAction[i].first).second == state.getSelection(current_square).second){
                  //cout << "COPAIN!" << endl;
                  listAction[i].second = NONE;
                }
                else{
                  if((state.getSelection(current_square).first->getID()>=state.getSelection(listAction[i].first).first->getID())||((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(listAction[i].first).second == 1 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(listAction[i].first).second == 0))){
                      //cout << "A L'ATTAQUE!" << endl;
                      listAction[i].second = ATTACK;
                    }
                    else{
                      //cout <<"TROP FORT"<< endl;
                      listAction[i].second = NONE;
                    }
                }

              }else{
                if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 0 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 1)){
                  //cout <<"TRAP ALLIE" << endl;
                  listAction[i].second = SHIFT;
                }
                else if((state.getSquare(listAction[i].first)->getID() == TRAPJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == TRAPJ2 && state.getSelection(current_square).second == 0)){
                  //cout <<"TRAPPED" << endl;
                  listAction[i].second = SHIFT_TRAPPED;
                }
                else if((state.getSquare(listAction[i].first)->getID() == THRONEJ1 && state.getSelection(current_square).second == 1 )||(state.getSquare(listAction[i].first)->getID() == THRONEJ2 && state.getSelection(current_square).second == 0)){
                //cout <<  "VICTORY SOON" << endl;
                  listAction[i].second = SHIFT_VICTORY;
                }
                else if((state.getSquare(listAction[i].first)->getID() == THRONEJ1 && state.getSelection(current_square).second == 0 )||(state.getSquare(listAction[i].first)->getID() == THRONEJ2 && state.getSelection(current_square).second == 1)){
                //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                  listAction[i].second = NONE;
                }
                else{
                //cout <<  "MOVE" << endl;
                  listAction[i].second = SHIFT;
                }

              }
            }else{
              if(i == 0){
                int compteur = 0;
                for(int n = 0; n<=3; n++){
                  if(state.getSelection(Coord(listAction[i].first.getX()+n, listAction[i].first.getY())).first==NULL){
                    compteur += 1;
                  if (compteur == 4){
                    //cout <<"CAN JUMP" << endl;
                    listAction[i].first = Coord(listAction[i].first.getX()+3, listAction[i].first.getY());
                    listAction[i].second = JUMP;
                  }
                  else{
                    listAction[i].second = NONE;
                  }
                }
              }

              //Jump
            } else if(i==1){
              int compteur = 0;
              for(int n = 0; n<=3; n++){
                if(state.getSelection(Coord(listAction[i].first.getX()-n, listAction[i].first.getY())).first==NULL){
                  compteur += 1;
                if (compteur == 4){
                  //cout <<"CAN JUMP" << endl;
                  listAction[i].first = Coord(listAction[i].first.getX()-3, listAction[i].first.getY());
                  listAction[i].second = JUMP;
                }
                else{
                  listAction[i].second = NONE;
                }
              }
            }
          }  else if(i==2){
            int compteur = 0;
            for(int n = 0; n<=3; n++){
              if(state.getSelection(Coord(listAction[i].first.getX(), listAction[i].first.getY()-n)).first==NULL){
                compteur += 1;
              if (compteur == 4){
                //cout <<"CAN JUMP" << endl;
                listAction[i].first = Coord(listAction[i].first.getX(), listAction[i].first.getY()-3);
                listAction[i].second = JUMP;
                compteur = 0;
              }
              else{
                listAction[i].second = NONE;
              }
            }
          }
        } else{
          int compteur = 0;
          for(int n = 0; n<=3; n++){
            if(state.getSelection(Coord(listAction[i].first.getX(), listAction[i].first.getY()+n)).first==NULL){
              compteur += 1;
            if (compteur == 4){
              //cout <<"CAN JUMP" << endl;
              listAction[i].first = Coord(listAction[i].first.getX(), listAction[i].first.getY()+3);
              listAction[i].second = JUMP;

            }
            else{
              listAction[i].second = NONE;

          }
        }
      }


       }
      }
     }
    }// end for
   }
  }
return listAction;
}
