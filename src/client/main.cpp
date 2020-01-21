#include <iostream>
#include <fstream>
#include <string> //pour utiliser string::compare
#include <utility>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <state.h>
#include "state.h"
#include "render.h"
#include <engine.h>
#include "engine.h"
#include "ai.h"
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <microhttpd.h>
using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;
using namespace ai;

void playerVSplayer();
void randomVSrandom();
void randomVSnovice();
void randomVSheuristic();
void noviceVSplayer();
void heuristicVSnovice();
void heuristicVSheuristic();
void heuristicVSplayer();
void replayRecord();
void deepVSplayer(int depth_in);
void deepVSdeep(int depth_inJ1, int depth_inJ2);
void heuristicVSdeep(int depth_inJ);
void saveEngineRecord(Engine* engine);
void network();


int delai = 50000; //temps de jeu minimum des IA en micro seconde

int main(int argc,char* argv[1]) {
  if(argc>=2 && string(argv[1])=="hello") {
    cout << "Hello world !" << endl;
  } else if (argc>=2 && string(argv[1])=="pVSp") {
    playerVSplayer();
  } else if (argc>=2 && string(argv[1])=="rVSr") {
    randomVSrandom();
  } else if (argc>=2 && string(argv[1])=="rVSn") {
    randomVSnovice();
  } else if (argc>=2 && string(argv[1])=="rVSh") {
    randomVSheuristic();
  } else if (argc>=2 && string(argv[1])=="nVSp") {
    noviceVSplayer();
  } else if (argc>=2 && string(argv[1])=="hVSn") {
    heuristicVSnovice();
  } else if (argc>=2 && string(argv[1])=="hVSh") {
    heuristicVSheuristic();
  } else if (argc>=2 && string(argv[1])=="replay") {
    replayRecord();
  }else if(argc>=2 && string(argv[1]) == "network"){
    network();
  }else if (argc>=2 && string(argv[1])=="hVSp") {
    heuristicVSplayer();
  } else if (argc>=2 && (string(argv[1])=="dVSp" || string(argv[1])=="dVSd" || string(argv[1])=="hVSd")) {
            int depth_in;
            try {
                depth_in = stoi(argv[2]);
            }
            catch(const std::logic_error){
              cout << "   -> Vous avez oublié le dernier argument qui précise la difficulté de l'ordinateur (la profondeur du MinMax).\nElle doit être précisée après l'appel de " << argv[1] << endl;
            }
            if(depth_in>=1 && depth_in<=5){
                if(string(argv[1])=="dVSp")
                  deepVSplayer(depth_in);
                else if (string(argv[1])=="dVSd")
                  deepVSdeep(depth_in, depth_in);
                else if (string(argv[1])=="hVSd")
                  heuristicVSdeep(depth_in);
            } else {
              cout << "   La profondeur doit être entre 1 et 4. Veuillez recommencer." << endl;
            }
  } else {
    cout << "Veuillez dire une commande parmis les suivantes :" << endl;
    cout << "-->  hello  : phrase d'accueil" << endl;
    cout << "-->  pVSp   : jouer joueur contre joueur" << endl;
    cout << "-->  rVSr   : jouer ordinateur aléatoire contre ordinateur aléatoire" << endl;
    cout << "-->  rVSn   : jouer ordinateur aléatoire contre ordinateur novice" << endl;
    cout << "-->  rVSh   : jouer ordinateur aléatoire contre ordinateur heuristique" << endl;
    cout << "-->  nVSp   : jouer ordinateur novice contre joueur" << endl;
    cout << "-->  hVSn   : jouer ordinateur heuristique contre ordinateur novice" << endl;
    cout << "-->  hVSh   : jouer ordinateur heuristique contre ordinateur heuristique" << endl;
    cout << "-->  hVSp   : jouer ordinateur heuristique contre joueur" << endl;
    cout << "-->  dVSp N : jouer ordinateur avancé (MinMax) profondeur N (à remplacer avec entier entre 1 et 5) contre joueur" << endl;
    cout << "-->  dVSd N : jouer ordinateur avancé (MinMax) profondeur N (à remplacer avec entier entre 1 et 5) contre ordinateur avancé" << endl;
    cout << "-->  hVSd N : jouer ordinateur avancé (MinMax) profondeur N (à remplacer avec entier entre 1 et 5) contre ordinateur heuristique" << endl;
    cout << "-->  replay : rejoue la séquence de jeu enregistrée précédement dans un fichier texte (./server record pour enregistrer une partie)" << endl;
  }
  return 0;
}

void playerVSplayer(){
  cout<<"Lancement de la commande Engine."<<endl;
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
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

  while (window.isOpen()){
    Event event;
    mouseX = Mouse::getPosition(window).x;
    mouseY = Mouse::getPosition(window).y;
    mouseGridX = (mouseX-73*3)/73; //73*3 to change by gridOrigine.getX() when in the render
    mouseGridY = mouseY/73;
    mouseCoord.setX(mouseGridX);
    mouseCoord.setY(mouseGridY);

    while (window.pollEvent(event)){
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
          engine.undo();
      if (event.type == Event::Closed){
        state.setGameover(true);
        window.close();
      }

      else if(event.type == Event::MouseButtonPressed) {
        cout << endl << "         * Clic *" << endl;

        if (animalSelected == false && state.getGameover() != true) {
          cout << "Selection :" << endl;
          cout << "Mouse clic pixel event : " << mouseX << " , "<< mouseY << endl;
          cout << "Mouse clic grid event : (" << mouseGridX << " , "<< mouseGridY << ")" << endl;
          pair<Animal*, int> selection = state.getSelection(mouseCoord);
          selectedAnimal = selection.first;
          if (selection.first != 0 && state.getPlaying() == selection.second){
            Select select1(selectedAnimal, mouseCoord, state.getPlaying());
            animalSelected = true;
          }

        } else if (animalSelected == true) {
          cout << "-- Beginning of the player move --" << endl;
          cout << "Animal selected id: " << selectedAnimal->getID() << endl;
          newX = mouseGridX;
          newY = mouseGridY;
          targetCoord.setX(newX);
          targetCoord.setY(newY);
          Move move1(selectedAnimal, refTargetCoord, state.getPlaying());
          ptr_stateLayer->notifyObservers(move1);
          animalSelected = false;
          cout << "-- End of the move --" << endl;
        }
      }
      if(state.getGameover() == true) {
        saveEngineRecord(ptr_engine);
        break;
      }
    }
  }
}

void randomVSrandom(){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  RandomAI randomAI0(0);
  RandomAI randomAI1(1);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        state.setGameover(true);
        window.close();
      }
    }
    if(state.getGameover() != true){
      if(state.getPlaying() == 0) {
        cout << endl << "         * IA0 random is playing *" << endl;
        usleep(delai);
        randomAI0.play(ptr_engine);
      } else {
        cout << endl << "         * IA1 random is playing *" << endl;
        usleep(delai);
        randomAI1.play(ptr_engine);
      }
    }
    if(state.getGameover() == true) {
      saveEngineRecord(ptr_engine);
      break;
    }
  }
}

void randomVSnovice(){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  RandomAI randomAI(1);
  NoviceAI noviceAI(0);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        state.setGameover(true);
        window.close();
      }
    }
    if(state.getGameover() != true){
      if(state.getPlaying() == 0) {
        cout << endl << "         * IA random is playing *" << endl;
        usleep(delai);
        randomAI.play(ptr_engine);
      } else {
        cout << endl << "         * IA novice is playing *" << endl;
        usleep(delai);
        noviceAI.play(ptr_engine);
      }
   }
   if(state.getGameover() == true) {
     saveEngineRecord(ptr_engine);
     break;
   }
  }
}

void noviceVSplayer(){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  NoviceAI noviceAI0(0);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
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

  while (window.isOpen()){
    Event event;
    mouseX = Mouse::getPosition(window).x;
    mouseY = Mouse::getPosition(window).y;
    mouseGridX = (mouseX-73*3)/73; //73*3 to change by gridOrigine.getX() when in the render
    mouseGridY = mouseY/73;
    mouseCoord.setX(mouseGridX);
    mouseCoord.setY(mouseGridY);

    while (window.pollEvent(event)){
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
          engine.undo();
      if (event.type == Event::Closed){
        state.setGameover(true);
        window.close();
      } else if(event.type == Event::MouseButtonPressed) {
        cout << endl << "         * Clic *" << endl;

        if (animalSelected == false && state.getGameover() != true && state.getPlaying() == 1) {
          cout << "Selection :" << endl;
          cout << "Mouse clic pixel event : " << mouseX << " , "<< mouseY << endl;
          cout << "Mouse clic grid event : (" << mouseGridX << " , "<< mouseGridY << ")" << endl;
          pair<Animal*, int> selection = state.getSelection(mouseCoord);
          selectedAnimal = selection.first;
          if (selection.first != 0 && state.getPlaying() == selection.second){
            Select select1(selectedAnimal, mouseCoord, state.getPlaying());
            animalSelected = true;
          }

        } else if (animalSelected == true) {
          cout << "-- Beginning of the player move --" << endl;
          cout << "Animal selected id: " << selectedAnimal->getID() << endl;
          newX = mouseGridX;
          newY = mouseGridY;
          targetCoord.setX(newX);
          targetCoord.setY(newY);
          Move move1(selectedAnimal, refTargetCoord, state.getPlaying());
          ptr_stateLayer->notifyObservers(move1);
          animalSelected = false;
          cout << "-- End of the move --" << endl;
        }
      }
    }
    if(state.getGameover() != true && state.getPlaying() == 0){
      cout << endl << "         * IA noviceAI0 is playing *" << endl;
      cout<<"Tour numéro : " << state.getTurn() << endl;
      usleep(delai);
      noviceAI0.play(ptr_engine);
    }
    if(state.getGameover() == true) {
      saveEngineRecord(ptr_engine);
      break;
    }
  }
}

void heuristicVSnovice(){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  HeuristicAI heuristicAI(0);
  NoviceAI noviceAI(1);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        state.setGameover(true);
        window.close();
      }
    }
    if(state.getGameover() != true){
      if(state.getPlaying() == 0) {
        cout << endl << "         * IA HeuristicAI is playing *" << endl;
        cout<<"Tour numéro : " << state.getTurn() << endl;
        usleep(delai);
        heuristicAI.play(ptr_engine);
      } else {
        cout << endl << "         * IA NoviceAI is playing *" << endl;
        cout<<"Tour numéro : " << state.getTurn() << endl;
        usleep(delai);
        noviceAI.play(ptr_engine);
      }
    }
    if(state.getGameover() == true) {
      saveEngineRecord(ptr_engine);
      break;
    }
  }
}

void randomVSheuristic(){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  HeuristicAI heuristicAI(0);
  RandomAI randomAI(1);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        state.setGameover(true);
        window.close();
      }
    }
    if(state.getGameover() != true){
      if(state.getPlaying() == 0) {
        cout << endl << "         * IA HeuristicAI is playing *" << endl;
        cout<<"Tour numéro : " << state.getTurn() << endl;
        usleep(delai);
        heuristicAI.play(ptr_engine);
      } else {
        cout << endl << "         * IA RandomAI is playing *" << endl;
        cout<<"Tour numéro : " << state.getTurn() << endl;
        usleep(delai);
        randomAI.play(ptr_engine);
      }
    }
    if(state.getGameover() == true) {
      saveEngineRecord(ptr_engine);
      break;
    }
  }
}

void heuristicVSheuristic(){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  HeuristicAI heuristicAI0(0);
  HeuristicAI heuristicAI1(1);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        state.setGameover(true);
        window.close();
      }
    }
    if(state.getGameover() != true){
      if(state.getPlaying() == 0) {
        cout << endl << "         * IA HeuristicAI0 is playing *" << endl;
        cout<<"Tour numéro : " << state.getTurn() << endl;
        usleep(delai);
        heuristicAI0.play(ptr_engine);
      } else {
        cout << endl << "         * IA HeuristicAI1 is playing *" << endl;
        cout<<"Tour numéro : " << state.getTurn() << endl;
        usleep(delai);
        heuristicAI1.play(ptr_engine);
      }
    }
    if(state.getGameover() == true) {
      saveEngineRecord(ptr_engine);
      break;
    }
  }
}

void heuristicVSplayer(){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  HeuristicAI heuristicAI1(1);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
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
        state.setGameover(true);
        window.close();
      } else if(event.type == Event::MouseButtonPressed) {
        cout << endl << "         * Clic *" << endl;
        if (animalSelected == false && state.getGameover() != true && state.getPlaying() == 0) {
          cout << " Mouse clic pixel event : " << mouseX << " , "<< mouseY << endl;
          cout << " Mouse clic grid event : (" << mouseGridX << " , "<< mouseGridY << ")" << endl;
          pair<Animal*, int> selection = state.getSelection(mouseCoord);
          selectedAnimal = selection.first;
          if (selection.first != 0 && state.getPlaying() == selection.second){
            Select select1(selectedAnimal, mouseCoord, state.getPlaying());
            animalSelected = true;
          }

        } else if (animalSelected == true) {
          cout << endl << "-- Beginning of player the move --" << endl;
          newX = mouseGridX;
          newY = mouseGridY;
          targetCoord.setX(newX);
          targetCoord.setY(newY);
          Move move1(selectedAnimal, refTargetCoord, state.getPlaying());
          ptr_stateLayer->notifyObservers(move1);
          animalSelected = false;
          cout << "-- End of the move --" << endl;
        }
      }
    }
    if(state.getGameover() != true && state.getPlaying() == 1){
      cout << endl << "         * IA HeuristicAI1 is playing *" << endl;
      cout<<"Tour numéro : " << state.getTurn() << endl;
      usleep(delai);
      Move moveIA = heuristicAI1.play(ptr_engine);
      ptr_stateLayer->notifyObservers(moveIA);
      cout << "         * IA HeuristicAI1 turn ends  *" << endl;
    }
    if(state.getGameover() == true) {
      saveEngineRecord(ptr_engine);
      break;
    }
  }
}

void deepVSplayer(int depth_in){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  engine.setEnableRecord(true);

  sf::RenderWindow* ptr_window = new sf::RenderWindow(sf::VideoMode(1314,949), "Jungle War");
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  DeepAI deepAI1(1, ptr_engine, depth_in);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
  srand (time(NULL));

  int newX = 1;
  int newY = 1;
  int mouseX;
  int mouseY;
  int mouseGridX;
  int mouseGridY;
  Coord mouseCoord;
  Coord targetCoord;
  bool animalSelected = false;
  Animal* selectedAnimal;

  while (ptr_window->isOpen()){
    Event event;
    mouseX = Mouse::getPosition(*ptr_window).x;
    mouseY = Mouse::getPosition(*ptr_window).y;
    mouseGridX = (mouseX-73*3)/73; //73*3 to change by gridOrigine.getX() when in the render
    mouseGridY = mouseY/73;
    mouseCoord.setX(mouseGridX);
    mouseCoord.setY(mouseGridY);

    while (ptr_window->pollEvent(event)){
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
          engine.undo();
      if (event.type == Event::Closed){
        state.setGameover(true);
        ptr_window->close();
      } else if(event.type == Event::MouseButtonPressed) {
        cout << endl << "\033[1;36m         * Clic player *\033[0m" << endl;
        if (animalSelected == false && state.getGameover() != true && state.getPlaying() == 0) {
          cout << " Mouse clic pixel event : " << mouseX << " , "<< mouseY << endl;
          cout << " Mouse clic grid event : (" << mouseGridX << " , "<< mouseGridY << ")" << endl;
          pair<Animal*, int> selection = state.getSelection(mouseCoord);
          selectedAnimal = selection.first;
          if (selection.first != 0 && state.getPlaying() == selection.second){
            Select select1(selectedAnimal, mouseCoord, state.getPlaying());
            animalSelected = true;
            cout << "Animal selected" << endl;
          }

        } else if (animalSelected == true) {
          cout << endl << "-- Beginning of player the move --" << endl;
          newX = mouseGridX;
          newY = mouseGridY;
          targetCoord.setX(newX);
          targetCoord.setY(newY);
          Move move1(selectedAnimal, targetCoord, state.getPlaying());
          ptr_stateLayer->notifyObservers(move1);
          animalSelected = false;
          cout << "-- End of the move --" << endl;
        }
      }
    }
    if(state.getGameover() != true && state.getPlaying() == 1){
      if (deepAI1.isReady()){
        cout << endl << "\033[1;36m         * IA deepAI1 is playing *\033[0m" << endl;
        cout<<"Tour numéro : " << state.getTurn() << endl;
        usleep(delai);
        Move moveIA = deepAI1.getNextMove();
        ptr_stateLayer->notifyObservers(moveIA);
        cout << "         * IA deepAI1 turn ends  *\n Move sent to the engine. Waiting for opponent player to play..." << endl;
      } else {
        //Ask to the AI to play, IA says if it is working or start working
        deepAI1.play(ptr_engine);
      }
    }
    if(state.getGameover() == true){
      cout << endl << "    ///--- END OF THE GAME ---///" << endl << endl;
      saveEngineRecord(ptr_engine);
      break;
    }
  }
}

void deepVSdeep(int depth_inJ1, int depth_inJ2){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  engine.setEnableRecord(true);

  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  DeepAI deepAI0(0, ptr_engine, depth_inJ1);
  DeepAI deepAI1(1, ptr_engine, depth_inJ2);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        state.setGameover(true);
        window.close();
      }
    }
    if(state.getGameover() != true){
      if(state.getPlaying() == 0) {
        if (deepAI0.isReady()){
          cout << endl << "\033[1;36m         * IA deepAI0 is playing *\033[0m" << endl;
          cout<<"Tour numéro : " << state.getTurn() << endl;

          Move moveIA = deepAI0.getNextMove();
          ptr_stateLayer->notifyObservers(moveIA);
          cout << "         * IA deepAI0 turn ends  *\n Move sent to the engine. Waiting for opponent player to play..." << endl;
          if (depth_inJ1<=3) {
            usleep(delai);
          }
        } else {
          //Ask to the AI to play, IA says if it is working or start working
          deepAI0.play(ptr_engine);
        }
      } else {
        if (deepAI1.isReady()){
          cout << endl << "\033[1;36m         * IA deepAI1 is playing *\033[0m" << endl;
          cout<<"Tour numéro : " << state.getTurn() << endl;

          Move moveIA = deepAI1.getNextMove();
          ptr_stateLayer->notifyObservers(moveIA);
          cout << "         * IA deepAI1 turn ends  *\n Move sent to the engine. Waiting for opponent player to play..." << endl;
          if (depth_inJ2<=3) {
            usleep(delai);
          }
        } else {
          //Ask to the AI to play, IA says if it is working or start working
          deepAI1.play(ptr_engine);
        }
      }
    }
    if(state.getGameover() == true) {
      cout << endl << "    ///--- END OF THE GAME ---///" << endl << endl;
      saveEngineRecord(ptr_engine);
      break;
    }
  }

}
void heuristicVSdeep(int depth_in){
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  DeepAI deepAI(0, ptr_engine, depth_in);
  HeuristicAI heuristicAI(1);

  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);
  srand (time(NULL));

  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        state.setGameover(true);
        window.close();
      }
    }
    if(state.getGameover() != true){
      if(state.getPlaying() == 0) {
        cout << endl << "         * IA DeepAI is playing *" << endl;
        cout<<"Tour numéro : " << state.getTurn() << endl;
        if(depth_in<=2){
          usleep(delai);
        }
        //std::thread t1(&DeepAI::play, deepAI, ptr_engine);
        //t1.join();
        deepAI.play(ptr_engine);
      } else {
        cout << endl << "         * IA HeuristicAI is playing *" << endl;
        cout<<"Tour numéro : " << state.getTurn() << endl;
        usleep(delai);
        //std::thread t2(&HeuristicAI::play, heuristicAI, ptr_engine);
        //t2.join();
        heuristicAI.play(ptr_engine);
      }
    }
    if(state.getGameover() == true) {
      saveEngineRecord(ptr_engine);
      break;
    }
  }
}

void replayRecord(){
  Json::Value root;
  std::string commandsPath = "../res/replay.txt";
  Engine engine;
  Engine* ptr_engine = &engine;
  State& state = engine.getState();
  State* ptr_state = engine.getptrState();
  sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
  sf::RenderWindow* ptr_window = &window;
  RenderLayer stateLayer(ptr_state, ptr_window);
  RenderLayer* ptr_stateLayer = &stateLayer;
  stateLayer.registerObserver(ptr_engine);
  state.registerObserver(ptr_stateLayer);
  stateLayer.draw(ptr_window);

  while (window.isOpen()){
    std::ifstream commandsFile(commandsPath);
    if (commandsFile){
      Json::Value root;
      Json::Reader reader;
      if (!reader.parse(commandsFile, root)){
          cout << "Failed to parse commands\n"
               << reader.getFormattedErrorMessages();
        break;
      }
      commandsFile.close();
      Coord Coord(0, 0);
      for (unsigned int i = 0; i < root["commands"].size(); i++)
      {
        if (root["commands"][i]["orderID"].asUInt() == engine::MOVE)
        {

            Coord.setX(root["commands"][i]["xDestination"].asUInt());
            Coord.setY(root["commands"][i]["yDestination"].asUInt());
            int id = root["commands"][i]["animalID"].asUInt();
            bool player = root["commands"][i]["player"].asBool();

            engine::Move moveReplay(state.getAnimal(id,player),Coord,player);
            ptr_stateLayer->notifyObservers(moveReplay);
            usleep(delai);

        }
        // Cas de l'attaque
        else if (root["commands"][i]["orderID"].asUInt() == engine::SELECT)
        {
          Coord.setX(root["commands"][i]["xDestination"].asUInt());
          Coord.setY(root["commands"][i]["yDestination"].asUInt());
          int id = root["commands"][i]["animalID"].asUInt();
          bool player = root["commands"][i]["player"].asBool();
          engine::Select selectReplay(state.getAnimal(id,player),Coord,player);
          usleep(delai);
        }
      }
      break;
    }
  }
}

void saveEngineRecord (Engine* engine){
  std::string files_order = "../res/replay.txt";
  std::ofstream files_writte(files_order, ios::out|ios::trunc);
  if(files_writte){
    cout << "--> Debut de l'enregistrement dans le fichier <--" << endl;

    Json::Value root = engine->getRecord();
    cout << root << endl;

    // Ecriture dans le fichier du tableau de commandes de cette partie
    files_writte << root;

    // Fermeture du fichier
    files_writte.close();

    cout << "--> Fin de l'enregistrement dans le fichier <--" << endl;
  }
  else{
    cerr << "Impossible d'ouvrir le fichier des commandes enregistrées pour l'ecriture" << endl;
  }
}

 void network(){
            string name;
            cout << "Enter your name: ";
            cin >> name;
            while (name.length() < 3 || name.length() > 15)
            {
                cout << "Invalid name. At least 3 characters and up to 15. Re-enter: ";
                cin >> name;
            }

            sf::Http http("http://localhost/", 8080);

            sf::Http::Request request1;
            request1.setMethod(sf::Http::Request::Post);
            request1.setUri("/player");
            request1.setHttpVersion(1, 0);
            string body = "{\"name\":\"" + name + "\", \"free\":true}";
            request1.setBody(body);

            sf::Http::Response response1 = http.sendRequest(request1);

            Json::Reader jsonReader;
            Json::Value rep1;
            if (jsonReader.parse(response1.getBody(), rep1))
            {
                int idPlayer = rep1["id"].asInt();

                // query array of players in lobby.
                sf::Http::Request players0;
                players0.setMethod(sf::Http::Request::Get);
                players0.setUri("/player");
                players0.setHttpVersion(1, 0);
                sf::Http::Response playersResp0 = http.sendRequest(players0);
                Json::Reader jsonReaderPlayers0;
                Json::Value jsonPlayers0;
                jsonReaderPlayers0.parse(playersResp0.getBody(), jsonPlayers0);

                cout << "Hello " << name << "! You joined the lobby succesfully!" << endl;
                cout << "Your ID is: " << idPlayer << endl << endl;
                cout << "Players in the lobby: (" << jsonPlayers0["players"].size() << "/2)" << endl;

                for(auto& playerInLobby : jsonPlayers0["players"]){
                    cout << "\t-" << playerInLobby[1].asString() << " [id: " << playerInLobby[0].asString() << "]" << endl;
                }

                cout << "Press q to exit from the lobby" << endl;

                while (getchar() != 'q'){/*endless retry*/}

                sf::Http::Request request3;
                request3.setMethod(sf::Http::Request::Delete);
                string uri2 = "/player/" + to_string(idPlayer);
                request3.setUri(uri2);
                request3.setHttpVersion(1, 0);
                http.sendRequest(request3);
                cout << "Player " << idPlayer << " deleted" << endl;

                // query players in lobby again
                sf::Http::Request players;
                players.setMethod(sf::Http::Request::Get);
                players.setUri("/player");
                players.setHttpVersion(1, 0);
                sf::Http::Response playersResp = http.sendRequest(players);

                Json::Reader jsonReaderPlayers;
                Json::Value jsonPlayers;
                jsonReaderPlayers.parse(playersResp.getBody(), jsonPlayers);

                cout << "Players in the lobby: (" << jsonPlayers["players"].size() << "/2)" << endl;
                for (auto &playerStillInLobby : jsonPlayers["players"])
                {
                    cout << "\t-" << playerStillInLobby[1].asString() << " [id: " << playerStillInLobby[0].asString() << "]" << endl;
                }
            }
            else
            {
                cout << "Out of places: 2/2 players in the lobby." << endl;
            }
        }
      
