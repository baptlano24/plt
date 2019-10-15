#include <boost/test/unit_test.hpp>
#include <state.h>

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestSquare)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestSquare1)
{
  {
    Square square{1,EARTH};
    BOOST_CHECK_EQUAL(square.isEmpty(),1);
    BOOST_CHECK_EQUAL(square.getID(),EARTH);
  }
  {
    Square square{1,SHORE};
    BOOST_CHECK_EQUAL(square.isEmpty(),1);
    BOOST_CHECK_EQUAL(square.getID(),SHORE);
  }
  {
    Square square{1,WATER};
    BOOST_CHECK_EQUAL(square.isEmpty(),1);
    BOOST_CHECK_EQUAL(square.getID(),WATER);
  }
  {
    Square square{1,TRAPJ1};
    BOOST_CHECK_EQUAL(square.isEmpty(),1);
    BOOST_CHECK_EQUAL(square.getID(),TRAPJ1);
  }
  {
    Square square{1,TRAPJ2};
    BOOST_CHECK_EQUAL(square.isEmpty(),1);
    BOOST_CHECK_EQUAL(square.getID(),TRAPJ2);
  }
  {
    Square square{1,THRONEJ1};
    BOOST_CHECK_EQUAL(square.isEmpty(),1);
    BOOST_CHECK_EQUAL(square.getID(),THRONEJ1);
  }
  {
    Square square{1,THRONEJ2};
    BOOST_CHECK_EQUAL(square.isEmpty(),1);
    BOOST_CHECK_EQUAL(square.getID(),THRONEJ2);
  }
  {
    Square square{0,EARTH};
    BOOST_CHECK_EQUAL(square.isEmpty(),0);
    BOOST_CHECK_EQUAL(square.getID(),EARTH);
  }
  {
    Square square{0,SHORE};
    BOOST_CHECK_EQUAL(square.isEmpty(),0);
    BOOST_CHECK_EQUAL(square.getID(),SHORE);
  }
  {
    Square square{0,WATER};
    BOOST_CHECK_EQUAL(square.isEmpty(),0);
    BOOST_CHECK_EQUAL(square.getID(),WATER);
  }
  {
    Square square{0,TRAPJ1};
    BOOST_CHECK_EQUAL(square.isEmpty(),0);
    BOOST_CHECK_EQUAL(square.getID(),TRAPJ1);
  }
  {
    Square square{0,TRAPJ2};
    BOOST_CHECK_EQUAL(square.isEmpty(),0);
    BOOST_CHECK_EQUAL(square.getID(),TRAPJ2);
  }
  {
    Square square{0,THRONEJ1};
    BOOST_CHECK_EQUAL(square.isEmpty(),0);
    BOOST_CHECK_EQUAL(square.getID(),THRONEJ1);
  }
  {
    Square square{0,THRONEJ2};
    BOOST_CHECK_EQUAL(square.isEmpty(),0);
    BOOST_CHECK_EQUAL(square.getID(),THRONEJ2);
  }
  {
    Square square{};
    BOOST_CHECK_EQUAL(square.isEmpty(),1);
    BOOST_CHECK_EQUAL(square.getID(),EARTH);
    square.setID(TRAPJ1);
    square.setEmpty(0);
    BOOST_CHECK_EQUAL(square.isEmpty(),0);
    BOOST_CHECK_EQUAL(square.getID(),TRAPJ1);
  }

}
