#include <boost/test/unit_test.hpp>
#include <state.h>


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestPlayer)
{
  {
    Player player{};
    BOOST_CHECK_EQUAL(player.getName(),"Joueur");
    BOOST_CHECK_EQUAL(player.getColor(),0);
    BOOST_CHECK_EQUAL(player.getPlaying(),0);
    player.setName("Bob");
    player.setColor(2);
    player.setPlaying(1);
    BOOST_CHECK_EQUAL(player.getName(),"Bob");
    BOOST_CHECK_EQUAL(player.getColor(),2);
    BOOST_CHECK_EQUAL(player.getPlaying(),1);

  }

  {
    Player player{"Baba",4,0};
    BOOST_CHECK_EQUAL(player.getName(),"Baba");
    BOOST_CHECK_EQUAL(player.getColor(),4);
    BOOST_CHECK_EQUAL(player.getPlaying(),0);
  }
}
