#include <boost/test/unit_test.hpp>
#include <state.h>


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestState)
{

    State state1{};
    state1.getPlayer1().getName();
    state1.getPlayer2().getName();
    State state2{"booba","caca"};
    //state.getPlayer1().setName("Tony");
    //BOOST_CHECK_EQUAL(state1.getPlayer1().getName(), "Robin");
}
