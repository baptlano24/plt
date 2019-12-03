#include <boost/test/unit_test.hpp>
#include <engine.h>
#include <state.h>


using namespace ::engine;
using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestEngine)
{
  Engine engine;
  Engine* ptr_engine = &engine;
  state::State& ref_state = engine.getState();
  //std::vector<std::pair<state::Coord,engine::ActionID>> testAuth;
  //testAuth.push_back(make_pair(state::Coord(1,0),engine::ActionID(SHIFT)))
  //testAuth.push_back(make_pair(state::Coord(0,1),engine::ActionID(SHIFT)))
  //testAuth.push_back(make_pair(state::Coord(1,2),engine::ActionID(SHIFT)))
  //testAuth.push_back(make_pair(state::Coord(2,1),engine::ActionID(SHIFT)))
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
    Coord initCoord = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(i,2));
    engine.getState().getPlayer2().getAnimals()[i].setCoord(Coord(i,3));
    state::Coord& ref_Coord = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(initCoord);
    engine.getState().getPlayer2().getAnimals()[i].setCoord(initCoord);
  }

  for(int i =0;i<=7;i++){
    Coord initCoord = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(5,1));
    engine.getState().getPlayer2().getAnimals()[i].setCoord(Coord(5,1));
    state::Coord& ref_Coord = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(Coord(5,2));
    engine.getState().getPlayer2().getAnimals()[i].setCoord(Coord(5,2));
    state::Coord& ref_Coord2 = engine.getState().getPlayer1().getAnimals()[i].getCoord();
    engine.authorisedActions(ref_state,ref_Coord);
    engine.getState().getPlayer1().getAnimals()[i].setCoord(initCoord);
    engine.getState().getPlayer2().getAnimals()[i].setCoord(initCoord);
  }



}
