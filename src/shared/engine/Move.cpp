#include "../state/State.h"
#include "Engine.h"
#include "Order.h"
#include "Move.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;


Move::Move(Animal* targetAnimal, Coord& targetCoord):targetAnimal(targetAnimal),targetCoord(targetCoord){
    this->ID = MOVE;
    this->player = 0;
}

void Move::execute(Engine* engine)
{
  /*
  cout<<"Début du tour numéro : " << engine->getState().getTurn() << endl;
  cout<<"Anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
  cout<<"Nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
  */
  //State& refTest1 = engine->getState();
  //Coord& refTest2 = this->targetAnimal->getCoord();
  //cout<<"test coord:" << engine->authorisedActions(refTest1,refTest2)[0].first.getX() << " x " << endl;

  for (int i =0 ;i<=3 ;i++){
    if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].first == this->targetCoord){

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == SHIFT)//Higlight = 1 pour moove
      {
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == ATTACK )//Higlight = 2 pour attack
      {
        engine->getState().getSelection(this->targetCoord).first->setStatus(DEAD);
        cout<<"AnimalAdverseDEAD" <<endl;
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == JUMP)//Higlight = 3 pour moove
      {
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == SHIFT_TRAPPED)//Higlight = 4 pour moove
      {

        cout<<"Animal TRAPPED" <<endl;
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == SHIFT_VICTORY)//Higlight = 4 pour moove
      {
        cout<<"Animal VICTORY" <<endl;
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }
    }
  }

  //cout<<"Nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;

  engine->getState().setTurn(engine->getState().getTurn()+1);
  cout<<"Passage au tour numéro : " << engine->getState().getTurn() << endl;

}
