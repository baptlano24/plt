#include <boost/test/unit_test.hpp>
#include <state.h>


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestState)
{
    State state1{"Robin","Baptiste"};
    //state.getPlayer1().setName("Tony");
    //BOOST_CHECK_EQUAL(state1.getPlayer1().getName(), "Robin");
}
