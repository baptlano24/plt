#include <boost/test/unit_test.hpp>
#include <ai.h>
#include <state.h>

using namespace std;
using namespace ai;
using namespace state;


BOOST_AUTO_TEST_CASE(TestDeepAI){
  engine::Engine engine;
  engine::Engine* ptr_engine = &engine;

  DeepAI deepTest = DeepAI(0, ptr_engine);
  deepTest.play(ptr_engine);
}
