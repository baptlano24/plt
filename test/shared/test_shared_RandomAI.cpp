#include <boost/test/unit_test.hpp>
#include <ai.h>

using namespace ::ai;


BOOST_AUTO_TEST_CASE(TestRandomAI)
{
  engine::Engine engine;
  engine::Engine* ptr_engine = &engine;
  RandomAI randomAItest0(0);
  RandomAI randomAItest1(1);
  randomAItest0.play(ptr_engine);
  randomAItest1.play(ptr_engine);
}
