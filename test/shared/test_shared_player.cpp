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
    std::vector<Animal> testAnimals;
    testAnimals.push_back(Animal({1,1},NORMAL,RAT)); //(x,y) en haut à gauche
    testAnimals.push_back(Animal({2,2},NORMAL,CAT));
    testAnimals.push_back(Animal({3,1},NORMAL,DOG));
    testAnimals.push_back(Animal({4,2},NORMAL,WOLF));
    testAnimals.push_back(Animal({7,2},NORMAL,LEOPARD));
    testAnimals.push_back(Animal({8,1},NORMAL,TIGER));
    testAnimals.push_back(Animal({9,2},NORMAL,LION));
    testAnimals.push_back(Animal({10,1},NORMAL,ELEPHANT));
    BOOST_CHECK_EQUAL(playerTest2.getName(),"Baba");
    BOOST_CHECK_EQUAL(playerTest2.getColor(),1);
    BOOST_CHECK(testAnimals.size() == playerTest2.getAnimals().size());
  }
  {
    Player playerTest3{"Jean Pierre", 10};
    std::vector<Animal> testAnimals;
    testAnimals.push_back(Animal({1,1},NORMAL,RAT)); //(x,y) en haut à gauche
    testAnimals.push_back(Animal({2,2},NORMAL,CAT));
    testAnimals.push_back(Animal({3,1},NORMAL,DOG));
    testAnimals.push_back(Animal({4,2},NORMAL,WOLF));
    testAnimals.push_back(Animal({7,2},NORMAL,LEOPARD));
    testAnimals.push_back(Animal({8,1},NORMAL,TIGER));
    testAnimals.push_back(Animal({9,2},NORMAL,LION));
    testAnimals.push_back(Animal({10,1},NORMAL,ELEPHANT));
    playerTest3.setColor(0);
    BOOST_CHECK_EQUAL(playerTest3.getName(),"Jean Pierre");
    BOOST_CHECK_EQUAL(playerTest3.getColor(),0);
    BOOST_CHECK(testAnimals.size() == playerTest3.getAnimals().size());
  }
}
