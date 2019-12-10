#include <boost/test/unit_test.hpp>
#include <ai.h>
#include <state.h>

using namespace std;
using namespace ::ai;
using namespace ::state;


BOOST_AUTO_TEST_CASE(TestAvancedAI){
  engine::Engine engine;
  engine::Engine* ptr_engine = &engine;
  //state::Coord coord = Coord(0,0);
  //state::Coord coord1 = Coord(1,1);
  //state::Coord& ref_coord = coord;
  //state::Coord& ref_coord1 = coord1;

  HeuristicAI Test = HeuristicAI(0);
  Test.play(ptr_engine);
  Test.selectAnimal(ptr_engine);
  //Test.selectAction(ptr_engine,ref_coord);
  //Test.getDistance(ref_coord,ref_coord1);

}
