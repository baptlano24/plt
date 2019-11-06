#include <boost/test/unit_test.hpp>
#include <state.h>

using namespace ::state;

BOOST_AUTO_TEST_CASE(StateEvent_test)
{
    StateEvent stateEvent {ALL_CHANGED};
    BOOST_CHECK_EQUAL(stateEvent.getID(),ALL_CHANGED);
    stateEvent.setID(TURN_CHANGED);
    BOOST_CHECK_EQUAL(stateEvent.getID(),TURN_CHANGED);
}
