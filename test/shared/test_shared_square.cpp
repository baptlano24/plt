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
    Square square{EARTH};
    BOOST_CHECK_EQUAL(square.getID(),EARTH);
  }
  {
    Square square{SHORE};
    BOOST_CHECK_EQUAL(square.getID(),SHORE);
  }
  {
    Square square{WATER};
    BOOST_CHECK_EQUAL(square.getID(),WATER);
  }
  {
    Square square{TRAPJ1};
    BOOST_CHECK_EQUAL(square.getID(),TRAPJ1);
  }
  {
    Square square{TRAPJ2};
    BOOST_CHECK_EQUAL(square.getID(),TRAPJ2);
  }
  {
    Square square{THRONEJ1};
    BOOST_CHECK_EQUAL(square.getID(),THRONEJ1);
  }
  {
    Square square{THRONEJ2};
    BOOST_CHECK_EQUAL(square.getID(),THRONEJ2);
  }
  {
    Square square{};
    BOOST_CHECK_EQUAL(square.getID(),EARTH);
    square.setID(TRAPJ1);
    BOOST_CHECK_EQUAL(square.getID(),TRAPJ1);
  }

}
