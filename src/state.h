
namespace state {

  enum AnimalID {
    RAT,
    CAT,
    WOLF,
    DOG,
    LEOPARD,
    TIGER,
    LION,
    ELEPHANT
  };

  enum AnimalStatus {
    NORMAL,
    SWIMMING,
    TRAPED,
    DEAD,
    VICTORIOUS
  };

  /// class Animal - 
  class Animal {
    // Attributes
  private:
    AnimalID id;
    int x;
    int y;
    AnimalStatus status;
    // Operations
  public:
    Animal (AnimalID id);
    AnimalStatus getStatus ();
    void setStatus (AnimalStatus status);
  };

  /// class Player - 
  class Player {
    // Attributes
  private:
    char name;
    int color;
    std::unordered_map<AnimalID, Animal> animals;
    bool playing;
    // Operations
  public:
    Player ();
    unordered_map getAnimals ();
    Animal getAnimal (AnimalID id);
  };

  /// class Square - 
  class Square {
    // Attributes
  private:
    bool empty;
    // Operations
  public:
    Square ();
    bool isEmpty ();
  };

  /// class State - 
  class State {
    // Associations
    state::Square* unnamed;
    state::Player* unnamed;
    // Attributes
  private:
    std::array<std::array<Square,13>,12> grid;
    Player player1;
    Player player2;
    // Operations
  public:
    MapArray getGrid ();
    Player getPlayer1 ();
    Player getPlayer2 ();
  };

  enum SquareID {
    EARTH,
    SHORE,
    WATER,
    TRAPJ1,
    TRAPJ2,
    THRONEJ1,
    THRONEJ2
  };

};

