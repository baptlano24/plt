#include "../state/State.h"
#include "engine.h"
#include "Order.h"
#include "Move.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;

Move::Move(state::Animal* targetAnimal, state::Coord& targetCoord): targetAnimal(targetAnimal),targetCoord(targetCoord){

}


void engine::Move::execute(engine::Engine* engine)
{
  /*
  cout<<"Début du tour numéro : " << engine->getState().getTurn() << endl;
  cout<<"Anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
  cout<<"Nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
  */
  //State& refTest1 = engine->getState();
  //Coord& refTest2 = this->targetAnimal->getCoord();
  //cout<<"test coord:" << engine->authorisedActions(refTest1,refTest2)[0].first.getX() << " x " << endl;
  //this->targetAnimal->setCoord(this->targetCoord);


  for (int i =0 ;i<=3 ;i++){
    if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].first == this->targetCoord){

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == SHIFT)//Higlight = 1 pour moove
      {
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == ATTACK )//Higlight = 2 pour attack
      {
        engine->getState().getSelection(this->targetCoord).first->setStatus(DEAD);
        cout<<"AnimalAdverseDEAD" <<endl;
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == JUMP)//Higlight = 3 pour moove
      {
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == SHIFT_TRAPPED)//Higlight = 4 pour moove
      {

        cout<<"Animal TRAPPED" <<endl;
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord())[i].second == SHIFT_VICTORY)//Higlight = 4 pour moove
      {
        cout<<"Animal VICTORY" <<endl;
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }
    }
  }


  //cout<<"Nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;

  //engine->getState().setTurn(engine->getState().getTurn()+1);
  cout<<"Passage au tour numéro : " << engine->getState().getTurn() << endl;

}


/*void engine::Move::execute(engine::Engine* engine)
{
  for (int i =0 ;i<=3 ;i++){
    if (engine->authorisedActions(engine->getState(),this->target)[i].first == this->destination){


      if (engine->authorisedActions(engine->getState(),this->target)[i].second == SHIFT)//Higlight = 1 pour moove
      {
        cout<<"anciennes coord:" << this->target.getX() <<","<< this->target.getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->destination.getX() <<","<< this->destination.getY() <<endl;
        engine->getState().getSelection(this->target).first->setCoord(this->destination);
        cout<<"nouvelles coord:" << this->target.getX() <<","<< this->target.getY() <<endl;

      }
      if (engine->authorisedActions(engine->getState(),this->target)[i].second == ATTACK )//Higlight = 2 pour attack
      {
        engine->getState().getSelection(this->destination).first->setStatus(DEAD);
        cout<<"AnimalAdverseDEAD" <<endl;
        cout<<"anciennes coord:" << this->target.getX() <<","<< this->target.getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->destination.getX() <<","<< this->destination.getY() <<endl;
        engine->getState().getSelection(this->target).first->setCoord(this->destination);

        cout<<"nouvelles coord:" << this->target.getX() <<","<< this->target.getY() <<endl;

      }
      if (engine->authorisedActions(engine->getState(),this->target)[i].second == JUMP)//Higlight = 3 pour moove
      {
        cout<<"anciennes coord:" << this->target.getX() <<","<< this->target.getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->destination.getX() <<","<< this->destination.getY() <<endl;
        engine->getState().getSelection(this->target).first->setCoord(this->destination);

        cout<<"nouvelles coord:" << this->target.getX() <<","<< this->target.getY() <<endl;

;
      }
      if (engine->authorisedActions(engine->getState(),this->target)[i].second == SHIFT_TRAPPED)//Higlight = 4 pour moove
      {

        cout<<"Animal TRAPPED" <<endl;
        cout<<"anciennes coord:" << this->target.getX() <<","<< this->target.getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->destination.getX() <<","<< this->destination.getY() <<endl;

        engine->getState().getSelection(this->target).first->setCoord(this->destination);
        cout<<"nouvelles coord:" << this->target.getX() <<","<< this->target.getY() <<endl;



      }
      if (engine->authorisedActions(engine->getState(),this->target)[i].second == SHIFT_VICTORY)//Higlight = 4 pour moove
      {

        cout<<"Animal VICTORY" <<endl;
        cout<<"anciennes coord:" << this->target.getX() <<","<< this->target.getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->destination.getX() <<","<< this->destination.getY() <<endl;

        engine->getState().getSelection(this->target).first->setCoord(this->destination);
        cout<<"nouvelles coord:" << this->target.getX() <<","<< this->target.getY() <<endl;

      }

    }}}


  //cout<<"anciennes coord:" << this->target->getCoord().getX() <<","<< this->target->getCoord().getY() <<endl;
  //cout<<"nouvelles coord demandees:" << this->destination.getX() <<","<< this->destination.getY() <<endl;

  //this->target.setCoord(this->destination);
  //cout<<"nouvelles coord:" << this->target->getCoord().getX() <<","<< this->target->getCoord().getY() <<endl;
  if (this->target.getStatus()==NORMAL)
  {
    if(state.getSquare(this->target.getCoord()).getID() == EARTH && state.getSquare(this->destination).getID()==EARTH)
    {

      this->target.setCoord(this->destination);
    }
  }*/


/*void engine:: Move::select(engine::Engine* engine) {
  for (int i =0 ;i<=3 ;i++){
    if (engine->authorisedActions(engine->getState(),this->target)[i].second == NONE)//Higlight = 0 pour rien
    {
      //engine->getState().getSquare(engine->authorisedActions(engine->getState(),this->target)[i].first)->setHighlight(0);
    }

    if (engine->authorisedActions(engine->getState(),this->target)[i].second == SHIFT)//Higlight = 1 pour moove
    {
      //engine->getState().getSquare(engine->authorisedActions(engine->getState(),this->target)[i].first)->setHighlight(1);
    }
    if (engine->authorisedActions(engine->getState(),this->target)[i].second == ATTACK )//Higlight = 2 pour attack
    {
      //engine->getState().getSquare(engine->authorisedActions(engine->getState(),this->target)[i].first)->setHighlight(2);
    }
    if (engine->authorisedActions(engine->getState(),this->target)[i].second == JUMP)//Higlight = 3 pour moove
    {
      //engine->getState().getSquare(engine->authorisedActions(engine->getState(),this->target)[i].first)->setHighlight(3);
    }
    if (engine->authorisedActions(engine->getState(),this->target)[i].second == SHIFT_TRAPPED)//Higlight = 4 pour moove
    {
      //engine->getState().getSquare(engine->authorisedActions(engine->getState(),this->target)[i].first)->setHighlight(4);
    }
    else{
      //engine->getState().getSquare(engine->authorisedActions(engine->getState(),this->target)[i].first)->setHighlight(5);
    }


}}*/
