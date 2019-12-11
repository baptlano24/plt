#include <boost/test/unit_test.hpp>
#include <ai.h>
#include <state.h>

using namespace std;
using namespace ::ai;
using namespace ::state;


BOOST_AUTO_TEST_CASE(TestHeuristicAI){
  engine::Engine engine;
  engine::Engine* ptr_engine = &engine;

  HeuristicAI heuTest = HeuristicAI(0);
  heuTest.play(ptr_engine);
  heuTest.selectAnimal(ptr_engine);

}
