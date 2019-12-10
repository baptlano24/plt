#include <boost/test/unit_test.hpp>
#include <ai.h>

using namespace ::ai;


BOOST_AUTO_TEST_CASE(TestNoviceAI)
{
  engine::Engine engine;
  engine::Engine* ptr_engine = &engine;
  NoviceAI novAItest0(0);
  NoviceAI novAItest1(1);
  novAItest0.play(ptr_engine);
  novAItest1.play(ptr_engine);
}
