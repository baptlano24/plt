#include "../state/State.h"
#include "DeepAI.h"
#include "Vertex.h"
#include "state.h"
#include "engine.h"
#include <unistd.h>
#include <iostream>
#include <math.h>

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;



DeepAI::DeepAI(int color, engine::Engine* engine){
  this->color = color;
  this->map = &engine->getState().getGrid();
}


 std::array<std::array<state::Square,13>,12>* DeepAI::getMap(){
   return this->map;

}

void DeepAI::createChildren (Vertex* vertex, int depth){
  //std::vector<state::Animal>* listAnimals = vertex->getMyAnimals();
  std::vector<Vertex*> listChildren = vertex->getChildren();
  std::vector<Action> listActions = this->enumerateActions(vertex);
  if(depth>=2){
    for(int i = 0; i<=(int)listActions.size(); i++){
      Vertex Child = Vertex(vertex, listActions[i]);
      createChildren(&Child,depth-1);
    }
  } else if (depth == 1){
    for(int i = 0; i<=(int)listActions.size(); i++){
      Vertex Child = Vertex(vertex, listActions[i]);
      Child.getAction()->setScore(1000);//a calculer
    }
  }
}


void DeepAI::play(engine::Engine* engine) {

}

std::vector<Action> DeepAI:: enumerateActions (Vertex* vertex){
  std::vector<Action> listAction;
  std::array<std::array<state::Square,13>,12>* map = getMap();
  std::array<std::array<state::Square,13>,12> map1 = *map;
  for(int i = 0; i<= (int)vertex->getMyAnimals()->size(); i++)
    {
      std::vector<state::Coord> listCoord;
      Coord current_square = vertex->getMyAnimals()->at(i).getCoord();
      Coord right_square(current_square.getX()+1,current_square.getY());
      Coord left_square(current_square.getX()-1,current_square.getY());
      Coord front_square(current_square.getX(),current_square.getY()-1);
      Coord behind_square(current_square.getX(),current_square.getY()+1);

      listCoord.push_back(right_square);
      listCoord.push_back(left_square);
      listCoord.push_back(behind_square);
      listCoord.push_back(front_square);
      std::pair<Animal*,int> selection = vertex->getSelection(vertex,current_square);
      std::pair<Animal*,int> selectionList;
      SquareID squareId_list;
      Animal* animal = &vertex->getMyAnimals()->at(+i);

      if (selection.first->getID() == ELEPHANT || selection.first->getID() ==  CAT || selection.first->getID() == DOG || selection.first->getID() == WOLF){
          //cout << "NORMAL!" << endl;
          for (int j = 0; j<=(int)listCoord.size() ;j++) {
            if (listCoord[j].getX()<=11 && listCoord[j].getX()>=0 && listCoord[j].getY()<= 12 && listCoord[j].getY()>=0){
              selectionList = vertex->getSelection(vertex,listCoord[j]);
              squareId_list = map1[listCoord[j].getX()][listCoord[j].getY()].getID();
              if(squareId_list!= WATER){
                //cout << "NOWATER!" << endl;
                if(selectionList.first && selectionList.first->getStatus() != DEAD ){
                  //cout << "SOMEONE!" << endl;
                  if(selectionList.second == selection.second){
                    //cout << "COPAIN!" << endl;
                    //do nothing
                  }
                  else{
                    if((selection.first->getID()>=selectionList.first->getID())||((squareId_list== TRAPJ1 && selectionList.second == 1 )||(squareId_list== TRAPJ2 && selectionList.second == 0))){
                        //cout << "A L'ATTAQUE!" << endl;
                        listAction.push_back(Action(0,animal,&listCoord[j],ATTACK));
                      }
                      else{
                        //cout <<"TROP FORT"<< endl;
                        //do nothing
                      }
                  }
                } else {
                  if((squareId_list== TRAPJ1 && selection.second== 0 )||(squareId_list== TRAPJ2 && selection.second== 1)){
                    //cout <<"TRAP ALLIE" << endl;
                    listAction.push_back(Action(0,animal,&listCoord[j],SHIFT));
                  }
                  else if((squareId_list== TRAPJ1 && selection.second== 1 )||(squareId_list== TRAPJ2 && selection.second== 0)){
                    //cout <<"TRAPPED" << endl;
                    listAction.push_back(Action(0,animal,&listCoord[j],SHIFT_TRAPPED));
                  }
                  else if((squareId_list== THRONEJ1 && selection.second== 1 )||(squareId_list== THRONEJ2 && selection.second== 0)){
                  //cout <<  "VICTORY SOON" << endl;
                    listAction.push_back(Action(0,animal,&listCoord[j],SHIFT_VICTORY));
                  }
                  else if((squareId_list== THRONEJ1 && selection.second== 0 )||(squareId_list== THRONEJ2 && selection.second== 1)){
                  //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                    //do nothing
                  }
                  else {
                  //cout <<  "MOVE" << endl;
                    listAction.push_back(Action(0,animal,&listCoord[j],SHIFT));
                  }

                }
              }
              else if (squareId_list== WATER) {
                //cout <<"WATER"<< endl;
                //do nothing
              }
            }
          } // end for

      } else if (selection.first->getID() == RAT) {

            for (int j = 0; j<=(int)listCoord.size() ;j++) {
              if (listCoord[j].getX()<=11 && listCoord[j].getX()>=0 && listCoord[j].getY()<= 12 && listCoord[j].getY()>=0){
              selectionList = vertex->getSelection(vertex,listCoord[j]);
              squareId_list = map1[listCoord[j].getX()][listCoord[j].getY()].getID();
                if(selectionList.first){
                    //cout << "SOMEONE!" << endl;
                  if(selectionList.second == selection.second){
                    //cout << "COPAIN!" << endl;
                    //do nothing
                  } else if(squareId_list!= WATER){
                      if(selectionList.first->getID() == ELEPHANT || selectionList.first->getID() == RAT){
                        //cout << "A L'ATTAQUE!" << endl;
                        listAction.push_back(Action(0,animal,&listCoord[j],ATTACK));
                      }
                      else if((selectionList.second != selection.second)
                           && ((squareId_list== TRAPJ1 && selection.second== 0) || (squareId_list== TRAPJ2 && selection.second== 1)) ){
                        //cout << " PIEGE ET A L'ATTAQUE!" << endl;
                        listAction.push_back(Action(0,animal,&listCoord[j],ATTACK));
                        }
                       else{
                         //cout << "MOVE TRAP ALLIE OCCUPE" << endl;
                         //do nothing
                       }
                  } else {
                    if (squareId_list== WATER) {
                      //cout << "ATTACK" << endl;
                      listAction.push_back(Action(0,animal,&listCoord[j],ATTACK));
                    } else {
                      //cout <<"Can't MOVE from WATER" << endl;
                      //do nothing
                    }
                  }
                } else {
                  if((squareId_list== TRAPJ1 && selection.second== 1 )||(squareId_list== TRAPJ2 && selection.second== 0)){
                    //cout <<"TRAPPED" << endl;
                    listAction.push_back(Action(0,animal,&listCoord[j],SHIFT_TRAPPED));
                  }
                  else if((squareId_list== THRONEJ1 && selection.second== 1 )||(squareId_list== THRONEJ2 && selection.second== 0)){
                    //cout <<  "VICTORY SOON" << endl;
                    listAction.push_back(Action(0,animal,&listCoord[j],SHIFT_VICTORY));
                  }
                  else if((squareId_list== THRONEJ1 && selection.second== 0 )||(squareId_list== THRONEJ2 && selection.second== 1)){
                    //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                    //do nothing
                  }
                  else{
                    //cout <<  "MOVE" << endl;
                    listAction.push_back(Action(0,animal,&listCoord[j],SHIFT));
                  }
                }
              }
            } //end for
      } else if(selection.first->getID() == TIGER || selection.first->getID() == LEOPARD || selection.first->getID() == LION) {

          for (int j = 0; j<=(int)listCoord.size() ;j++) {
            if (listCoord[j].getX()<=11 && listCoord[j].getX()>=0 && listCoord[j].getY()<= 12 && listCoord[j].getY()>=0){
            selectionList = vertex->getSelection(vertex,listCoord[j]);
            squareId_list = map1[listCoord[j].getX()][listCoord[j].getY()].getID();
                if(squareId_list!= WATER){
                  //cout << "NOWATER!" << endl;
                  if(selectionList.first){
                    //cout << "SOMEONE!" << endl;
                    if(selectionList.second == selection.second){
                      //cout << "COPAIN!" << endl;
                      //do nothing
                    }
                    else{
                      if((selection.first->getID()>=selectionList.first->getID())||((squareId_list== TRAPJ1 && selectionList.second == 1 )||(squareId_list== TRAPJ2 && selectionList.second == 0))){
                          //cout << "A L'ATTAQUE!" << endl;
                          listAction.push_back(Action(0,animal,&listCoord[j],ATTACK));
                        }
                        else{
                          //cout <<"TROP FORT"<< endl;
                          //do nothing
                        }
                    }

                  }else{
                    if((squareId_list== TRAPJ1 && selection.second== 0 )||(squareId_list== TRAPJ2 && selection.second== 1)){
                      //cout <<"TRAP ALLIE" << endl;
                      listAction.push_back(Action(0,animal,&listCoord[j],SHIFT));
                    }
                    else if((squareId_list== TRAPJ1 && selection.second== 1 )||(squareId_list== TRAPJ2 && selection.second== 0)){
                      //cout <<"TRAPPED" << endl;
                      listAction.push_back(Action(0,animal,&listCoord[j],SHIFT_TRAPPED));
                    }
                    else if((squareId_list== THRONEJ1 && selection.second== 1 )||(squareId_list== THRONEJ2 && selection.second== 0)){
                    //cout <<  "VICTORY SOON" << endl;
                      listAction.push_back(Action(0,animal,&listCoord[j],SHIFT_VICTORY));
                    }
                    else if((squareId_list== THRONEJ1 && selection.second== 0 )||(squareId_list== THRONEJ2 && selection.second== 1)){
                    //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                      //do nothing
                    }
                    else{
                    //cout <<  "MOVE" << endl;
                      listAction.push_back(Action(0,animal,&listCoord[j],SHIFT));
                    }

                  }
                }else{
                  if(j == 0){
                    int compteur = 0;
                    for(int n = 0; n<=3; n++){
                      if(vertex->getSelection(vertex,Coord(listCoord[j].getX()+n, listCoord[j].getY())).first==NULL){
                        compteur += 1;
                      if (compteur == 4){
                        //cout <<"CAN JUMP" << endl;
                        listCoord[j] = Coord(listCoord[j].getX()+3, listCoord[j].getY());
                        listAction.push_back(Action(0,animal,&listCoord[j],JUMP));
                      }
                      else{
                        //do nothing
                      }
                    }
                  }

                  //Jump
                } else if(j==1){
                  int compteur = 0;
                  for(int n = 0; n<=3; n++){
                    if(vertex->getSelection(vertex,Coord(listCoord[j].getX()-n, listCoord[j].getY())).first==NULL){
                      compteur += 1;
                    if (compteur == 4){
                      //cout <<"CAN JUMP" << endl;
                      listCoord[j] = Coord(listCoord[j].getX()-3, listCoord[j].getY());
                      listAction.push_back(Action(0,animal,&listCoord[j],JUMP));
                    }
                    else{
                      //do nothing
                    }
                  }
                }
              }  else if(j==2){
                int compteur = 0;
                for(int n = 0; n<=3; n++){
                  if(vertex->getSelection(vertex,Coord(listCoord[j].getX(), listCoord[j].getY()+n)).first==NULL){
                    compteur += 1;
                  if (compteur == 4){
                    //cout <<"CAN JUMP" << endl;
                    listCoord[j] = Coord(listCoord[j].getX(), listCoord[j].getY()+3);
                    listAction.push_back(Action(0,animal,&listCoord[j],JUMP));
                    compteur = 0;
                  }
                  else{
                    //do nothing
                  }
                }
              }
            } else{
              int compteur = 0;
              for(int n = 0; n<=3; n++){
                if(vertex->getSelection(vertex,Coord(listCoord[j].getX(), listCoord[j].getY()-n)).first==NULL){
                  compteur += 1;
                if (compteur == 4){
                  //cout <<"CAN JUMP" << endl;
                  listCoord[j] = Coord(listCoord[j].getX(), listCoord[j].getY()-3);
                  listAction.push_back(Action(0,animal,&listCoord[j],JUMP));

                }
                else{
                  //do nothing

              }
            }
          }


           }
          }
         }
        }// end for
      }
    }
    return listAction;}


int DeepAI::getDistance(Coord& coord1, Coord& coord2){
  int distance;
  distance = abs(coord2.getX()-coord1.getX())+abs(coord2.getY()-coord1.getY());
  return distance;
}
