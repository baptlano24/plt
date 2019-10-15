
#include <boost/test/unit_test.hpp>
#include <state.h>

using namespace ::state;

BOOST_AUTO_TEST_CASE(Animal_test)
{
    Animal animal {0,0,NORMAL};
    BOOST_CHECK_EQUAL(animal.getX(),0);
    animal.setX(1);
    BOOST_CHECK_EQUAL(animal.getX(),1);
    animal.setY(1);
    BOOST_CHECK_EQUAL(animal.getY(),1);
    BOOST_CHECK_EQUAL(animal.getStatus(),NORMAL);
    animal.setStatus(DEAD);
    BOOST_CHECK_EQUAL(animal.getStatus(),DEAD);
    animal.setStatus(NORMAL);
    BOOST_CHECK_EQUAL(animal.getStatus(),NORMAL);
    animal.setStatus(TRAPPED);
    BOOST_CHECK_EQUAL(animal.getStatus(),TRAPPED);
}
