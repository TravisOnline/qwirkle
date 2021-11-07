#ifndef PLAYER_H
#define PLAYER_H

#include "Bag.h"
#include "Tile.h"
#include "Board.h"
#include <string>

class Player
{
public:
    Player();
    Player(std::string playerName, LinkedList *newHand);
    Player(std::string playerName, int score, LinkedList* savedHand);
    ~Player();

    //get methods
    std::string getPlayerName();
    LinkedList* getPlayerHand();
    int getPlayerScore();

    //set methods
    void setPlayerName(std::string name);
    void setPlayerScore(int score);

    int searchHand(std::string toFind);  // find a tile in hand at certain index
    Tile* pop_at(int index);   // delete a tile in hand at certain index
    void push_at(int index, Tile *data);  // add a tile to hand at certain index
    void push_back(Tile *data);

    void drawTile(Bag* bag);
    void drawFromString(std::string handString);

    int getHandSize();
    std::string printHand();

private:
    int score;
    std::string playerName;
    LinkedList* hand;
};

#endif // PLAYER_H