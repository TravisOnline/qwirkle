
#ifndef GAME_H
#define GAME_H

#include "Node.h"
#include "LinkedList.h"
#include "Bag.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>

#define MAX_HAND_SIZE 6
#define SMALL_PLACE_COMMAND 14
#define LARGE_PLACE_COMMAND 15
#define REPLACE_COMMAND 10
#define QUIT_COMMAND 4
#define DEFAULT_PLAYER_COUNT 2
#define ENHANCEMENT_COUNT 3
#define PLAYER_SAVE_LINES 3

class Game{
  
  public:
    Game();
    Game(bool helpCommand, bool betterInvalidInput, bool morePlayers, int playerCount);
    ~Game();

    bool checkPlayerName(std::string playerName);
    void printState(Player *player);
    void printScore(int playerCount);
    void printHelp(Player *player, bool helpCommand, bool betterInvalidInput, bool morePlayers);
    
    void getMoveFromPlayer(Player *player, bool helpCommand, bool betterInvalidInput, bool morePlayers);
    bool validateInput(std::string choice, bool helpCommand, bool betterInvalidInput);
    int checkSpaces(std::string choice);

    void placeTile(std::string input, Player* player, bool betterInvalidInput);
    void replaceTile(std::string input, Player* player, bool betterInvalidInput);
    Player* switchTurn(Player* curr, std::vector<Player *> players);

    std::string playerNameInput(int playerNumber);

    void newGame(bool helpCommand, bool betterInvalidInput, bool morePlayers, int playerCount);
    void saveGame(std::string input, Player *player, bool helpCommand, bool betterInvalidInput, bool morePlayers);
    void loadGame(std::string fileName);
    void loadDefault(std::string fileName);

    void newLoadGame(){

    }

    void loadMyFormat(std::string fileName);

    std::string getPlayedTiles(Board* board, std::string boardString, int height);
    void constructBag(std::string filename, Bag* bag);
    void constructBoard(Board* board, std::string boardString);

    void gameOver(std::vector<Player *> playerVect);
 
    void playGame(std::vector<Player *> players, bool helpCommand, bool betterInvalidInput, bool morePlayers);

    bool helpCommand = false;
    bool betterInvalidInput = false;
    bool morePlayers = false;
    int playerCount = 0;

  private:
    std::vector<Player *> players;
    //Player* players[MAX_PLAYERS];
    Player* currPlayer = nullptr;
    Bag* bag;
    Board* board;
    bool isNewGame = false;
    bool earlyExit = false;
};

#endif /* GAME_H */
