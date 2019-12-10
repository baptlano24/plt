#include <boost/test/unit_test.hpp>
#include <ai.h>
#include <state.h>
#include <engine.h>

using namespace std;
using namespace ::ai;
using namespace ::state;
using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestAction){


  Action action = Action(120,NULL,NULL,NONE);
  BOOST_CHECK_EQUAL(action.getScore(), 120);
  BOOST_CHECK(action.getAnimal() == NULL);
  BOOST_CHECK(action.getCoord() == NULL);
  action.setScore(55);
  BOOST_CHECK_EQUAL(action.getScore(), 55);
}
