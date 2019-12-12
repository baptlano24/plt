#include <boost/test/unit_test.hpp>
#include <state.h>

using namespace ::state;

BOOST_AUTO_TEST_CASE(Coord_test)
{
    {
        Coord coord {};
        BOOST_CHECK_EQUAL(coord.getX(),0);
        BOOST_CHECK_EQUAL(coord.getY(),0);
        coord.setX(12);
        coord.setY(20);
        BOOST_CHECK_EQUAL(coord.getX(),12);
        BOOST_CHECK_EQUAL(coord.getY(),20);
    }
    {
        Coord coord2 {5,1};
        BOOST_CHECK_EQUAL(coord2.getX(),5);
        BOOST_CHECK_EQUAL(coord2.getY(),1);
    }
    {
      Coord coucou (0,1);
      Coord coucou2 (0,1);

      BOOST_CHECK(coucou == coucou2);
    }

}
