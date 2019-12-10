#include <boost/test/unit_test.hpp>
#include <engine.h>
#include <state.h>
#include <iostream>
#include <utility>

using namespace std;
using namespace ::engine;
using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestEngine)
{
  Engine engine;
  //Engine* ptr_engine = &engine;
  state::State& ref_state = engine.getState();

  //engine.getState().getPlayer1().getAnimals()[7].setCoord(Coord(10,10));
  //engine.getState().getPlayer1().getAnimals()[5].setCoord(Coord(5,5));
  //engine.getState().getPlayer1().getAnimals()[0].setCoord(Coord(5,6));
  //state::Coord& ref_Coordelephant = engine.getState().getPlayer1().getAnimals()[7].getCoord();

  //engine.authorisedActions(ref_state,ref_Coordelephant);

  for(int i =0;i<=7;i++){
    Coord initCoord = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(5,5));
    state::Coord& ref_Coord = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(initCoord);
  }

  for(int i =0;i<=7;i++){
    Coord initCoord = engine.getState().getPlayer1().getAnimals()[i].getCoord();

    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(4,4));
    state::Coord& ref_Coord = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(1,6));
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(1,5));
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(10,5));
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(8,8));
    engine.authorisedActions(ref_state,ref_Coord);


    engine.getState().getPlayer1().getAnimals()[i].setCoord(initCoord);
  }

  for(int i =0;i<=7;i++){
    Coord initCoord1 = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    Coord initCoord2 = engine.getState().getPlayer2().getAnimals()[i].getCoord();
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(i,2));
    engine.getState().getPlayer2().getAnimals()[i].setCoord(Coord(i,3));
    state::Coord& ref_Coord = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(initCoord1);
    engine.getState().getPlayer2().getAnimals()[i].setCoord(initCoord2);
  }

  for(int i =0;i<=7;i++){
    Coord initCoord1 = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    Coord initCoord2 = engine.getState().getPlayer2().getAnimals()[i].getCoord();
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(5,1));
    engine.getState().getPlayer2().getAnimals()[i].setCoord(Coord(5,1));
    state::Coord& ref_Coord = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(5,2));
    engine.getState().getPlayer2().getAnimals()[i].setCoord(Coord(5,2));
    //state::Coord& ref_Coord2 = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(initCoord1);
    engine.getState().getPlayer2().getAnimals()[i].setCoord(initCoord2);
  }


  engine.getState().getPlayer1().getAnimals()[0].setCoord(Coord(1,1));//RAT J1 placé en (1,1)


  engine.getState().getPlayer1().getAnimals()[1].setCoord(Coord(2,1));//CAT J1 placé en (2,1) droite
  engine.getState().getPlayer2().getAnimals()[2].setCoord(Coord(0,1));//CAT J2 placé en (0,1) gauche
  engine.getState().getPlayer2().getAnimals()[7].setCoord(Coord(1,2));// Elephant J2 placé en (1,2) devant
  //engine.getState().getPlayer2().getAnimals()[1].setCoord(Coord(1,0));//DOG J2 placé en (1,0) derrière

  Coord newCord = Coord(1,1);
  state::Coord& ref_Coord = newCord;
  engine.authorisedActions(ref_state,ref_Coord);
  std::vector<std::pair<state::Coord,engine::ActionID>> testAuth;
  std::vector<std::pair<state::Coord,engine::ActionID>> auth;
  testAuth.push_back(std::make_pair(state::Coord(2,1),engine::ActionID(NONE)));
  testAuth.push_back(std::make_pair(state::Coord(0,1),engine::ActionID(NONE)));
  testAuth.push_back(std::make_pair(state::Coord(1,0),engine::ActionID(SHIFT)));
  testAuth.push_back(std::make_pair(state::Coord(1,2),engine::ActionID(ATTACK)));

  for (int i =0; i<=3;i++){
    auth = engine.authorisedActions(engine.getState(),ref_Coord);
    BOOST_CHECK(testAuth[i].first == auth[i].first);
    BOOST_CHECK(testAuth[i].second == auth[i].second);
  }


  //engine.getState().getPlayer1().getAnimals()[0].setCoord(Coord(3,6)); //RAT J1 en (3,6)
  //testAuth.push_back(std::make_pair(Coord(4,6),engine::ActionID(SHIFT)));
  //testAuth.push_back(std::make_pair(state::Coord(2,6),engine::ActionID(SHIFT)));
  //testAuth.push_back(std::make_pair(state::Coord(3,7),engine::ActionID(SHIFT)));
  //testAuth.push_back(std::make_pair(state::Coord(4,5),engine::ActionID(SHIFT)));

  //for (int i =0; i<=4;i++){
  //BOOST_CHECK_EQUAL(testAuth[0].first,engine.authorisedActions(ref_state,ref_Coord)[0].first );
  //BOOST_CHECK_EQUAL(testAuth[i].second,engine.authorisedActions(ref_state,ref_Coord)[i].second );
  //}








}
