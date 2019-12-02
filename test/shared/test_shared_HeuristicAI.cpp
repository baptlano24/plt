#include <boost/test/unit_test.hpp>
#include <ai.h>

using namespace ::ai;


BOOST_AUTO_TEST_CASE(TestHeuristicAI)
{
  engine::Engine engine;
  engine::Engine* ptr_engine = &engine;
  HeuristicAI heuAItest0(0);
  HeuristicAI heuAItest1(1);
  heuAItest0.play(ptr_engine);
  heuAItest1.play(ptr_engine);
}
