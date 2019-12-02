#include <boost/test/unit_test.hpp>
#include <engine.h>


using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestEngine)
{
  Engine engine;
  Engine* ptr_engine = &engine;
  std::vector<std::pair<state::Coord,engine::ActionID>> testAuth;
  testAuth.push_back(make_pair(state::Coord(1,0),engine::ActionID(SHIFT)))
  testAuth.push_back(make_pair(state::Coord(0,1),engine::ActionID(SHIFT)))
  testAuth.push_back(make_pair(state::Coord(1,2),engine::ActionID(SHIFT)))
  testAuth.push_back(make_pair(state::Coord(2,1),engine::ActionID(SHIFT)))

}
