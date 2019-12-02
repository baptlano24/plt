#include <boost/test/unit_test.hpp>
#include <state.h>


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestState)
{
  {
    State state1{};
    state1.getPlayer1().setName("Bibou");
    BOOST_CHECK_EQUAL(state1.getPlayer1().getName(), "Bibou");
    BOOST_CHECK_EQUAL(state1.getMenu(), GAME_MENU);
    state1.setMenu(SETTINGS_MENU);
    BOOST_CHECK_EQUAL(state1.getMenu(), SETTINGS_MENU);
    BOOST_CHECK_EQUAL(state1.getGameover(), 0);
    state1.setGameover(1);
    state1.setWinner(state1.getPlayer1());
    BOOST_CHECK_EQUAL(state1.getGameover(), 1);
    BOOST_CHECK_EQUAL(state1.getWinner().getColor(), state1.getPlayer1().getColor());


  }
  {
    State state2{"booba","baboo"};
    BOOST_CHECK_EQUAL(state2.getPlayer1().getName(), "booba");
    BOOST_CHECK_EQUAL(state2.getPlayer2().getName(), "baboo");
  }
  {
    State state3{};
    Square squareTest = state3.getGrid()[0][0];
    BOOST_CHECK_EQUAL(state3.getSquare(Coord{0,0})->getID(), squareTest.getID());

    /*BOOST_CHECK_EQUAL(state3.getSquare(Coord{-1,2})->getID(), NULL);
    BOOST_CHECK_EQUAL(state3.getSquare(Coord{15,2})->getID(), NULL);
    BOOST_CHECK_EQUAL(state3.getSquare(Coord{5,-10})->getID(), NULL);
    BOOST_CHECK_EQUAL(state3.getSquare(Coord{5,100})->getID(), NULL);*/
  }
}
