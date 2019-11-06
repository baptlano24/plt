#include <boost/test/unit_test.hpp>
#include <state.h>
#include <unordered_map>
#include <utility>
using namespace ::state;
using namespace std;

BOOST_AUTO_TEST_CASE(TestPlayer)
{
  {
    /*Player playerTest1{};
    BOOST_CHECK_EQUAL(playerTest1.getName(),"Joueur");
    BOOST_CHECK_EQUAL(playerTest1.getColor(),0);
    playerTest1.setName("Bob");
    playerTest1.setColor(2);
    BOOST_CHECK_EQUAL(playerTest1.getName(),"Bob");
    BOOST_CHECK_EQUAL(playerTest1.getColor(),2);*/
  }

  {
    Player playerTest2{"Baba",1};
    std::unordered_map<AnimalID,Animal> testAnimals;
    testAnimals.insert(make_pair(RAT,Animal({10,11},NORMAL))); //(x,y) en haut à gauche
    testAnimals.insert(make_pair(CAT,Animal({9,10},NORMAL)));
    testAnimals.insert(make_pair(DOG,Animal({8,11},NORMAL)));
    testAnimals.insert(make_pair(WOLF,Animal({7,10},NORMAL)));
    testAnimals.insert(make_pair(LEOPARD,Animal({4,10},NORMAL)));
    testAnimals.insert(make_pair(TIGER,Animal({3,11},NORMAL)));
    testAnimals.insert(make_pair(LION,Animal({2,10},NORMAL)));
    testAnimals.insert(make_pair(ELEPHANT,Animal({1,11},NORMAL)));
    BOOST_CHECK_EQUAL(playerTest2.getName(),"Baba");
    BOOST_CHECK_EQUAL(playerTest2.getColor(),1);
    BOOST_CHECK(testAnimals.size() == playerTest2.getAnimals().size());
  }
  {
    Player playerTest3{"Jean Pierre", 10};
    std::unordered_map<AnimalID,Animal> testAnimals;
    testAnimals.insert(make_pair(RAT,Animal({2,6},NORMAL))); //(x,y) en haut à gauche
    testAnimals.insert(make_pair(CAT,Animal({3,6},NORMAL)));
    testAnimals.insert(make_pair(DOG,Animal({4,6},NORMAL)));
    testAnimals.insert(make_pair(WOLF,Animal({5,6},NORMAL)));
    testAnimals.insert(make_pair(LEOPARD,Animal({6,6},NORMAL)));
    testAnimals.insert(make_pair(TIGER,Animal({7,6},NORMAL)));
    testAnimals.insert(make_pair(LION,Animal({8,6},NORMAL)));
    testAnimals.insert(make_pair(ELEPHANT,Animal({9,6},NORMAL)));
    BOOST_CHECK_EQUAL(playerTest3.getName(),"Jean Pierre");
    BOOST_CHECK_EQUAL(playerTest3.getColor(),10);
    BOOST_CHECK(testAnimals.size() == playerTest3.getAnimals().size());
  }
}
