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

      if (vertex->getSelection(vertex,current_square).first->getID() == ELEPHANT || vertex->getSelection(vertex,current_square).first->getID() ==  CAT || vertex->getSelection(vertex,current_square).first->getID() == DOG || vertex->getSelection(vertex,current_square).first->getID() == WOLF){


        if(vertex->getSelection(vertex,current_square).first->getStatus() == NORMAL){
          //cout << "NORMAL!" << endl;

          for (int j = 0; j<=(int)listCoord.size() ;j++) {
            //if(map1[listCoord[j].getX()][listCoord[j].getY()]){
              if(map1[listCoord[j].getX()][listCoord[j].getY()].getID() != WATER){
                //cout << "NOWATER!" << endl;
                if(vertex->getSelection(vertex,listCoord[j]).first && vertex->getSelection(vertex,listCoord[j]).first->getStatus() != DEAD ){
                  //cout << "SOMEONE!" << endl;
                  if(vertex->getSelection(vertex,listCoord[j]).second == vertex->getSelection(vertex,current_square).second){
                    //cout << "COPAIN!" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                  }
                  else{
                    if((vertex->getSelection(vertex,current_square).first->getID()>=vertex->getSelection(vertex,listCoord[j]).first->getID())||((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ1 && vertex->getSelection(vertex,listCoord[j]).second == 1 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ2 && vertex->getSelection(vertex,listCoord[j]).second == 0))){
                        //cout << "A L'ATTAQUE!" << endl;
                        listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],ATTACK));
                      }
                      else{
                        //cout <<"TROP FORT"<< endl;
                        listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                      }
                  }
                } else {
                  if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ1 && vertex->getSelection(vertex,current_square).second== 0 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ2 && vertex->getSelection(vertex,current_square).second== 1)){
                    //cout <<"TRAP ALLIE" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT));
                  }
                  else if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ1 && vertex->getSelection(vertex,current_square).second== 1 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ2 && vertex->getSelection(vertex,current_square).second== 0)){
                    //cout <<"TRAPPED" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT_TRAPPED));
                  }
                  else if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ1 && vertex->getSelection(vertex,current_square).second== 1 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ2 && vertex->getSelection(vertex,current_square).second== 0)){
                  //cout <<  "VICTORY SOON" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT_VICTORY));
                  }
                  else if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ1 && vertex->getSelection(vertex,current_square).second== 0 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ2 && vertex->getSelection(vertex,current_square).second== 1)){
                  //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                  }
                  else {
                  //cout <<  "MOVE" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT));
                  }

                }
              }
              else if (map1[listCoord[j].getX()][listCoord[j].getY()].getID() == WATER) {
                //cout <<"WATER"<< endl;
                listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
              }
            //}
          } // end for
        }

      } else if (vertex->getSelection(vertex,current_square).first->getID() == RAT) {

        if(vertex->getSelection(vertex,current_square).first->getStatus() == NORMAL){
            for (int j = 0; j<=(int)listCoord.size() ;j++) {
              //if(state.getSquare(listCoord[j])){

                if(vertex->getSelection(vertex,listCoord[j]).first){
                    //cout << "SOMEONE!" << endl;
                  if(vertex->getSelection(vertex,listCoord[j]).second == vertex->getSelection(vertex,current_square).second){
                    //cout << "COPAIN!" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                  } else if(map1[listCoord[j].getX()][listCoord[j].getY()].getID() != WATER){
                      if(vertex->getSelection(vertex,listCoord[j]).first->getID() == ELEPHANT || vertex->getSelection(vertex,listCoord[j]).first->getID() == RAT){
                        //cout << "A L'ATTAQUE!" << endl;
                        listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],ATTACK));
                      }
                      else if((vertex->getSelection(vertex,listCoord[j]).second != vertex->getSelection(vertex,current_square).second)
                           && ((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ1 && vertex->getSelection(vertex,current_square).second== 0) || (map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ2 && vertex->getSelection(vertex,current_square).second== 1)) ){
                        //cout << " PIEGE ET A L'ATTAQUE!" << endl;
                        listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],ATTACK));
                        }
                       else{
                         //cout << "MOVE TRAP ALLIE OCCUPE" << endl;
                         listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                       }
                  } else {
                    if (map1[listCoord[j].getX()][listCoord[j].getY()].getID() == WATER) {
                      //cout << "ATTACK" << endl;
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],ATTACK));
                    } else {
                      //cout <<"Can't MOVE from WATER" << endl;
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                    }
                  }
                } else {
                  if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ1 && vertex->getSelection(vertex,current_square).second== 1 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ2 && vertex->getSelection(vertex,current_square).second== 0)){
                    //cout <<"TRAPPED" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT_TRAPPED));
                  }
                  else if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ1 && vertex->getSelection(vertex,current_square).second== 1 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ2 && vertex->getSelection(vertex,current_square).second== 0)){
                    //cout <<  "VICTORY SOON" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT_VICTORY));
                  }
                  else if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ1 && vertex->getSelection(vertex,current_square).second== 0 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ2 && vertex->getSelection(vertex,current_square).second== 1)){
                    //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                  }
                  else{
                    //cout <<  "MOVE" << endl;
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT));
                  }
                }
              //}
            } //end for
          }
      } else if(vertex->getSelection(vertex,current_square).first->getID() == TIGER || vertex->getSelection(vertex,current_square).first->getID() == LEOPARD || vertex->getSelection(vertex,current_square).first->getID() == LION) {

        if(vertex->getSelection(vertex,current_square).first->getStatus() == NORMAL){
          for (int j = 0; j<=(int)listCoord.size() ;j++) {
            //if(state.getSquare(listCoord[j])){
                if(map1[listCoord[j].getX()][listCoord[j].getY()].getID() != WATER){
                  //cout << "NOWATER!" << endl;
                  if(vertex->getSelection(vertex,listCoord[j]).first){
                    //cout << "SOMEONE!" << endl;
                    if(vertex->getSelection(vertex,listCoord[j]).second == vertex->getSelection(vertex,current_square).second){
                      //cout << "COPAIN!" << endl;
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                    }
                    else{
                      if((vertex->getSelection(vertex,current_square).first->getID()>=vertex->getSelection(vertex,listCoord[j]).first->getID())||((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ1 && vertex->getSelection(vertex,listCoord[j]).second == 1 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ2 && vertex->getSelection(vertex,listCoord[j]).second == 0))){
                          //cout << "A L'ATTAQUE!" << endl;
                          listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],ATTACK));
                        }
                        else{
                          //cout <<"TROP FORT"<< endl;
                          listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                        }
                    }

                  }else{
                    if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ1 && vertex->getSelection(vertex,current_square).second== 0 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ2 && vertex->getSelection(vertex,current_square).second== 1)){
                      //cout <<"TRAP ALLIE" << endl;
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT));
                    }
                    else if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ1 && vertex->getSelection(vertex,current_square).second== 1 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == TRAPJ2 && vertex->getSelection(vertex,current_square).second== 0)){
                      //cout <<"TRAPPED" << endl;
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT_TRAPPED));
                    }
                    else if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ1 && vertex->getSelection(vertex,current_square).second== 1 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ2 && vertex->getSelection(vertex,current_square).second== 0)){
                    //cout <<  "VICTORY SOON" << endl;
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT_VICTORY));
                    }
                    else if((map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ1 && vertex->getSelection(vertex,current_square).second== 0 )||(map1[listCoord[j].getX()][listCoord[j].getY()].getID() == THRONEJ2 && vertex->getSelection(vertex,current_square).second== 1)){
                    //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                    }
                    else{
                    //cout <<  "MOVE" << endl;
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],SHIFT));
                    }

                  }
                }else{
                  if(i == 0){
                    int compteur = 0;
                    for(int n = 0; n<=3; n++){
                      if(vertex->getSelection(vertex,Coord(listCoord[j].getX()+n, listCoord[j].getY())).first==NULL){
                        compteur += 1;
                      if (compteur == 4){
                        //cout <<"CAN JUMP" << endl;
                        listCoord[j] = Coord(listCoord[j].getX()+3, listCoord[j].getY());
                        listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],JUMP));
                      }
                      else{
                        listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                      }
                    }
                  }

                  //Jump
                } else if(i==1){
                  int compteur = 0;
                  for(int n = 0; n<=3; n++){
                    if(vertex->getSelection(vertex,Coord(listCoord[j].getX()-n, listCoord[j].getY())).first==NULL){
                      compteur += 1;
                    if (compteur == 4){
                      //cout <<"CAN JUMP" << endl;
                      listCoord[j] = Coord(listCoord[j].getX()-3, listCoord[j].getY());
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],JUMP));
                    }
                    else{
                      listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                    }
                  }
                }
              }  else if(i==2){
                int compteur = 0;
                for(int n = 0; n<=3; n++){
                  if(vertex->getSelection(vertex,Coord(listCoord[j].getX(), listCoord[j].getY()-n)).first==NULL){
                    compteur += 1;
                  if (compteur == 4){
                    //cout <<"CAN JUMP" << endl;
                    listCoord[j] = Coord(listCoord[j].getX(), listCoord[j].getY()-3);
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],JUMP));
                    compteur = 0;
                  }
                  else{
                    listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));
                  }
                }
              }
            } else{
              int compteur = 0;
              for(int n = 0; n<=3; n++){
                if(vertex->getSelection(vertex,Coord(listCoord[j].getX(), listCoord[j].getY()+n)).first==NULL){
                  compteur += 1;
                if (compteur == 4){
                  //cout <<"CAN JUMP" << endl;
                  listCoord[j] = Coord(listCoord[j].getX(), listCoord[j].getY()+3);
                  listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],JUMP));

                }
                else{
                  listAction.push_back(Action(0,&vertex->getMyAnimals()->at(i),&listCoord[j],NONE));

              }
            }
          }


           }
          }
        // }
        }// end for
       }
      }
    }
    return listAction;}


int DeepAI::getDistance(Coord& coord1, Coord& coord2){
  int distance;
  distance = abs(coord2.getX()-coord1.getX())+abs(coord2.getY()-coord1.getY());
  return distance;
}
