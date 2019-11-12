
#include <boost/test/unit_test.hpp>
#include <state.h>

using namespace ::state;

BOOST_AUTO_TEST_CASE(Animal_test)
{
    Animal animal {{0,0},NORMAL,RAT};
    BOOST_CHECK_EQUAL(animal.getCoord().getX(),0);
    BOOST_CHECK_EQUAL(animal.getCoord().getY(),0);
    BOOST_CHECK_EQUAL(animal.getStatus(),NORMAL);

    animal.setStatus(DEAD);
    animal.setCoord({1,1});
    BOOST_CHECK_EQUAL(animal.getStatus(),DEAD);
    BOOST_CHECK_EQUAL(animal.getCoord().getX(),1);
    BOOST_CHECK_EQUAL(animal.getCoord().getY(),1);
}
