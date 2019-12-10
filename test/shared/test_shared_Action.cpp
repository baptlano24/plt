#include <boost/test/unit_test.hpp>
#include <ai.h>
#include <state.h>
#include <engine.h>

using namespace std;
using namespace ::ai;
using namespace ::state;
using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestAction){
  Coord test = Coord(0,0);
  Coord& ref = test;
  Action action = Action(120,NULL,ref,NONE);
  BOOST_CHECK_EQUAL(action.getScore(), 120);
  BOOST_CHECK(action.getAnimal() == NULL);
  BOOST_CHECK(action.getCoord() == Coord(0,0));
  action.setScore(55);
  BOOST_CHECK_EQUAL(action.getScore(), 55);
}
