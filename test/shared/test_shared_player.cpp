#include <boost/test/unit_test.hpp>
#include <state.h>
#include <unordered_map>
#include <utility>
using namespace ::state;
using namespace std;

BOOST_AUTO_TEST_CASE(TestPlayer)
{
  {
    Player playerTest1{};
    BOOST_CHECK_EQUAL(playerTest1.getName(),"Joueur");
    BOOST_CHECK_EQUAL(playerTest1.getColor(),0);
    BOOST_CHECK_EQUAL(playerTest1.getPlaying(),0);
    playerTest1.setName("Bob");
    playerTest1.setColor(2);
    playerTest1.setPlaying(1);
    BOOST_CHECK_EQUAL(playerTest1.getName(),"Bob");
    BOOST_CHECK_EQUAL(playerTest1.getColor(),2);
    BOOST_CHECK_EQUAL(playerTest1.getPlaying(),1);
  }

  {
    Player playerTest2{"Baba",4,0};
    BOOST_CHECK_EQUAL(playerTest2.getName(),"Baba");
    BOOST_CHECK_EQUAL(playerTest2.getColor(),4);
    BOOST_CHECK_EQUAL(playerTest2.getPlaying(),0);
  }
  {
    Player playerTest3{};
    std::unordered_map<int, Animal> testAnimals;
    testAnimals.insert(make_pair(1,Animal(0,0,NORMAL)));
    testAnimals.insert(make_pair(2,Animal(0,0,NORMAL)));
    testAnimals.insert(make_pair(3,Animal(0,0,NORMAL)));
    testAnimals.insert(make_pair(4,Animal(0,0,NORMAL)));
    testAnimals.insert(make_pair(5,Animal(0,0,NORMAL)));
    testAnimals.insert(make_pair(6,Animal(0,0,NORMAL)));
    testAnimals.insert(make_pair(7,Animal(0,0,NORMAL)));
    testAnimals.insert(make_pair(8,Animal(0,0,NORMAL)));
    BOOST_CHECK_EQUAL(playerTest3.getName(),"Joueur");
    BOOST_CHECK(testAnimals.size() == playerTest3.getAnimals().size());
    //BOOST_CHECK(testAnimals == playerTest3.getAnimals());
    //BOOST_CHECK_EQUAL_COLLECTIONS(testAnimals.begin(), testAnimals.end(), playerTest3.getAnimals().begin(), playerTest3.getAnimals().end());
  }
}
