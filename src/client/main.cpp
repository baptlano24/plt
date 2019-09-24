#include <iostream>
#include <string> //pour utiliser string::compare

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    Exemple exemple;
    exemple.setX(53);

    if (argc>=2 && (std::string(argv[1]) == "hello")) {
      cout << "Merci de dire "<< argv[1] << " !"<< endl;
    } else {
      cout << "Dis plutôt hello."<< endl;
    }

    return 0;
}
