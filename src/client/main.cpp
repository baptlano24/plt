#include <iostream>
#include <string> //pour utiliser string::compare
#include <utility>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <state.h>
#include "state.h"
#include "render.h"
#include <engine.h>
#include "engine.h"
#include "ai.h"
using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;
using namespace ai;

void playerVSplayer();
void randomVSrandom();
void randomVSheuristic();
void heuristicVSheuristic();

int main(int argc,char* argv[1]) {
  if(argc>=2 && string(argv[1])=="hello") {
    cout << "Hello world !" << endl;
  } else if (argc>=2 && string(argv[1])=="pVSp") {
    playerVSplayer();
  } else if (argc>=2 && string(argv[1])=="rVSr") {
    randomVSrandom();
  } else if (argc>=2 && string(argv[1])=="rVSh") {
    randomVSheuristic();
  } else if (argc>=2 && string(argv[1])=="hVSh") {
    heuristicVSheuristic();
  } else {
    cout << "Veuillez dire une commande parmis les suivantes :" << endl;
    cout << "-->  hello  -> (phrase d'accueil) " << endl;
    cout << "-->  pVSp   -> (jouer joueur contre joueur)  " << endl;
    cout << "-->  rVSr   -> (jouer ordinateur aléatoire contre ordinateur aléatoire)  " << endl;
    cout << "-->  rVSh   -> (jouer ordinateur aléatoire contre ordinateur heuristique)  " << endl;
    cout << "-->  hVSh   -> (jouer ordinateur heuristique contre ordinateur heuristique)  " << endl;
  }
  return 0;
}

void playerVSplayer(){
  cout<<"Lancement de la commande Engine."<<endl;
  Engine engine;
  Engine* ptr_engine = &engine;
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  RenderLayer stateLayer(engine.getState(), window);
  RenderLayer* ptr_stateLayer = &stateLayer;

  stateLayer.registerObserver(ptr_engine);
  engine.getState().registerObserver(ptr_stateLayer);
  stateLayer.draw(window);
  srand (time(NULL));

  int newX = 1;
  int newY = 1;
  int mouseX;
  int mouseY;
  int mouseGridX;
  int mouseGridY;
  Coord mouseCoord;
  Coord targetCoord;
  Coord& refTargetCoord = targetCoord;
  bool animalSelected = false;
  Animal* selectedAnimal;

  StateEvent animalChangedEvent(ANIMALS_CHANGED);
  StateEvent& refAnimalChangedEvent = animalChangedEvent;
  StateEvent highlightsChangedEvent(HIGHLIGHTS_CHANGED);
  StateEvent& refHighlightsChangedEvent = highlightsChangedEvent;
  StateEvent infosChangedEvent(INFOS_CHANGED);
  StateEvent& refInfosChangedEvent = infosChangedEvent;
  engine.getState().notifyObservers(refAnimalChangedEvent, engine.getState());
  engine.getState().notifyObservers(refHighlightsChangedEvent, engine.getState());
  engine.getState().notifyObservers(refInfosChangedEvent, engine.getState());

  while (window.isOpen()){
    Event event;
    mouseX = Mouse::getPosition(window).x;
    mouseY = Mouse::getPosition(window).y;
    mouseGridX = (mouseX-73*3)/73; //73*3 to change by gridOrigine.getX() when in the render
    mouseGridY = mouseY/73;
    mouseCoord.setX(mouseGridX);
    mouseCoord.setY(mouseGridY);

    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        window.close();
      }

      else if(event.type == Event::MouseButtonPressed) {
        cout << endl << "         * Clic *" << endl;

        if (animalSelected == false && engine.getState().getGameover() != true) {
          cout << "Selection :" << endl;
          cout << "Mouse clic pixel event : " << mouseX << " , "<< mouseY << endl;
          cout << "Mouse clic grid event : (" << mouseGridX << " , "<< mouseGridY << ")" << endl;
          pair<Animal*, int> selection = engine.getState().getSelection(mouseCoord);
          selectedAnimal = selection.first;
          if (selection.first != 0 && engine.getState().getTurn()%2 == selection.second){
            Select select1(selectedAnimal, mouseCoord);
            select1.execute(ptr_engine);
            StateEvent highlightsChangedEvent(HIGHLIGHTS_CHANGED);
            StateEvent& refHighlightsChangedEvent = highlightsChangedEvent;
            engine.getState().notifyObservers(refHighlightsChangedEvent, engine.getState());
            animalSelected = true;
          }

        } else if ((animalSelected == true)) {
          cout << "-- Beginning of the move --" << endl;
          cout << "Animal selected id: " << selectedAnimal->getID() << endl;
          newX = mouseGridX;
          newY = mouseGridY;
          targetCoord.setX(newX);
          targetCoord.setY(newY);
          Move move1(selectedAnimal, refTargetCoord);
          move1.execute(ptr_engine);
          engine.getState().notifyObservers(refAnimalChangedEvent, engine.getState());
          engine.getState().notifyObservers(refHighlightsChangedEvent, engine.getState());
          engine.getState().notifyObservers(refInfosChangedEvent, engine.getState());
          animalSelected = false;
          cout << "-- End of the move --" << endl;
        }
      }
    }
  }
}

void randomVSrandom(){
  cout<<"Lancement de la commande randomVSrandom."<<endl;
  Engine engine;
  Engine* ptr_engine = &engine;
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  RenderLayer stateLayer(engine.getState(), window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  RandomAI randomAI0(0);
  RandomAI randomAI1(1);

  stateLayer.registerObserver(ptr_engine);
  engine.getState().registerObserver(ptr_stateLayer);
  stateLayer.draw(window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        window.close();
      }
    }
    if(engine.getState().getGameover() != true){
      if(engine.getState().getTurn()%2 == 0) {
        cout << endl << "         * IA0 is playing*" << endl;
        randomAI0.play(ptr_engine);
      } else {
        cout << endl << "         * IA1 is playing*" << endl;
        randomAI1.play(ptr_engine);
      }
    }
  }
}

void randomVSheuristic(){
  cout<<"Lancement de la commande randomVSheuristic."<<endl;
  Engine engine;
  Engine* ptr_engine = &engine;
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  RenderLayer stateLayer(engine.getState(), window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  RandomAI randomAI(1);
  HeuristicAI heuristicAI(0);

  stateLayer.registerObserver(ptr_engine);
  engine.getState().registerObserver(ptr_stateLayer);
  stateLayer.draw(window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        window.close();
      }
    }
    if(engine.getState().getGameover() != true){
      if(engine.getState().getTurn()%2 == 0) {
        cout << endl << "         * IA random is playing*" << endl;
        randomAI.play(ptr_engine);
      } else {
        cout << endl << "         * IA heuristic is playing*" << endl;
        heuristicAI.play(ptr_engine);
      }
   }
  }
}

void heuristicVSheuristic(){
  cout<<"Lancement de la commande randomVSheuristic."<<endl;
  Engine engine;
  Engine* ptr_engine = &engine;
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  RenderLayer stateLayer(engine.getState(), window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  HeuristicAI heuristicAI0(0);
  HeuristicAI heuristicAI1(1);

  stateLayer.registerObserver(ptr_engine);
  engine.getState().registerObserver(ptr_stateLayer);
  stateLayer.draw(window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        window.close();
      }
    }
    if(engine.getState().getGameover() != true){
      if(engine.getState().getTurn()%2 == 0) {
        cout << endl << "         * IA heuristicAI0 is playing*" << endl;
        heuristicAI0.play(ptr_engine);
      } else {
        cout << endl << "         * IA heuristiAI1 is playing*" << endl;
        heuristicAI1.play(ptr_engine);
      }
    }
  }
}
