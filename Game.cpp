#include "Game.h"
#include "Player.h"
#include <regex>
#include <iostream>

Game::Game() {}

Game::Game(bool helpCommand, bool betterInvalidInput, bool morePlayers, int playerCount){
    helpCommand = helpCommand;
    betterInvalidInput = betterInvalidInput;
    morePlayers = morePlayers;
    players.resize(0);
}

Game::~Game()
{
    delete bag;
    delete board;
    if(!players.empty()){
        players.clear();
    }
}

bool Game::checkPlayerName(std::string playerName)
{
    bool valid = false;
    std::regex enteredName("[A-Z]{1,20}");
    if (std::regex_match(playerName, enteredName))
    {
        valid = true;
    }
    else
    {
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }
    return valid;
}


//print game state infomation before each turn 
void Game::printState(Player *player)
{
    std::cout << "" << std::endl;
    std::cout << player->getPlayerName() << ", it's your turn" << std::endl;
    printScore(players.size());
    std::cout << board->toString() << std::endl;
    std::cout << "\n Your hand is " << std::endl;
    std::cout << player->printHand() << std::endl;
}


// print score for all players
void Game::printScore(int playerCount)
{
    for (int i = 0; i < playerCount; i++)
    {
        std::cout << "Score for " << players.at(i)->getPlayerName() << ": " <<
        players.at(i)->getPlayerScore() << std::endl;
    }
}

void Game::printHelp(Player *player, bool helpCommand, bool betterInvalidInput, bool morePlayers){
    if(helpCommand == true && (betterInvalidInput == true || betterInvalidInput == false)){
        std::cout << "\033[7;37mQuirkle Commands\033[0m" << std::endl;
        std::cout << "Note: All coordinates and tiles are entered as capital letters." << std::endl;
        std::cout << "Commands are entered in lowercase" << std::endl;
        std::cout << "\033[;33mPlace Tile:\033[0m place -- at --" << std::endl;
        std::cout << "\033[;33mReplace Tile:\033[0m replace --" << std::endl;
        std::cout << "\033[;33mSave Game:\033[0m save [filename_goes_here]" << std::endl;
        std::cout << "\033[;33mQuit:\033[0m quit" << std::endl;

        getMoveFromPlayer(player, helpCommand, betterInvalidInput, morePlayers);
    }else if(helpCommand == false && betterInvalidInput == true){
        std::cout << "\033[;31mInvalid Input\033[0m" << std::endl;
        std::cout << "\033[;33m3.The help command is not activated for this game.\033[0m" << std::endl;
        std::cout << std::endl;
        getMoveFromPlayer(player, helpCommand, betterInvalidInput, morePlayers);
    }else if(helpCommand == false && betterInvalidInput == false){
        std::cout << "Invalid Input" << std::endl;
        getMoveFromPlayer(player, helpCommand, betterInvalidInput, morePlayers);
    }
}


void Game::getMoveFromPlayer(Player *player, bool helpCommand, bool betterInvalidInput, bool morePlayers)
{
    std::string choice = "";
    bool validInput = false;
    std::cout << "" << std::endl;
    
      while (!validInput)
      {
        std::cout << ">";
        
        if(std::cin.eof() == 1){
            std::cout << "Goodbye." << std::endl;
            earlyExit = true;
        }else{
            std::getline(std::cin, choice);
        }
        if(choice.back() == '\r'){choice.pop_back();}
        validInput = validateInput(choice, helpCommand, betterInvalidInput);
        if(earlyExit){validInput = true;}

        if (!validInput)
        {
            if(betterInvalidInput == false){
                std::cout << "Invalid input." << std::endl;
            }else{
                std::cout << "Error, invalid input. Command may be formatted incorrectly." << std::endl;
                std::cout << "If more information is not show above, it may not have fit a" <<std::endl;
                std::cout << "known command format." << std::endl;
            }
        }

        if (validInput)
        {
            if (choice.substr(0, 5).compare("place") == 0)
            {
                placeTile(choice, player, betterInvalidInput);
            }
            else if (choice.substr(0, 7).compare("replace") == 0)
            {
                replaceTile(choice, player, betterInvalidInput);
            }
            else if (choice.substr(0, 4).compare("save") == 0)
            {
                saveGame(choice, player, helpCommand, betterInvalidInput, morePlayers);
                std::cout << "Game saved successfully!" << std::endl;
                getMoveFromPlayer(player, helpCommand, betterInvalidInput, morePlayers);
                 if(std::cin.eof() == 1){
                    std::cout << "Goodbye." << std::endl;
                    earlyExit = true;
                 }else{
                    std::getline(std::cin, choice);
                 }
            }
            else if (choice.substr(0, 4).compare("quit") == 0)
            {
                earlyExit = true;
                std::cout << "Goodbye" << std::endl;
            }else if (choice.substr(0, 4).compare("help") == 0){
                printHelp(player, helpCommand, betterInvalidInput, morePlayers);
            }
        }
    }
}

bool Game::validateInput(std::string choice, bool helpCommand, bool betterInvalidInput)
{
    bool validInput = false;

    if (choice.length() == SMALL_PLACE_COMMAND || choice.length() == LARGE_PLACE_COMMAND)
    {
        //1. check to see if the word place is used and there are correct spaces
        //2. check for 3 spaces in the command
        //3. look for "at" in the string
        if (choice.substr(0, 5).compare("place") == 0 && checkSpaces(choice) == 3 
        && choice.substr(9, 2).compare("at") == 0)
        {
            //place -- at ---
            if (choice.length() == 14 && //If using a position 0-9
                (choice.at(12) >= 'A' && choice.at(12) <= 'Z') &&
                (choice.at(13) >= '0' && choice.at(13) <= '9'))
            {
                validInput = true;
            }
            else if (choice.length() == 15 && //If using a position 10-25
                     (choice.at(12) >= 'A' && choice.at(12) <= 'Z') &&
                     (choice.at(13) >= '1' && choice.at(13) <= '2') &&
                     (choice.at(14) >= '0' && choice.at(14) <= '9'))
            {
                if ((choice.at(13) == '1' &&
                     (choice.at(14) >= '0' && choice.at(14) <= '9')) ||
                    (choice.at(13) == '2' &&
                     (choice.at(14) >= '0' && choice.at(14) <= '5')))
                    validInput = true;
            }else{
                    if(betterInvalidInput == true){
                        std::cout << "\033[;31mInvalid Input\033[0m" << std::endl;
                        std::cout << "\033[;31mThe coordinate you listed is out of range.\033[0m" << std::endl;
                        std::cout << "\033[;31mCoordinates must be between A0 and Z25.\033[0m" << std::endl;
                        std::cout << std::endl;
                    }
            }
        }
    }
    else if (choice.length() == REPLACE_COMMAND)
    {
        if (choice.substr(0, 7).compare("replace") == 0 && checkSpaces(choice) == 1)
        {
            validInput = true;
        }
    }
    else if (choice.substr(0, 4).compare("save") == 0 && checkSpaces(choice) == 1)
    {
            validInput = true;
    }
    else if (choice.length() == QUIT_COMMAND)
    {
        if (choice.substr(0, 4).compare("quit") == 0 && checkSpaces(choice) == 0)
        {
            validInput = true;
        }
        else if(choice.substr(0, 4).compare("help") == 0 && checkSpaces(choice) == 0)
        {
            validInput = true;
        }
    }
    return validInput;
}


//string is passed from validateInput  to here to look for spaces in commands
int Game::checkSpaces(std::string choice)
{
    int spaces = 0;

    for (unsigned int i = 0; i < choice.length(); ++i)
    {
        if (choice[i] == 32)
        {
            spaces++;
        }
    }
    return spaces;
}


void Game::placeTile(std::string input, Player *player, bool betterInvalidInput)
{   
    std::string boardPos = input.substr(12, (input.length() - 12));
    char row = boardPos[0];
    int col = stoi(boardPos.substr(1, boardPos.length() - 1));

    // search requested tile from player's hand and return the index of the tile
    int index = player->searchHand(input.substr(6, 2));
    if (index != -1)
    {   // delete the tile from hand
        Tile *tile = player->pop_at(index);
        // when the tile is in hand and board postion is valid
        if (index > -1 && board->validation(row, col, tile))
        {
            if (board->isEmpty())
            {
                //board->setTile('M', 13, tile); //Forces the first tile to be at 'M13' if board is empty
                board->setTile(row, col, tile);
                player->setPlayerScore(1);
                player->drawTile(bag);
            }
            else
            {
                board->setTile(row, col, tile);
                player->setPlayerScore(board->calTotalScore(row, col));
                player->drawTile(bag);
            }
        }
        else 
        {   // push the tile back to original index in player's hand 
            // print invalid input message and get player input to try again
            if(betterInvalidInput == true){
            std::cout << "\033[;31mInvalid Input\033[0m" << std::endl;
            std::cout << "\033[;31m1. Tiles MUST share a colour or shape with a neighbor.\033[0m" << std::endl;
            std::cout << "\033[;31m2. After placement of the first tile, all subsequent tiles must have a neighbor\033[0m" << std::endl;
            std::cout << "\033[;33m3. Please remember that identical tiles cannot be placed in the same line\033[0m" << std::endl;
            }else{
                std::cout << "Invalid input" << std::endl;
            }
            player->push_at(index, tile);
            getMoveFromPlayer(player, helpCommand, betterInvalidInput, morePlayers);
        }
    }
    else
    {
        std::cout << "\033[;31mInvalid Input\033[0m" << std::endl;
        if(betterInvalidInput){
            std::cout << "\033[;31mSelected tile is not in your hand\033[0m" << std::endl;
        }
        getMoveFromPlayer(player, helpCommand, betterInvalidInput, morePlayers);
    }
}


void Game::replaceTile(std::string input, Player *player, bool betterInvalidInput)
{
    int index = player->searchHand(input.substr(8, 2));
    if (index > -1 && bag->getSize() > 0)
    {
        bag->push_back(player->pop_at(index)); 
        player->drawTile(bag);
    }
    else
    {
        if(betterInvalidInput){
            std::cout << "\033[;31mInvalid Input\033[0m" << std::endl;
            std::cout << "\033[;31mTile not found for replacement.\033[0m" << std::endl;
        }else{
            std::cout << "Invalid Input";
        }
        getMoveFromPlayer(player, helpCommand, betterInvalidInput, morePlayers);
    }
}

Player* Game::switchTurn(Player * curr, std::vector<Player *> players){
    if(players.size() == 2){
        if (curr == players[0])
        {
            curr = players[1];
        }
        else
        {
            curr = players[0];
        }
    }else if(players.size() == 3){
        if (curr == players[0])
        {
            curr = players[1];
        }
        else if(curr == players[1])
        {
            curr = players[2];
        }
        else{
            curr = players[0];
        }
    }else{
        if (curr == players[0])
        {
            curr = players[1];
        }
        else if(curr == players[1])
        {
            curr = players[2];
        }
        else if(curr == players[2]){
            curr = players[3];
        }else{
            curr = players[0];
        }
    }
    return curr;
}

std::string Game::playerNameInput(int playerNumber)
{
    bool prompt = true;
    std::string playerName = "";
    do
    {
        if (prompt)
        {
            std::cout << "Please enter name for player " << playerNumber << " (Uppercase only)" << std::endl;
            std::cout << "> ";
            if(std::cin.eof() == 1){
                std::cout << "Goodbye." << std::endl;

                // exit(0);
            }else{
                std::cin >> playerName;
            }
            prompt = false;
        }
        if (!checkPlayerName(playerName))
        {
            std::cout << "Uppercase only and with 20 characters." << std::endl;
            std::cout << "> ";
             if(std::cin.eof() == 1){
                std::cout << "Goodbye." << std::endl;
                earlyExit = true;
                // exit(0);
            }else{
                std::cin >> playerName;
            }
        }
    } while (!checkPlayerName(playerName) && !earlyExit);
    return playerName;
}

void Game::newGame(bool helpCommand, bool betterInvalidInput, bool morePlayers, int playerCount)
{
    isNewGame = true;

    std::string player1Name = playerNameInput(1);;

    Player* player1 = new Player(player1Name, new LinkedList());
    players.push_back(player1);
    if(!earlyExit)
    {
        std::string player2Name = playerNameInput(2);
        Player* player2 = new Player(player2Name, new LinkedList());
        players.push_back(player2);
        if(morePlayers == true){
            std::string player3Name = playerNameInput(3);
            Player* player3 = new Player(player3Name, new LinkedList());
            players.push_back(player3);
            if(playerCount == 4){
                std::string player4Name = playerNameInput(4);
                Player* player4 = new Player(player4Name, new LinkedList());
                players.push_back(player4);
            }  
        }
    }

    bag = new Bag();
    bag->shuffleBag();
    //initialise a board
    board = new Board();

    std::cin.clear();
    std::cin.ignore(265, '\n');

   playGame(players, helpCommand, betterInvalidInput, morePlayers);       
}

// save game to a file 
void Game::saveGame(std::string input, Player *player, bool helpCommand, bool betterInvalidInput, bool morePlayers)
{
    std::string fileName = input.substr(5, input.length()-5);
    fileName = fileName +".save";
    std::ofstream outputFile;
    outputFile.open(fileName);

    if(helpCommand == true || betterInvalidInput == true || morePlayers == true){
        outputFile << "#myformat" << std::endl;
        outputFile << players.size() <<std::endl;
    }else{
        outputFile << "#default" << std::endl;
    }

    for (unsigned int i = 0; i < players.size(); ++i)
    {
        outputFile << players[i]->getPlayerName() << std::endl;
        outputFile << players[i]->getPlayerScore() << std::endl;
        outputFile << players[i]->printHand() << std::endl;
    }
    //save the board
    outputFile << board->getRowSize() << "," << board->getColumnSize() << std::endl;
    std::string boardToString = board->toString();

    //Save tiles on the board
    std::string playedtiles = getPlayedTiles(board, boardToString, board->getRowSize());
    outputFile << playedtiles << std::endl;

    //Save the current bag
    outputFile << bag->printBag() << std::endl;

    //save player name for current turn
    outputFile << player->getPlayerName() << std::endl;

    outputFile << helpCommand << std::endl;
    outputFile << betterInvalidInput << std::endl;
    outputFile << morePlayers;

    outputFile.close();
}

/*Loading now passes to this if statement
 *If in default format, call default
 *loader, otherwise load my format
 */
void Game::loadGame(std::string fileName){
    std::ifstream inFile;
    inFile.open(fileName);

    std::string fileFormat;
    std::getline(inFile, fileFormat);
    inFile.close();
    if(fileFormat == "#default"){
        loadDefault(fileName);
    }else{
        loadMyFormat(fileName);       
    } 
}

void Game::loadDefault(std::string fileName){
    std::ifstream inFile;
    inFile.open(fileName);
    
    std::string format;
    std::getline(inFile, format);

    std::string player1Name;
    std::getline(inFile, player1Name);
    if(player1Name.back() == '\r'){player1Name.pop_back();}

    std::string player1ScoreString;
    std::getline(inFile, player1ScoreString);
    int player1Score = stoi(player1ScoreString);

    std::string player1Hand;
    std::getline(inFile, player1Hand);
    LinkedList* player1HandList = new LinkedList();

    std::string player2Name;
    std::getline(inFile, player2Name);
    if(player2Name.back() == '\r'){player2Name.pop_back();}

    std::string player2ScoreString;
    std::getline(inFile, player2ScoreString);
    int player2Score = stoi(player2ScoreString);

    std::string player2Hand;
    std::getline(inFile, player2Hand);
    LinkedList* player2HandList = new LinkedList(); 
        
    for(int i =0; i <player1HandList->size(); ++i){
        std::cout << player1HandList->get(i)->getTileColour() << player1HandList->get(i)->getTileShape() << std::endl;
    }

    for(int i =0; i <player2HandList->size(); ++i){
        std::cout << player2HandList->get(i)->getTileColour() << player2HandList->get(i)->getTileShape() << std::endl;
    }
        
    Player* player1 = new Player(player1Name, player1Score, player1HandList);
    players.push_back(player1);
    player1->drawFromString(player1Hand);

    Player* player2 = new Player(player2Name, player2Score, player2HandList);
    players.push_back(player2);
    player2->drawFromString(player2Hand);

    std::string boardString;
    std::getline(inFile, boardString);

    int height = 0;
    int width = 0;
    std::string heightString = "";
    std::string widthString = "";

    if(boardString.length() == 3){
        std::string heightString = boardString.substr(0,1);
        std::string widthString = boardString.substr(2,1);
        height = std::stoi(heightString);
        width = std::stoi(widthString);
    }else{
        std::string heightString = boardString.substr(0,2);
        std::string widthString = boardString.substr(3,2);
        height = std::stoi(heightString);
        width = std::stoi(widthString);
    }     
    board = new Board(width, height);

    //Load placed tiles and put them on the board
    std::string playedTilesString;
    std::getline(inFile, playedTilesString);
    constructBoard(board, playedTilesString);

    //Load bag
    std::string bagString;
    std::getline(inFile, bagString);

    bag = new Bag(bagString);

    std::string currentTurn;
    std::getline(inFile, currentTurn);

    if(currentTurn.compare(players[0]->getPlayerName()) == 0){
        currPlayer = players[0];
    }else if(currentTurn.compare(players[1]->getPlayerName()) == 0){
        currPlayer = players[1];
    }else{
        std::cout << "no player found" << std::endl;
    }

    inFile.close();
    isNewGame = false;
    playGame(players, false, false, false);
}

void Game::loadMyFormat(std::string fileName){
    std::ifstream inFile;
    inFile.open(fileName);

    std::string format;
    std::getline(inFile, format);

    int savedPlayerCount = 0;
    std::string savedPlayerCountString;
    std::getline(inFile, savedPlayerCountString);
    savedPlayerCount = stoi(savedPlayerCountString);

    std::string player1Name;
    std::getline(inFile, player1Name);
    if(player1Name.back() == '\r'){player1Name.pop_back();}

    std::string player1ScoreString;
    std::getline(inFile, player1ScoreString);
    int player1Score = stoi(player1ScoreString);

    std::string player1Hand;
    std::getline(inFile, player1Hand);
    LinkedList* player1HandList = new LinkedList();

    std::string player2Name;
    std::getline(inFile, player2Name);
    if(player2Name.back() == '\r'){player2Name.pop_back();}

    std::string player2ScoreString;
    std::getline(inFile, player2ScoreString);
    int player2Score = stoi(player2ScoreString);

    std::string player2Hand;
    std::getline(inFile, player2Hand);
    LinkedList* player2HandList = new LinkedList();

    Player* player1 = new Player(player1Name, player1Score, player1HandList);
    players.push_back(player1);
    player1->drawFromString(player1Hand);

    Player* player2 = new Player(player2Name, player2Score, player2HandList);
    players.push_back(player2);
    player2->drawFromString(player2Hand);

    if(savedPlayerCount >= 3){
        std::string player3Name;
        std::getline(inFile, player3Name);
        if(player3Name.back() == '\r'){player3Name.pop_back();}
        std::string player3ScoreString;
        std::getline(inFile, player3ScoreString);
        int player3Score = stoi(player3ScoreString);
        std::string player3Hand;
        std::getline(inFile, player3Hand);
        LinkedList* player3HandList = new LinkedList();

        Player* player3 = new Player(player3Name, player3Score, player3HandList);
        players.push_back(player3);
        player3->drawFromString(player3Hand);
    }
    if(savedPlayerCount == 4){
        std::string player4Name;
        std::getline(inFile, player4Name);
        if(player4Name.back() == '\r'){player4Name.pop_back();}

        std::string player4ScoreString;
        std::getline(inFile, player4ScoreString);
        int player4Score = stoi(player4ScoreString);

        std::string player4Hand;
        std::getline(inFile, player4Hand);
        LinkedList* player4HandList = new LinkedList();

        Player* player4 = new Player(player4Name, player4Score, player4HandList);
        players.push_back(player4);
        player4->drawFromString(player4Hand);
    }

    std::string boardString;
    std::getline(inFile, boardString);
    int height = 0;
    int width = 0;
    std::string heightString = "";
    std::string widthString = "";

    if(boardString.length() == 3){
        std::string heightString = boardString.substr(0,1);
        std::string widthString = boardString.substr(2,1);
        height = std::stoi(heightString);
        width = std::stoi(widthString);
    }else{
        std::string heightString = boardString.substr(0,2);
        std::string widthString = boardString.substr(3,2);
        height = std::stoi(heightString);
        width = std::stoi(widthString);
    }     
    board = new Board(width, height);

    std::string playedTilesString;
    std::getline(inFile, playedTilesString);
    constructBoard(board, playedTilesString);

    //Load bag
    std::string bagString;
    std::getline(inFile, bagString);

    bag = new Bag(bagString);

    std::string currentTurn;
    std::getline(inFile, currentTurn);

    bool nameFound = false;
    do{
        for(unsigned int i = 0; i < players.size(); ++i){
            if(currentTurn.compare(players.at(i)->getPlayerName()) == 0){
                currPlayer = players[i];
                nameFound = true;
            }
        }
    }while(!nameFound);
    
    if(!nameFound){
        std::cout << "Error: no player name found." << std::endl;
    }

    bool helpEnabled;
    std::string helpString;
    std::getline(inFile, helpString);
    helpEnabled = std::stoi(helpString);

    bool invalidErrorEnabled;
    std::string ieString;
    std::getline(inFile, ieString);
    invalidErrorEnabled = std::stoi(ieString);

    bool morePlayersEnabled;
    std::string morePlayersString;
    std::getline(inFile, morePlayersString);
    morePlayersEnabled = std::stoi(morePlayersString);

    inFile.close();
    isNewGame = false;

    playGame(players, helpEnabled, invalidErrorEnabled, morePlayersEnabled);
}

//get the played tiles from board for saving purpose
std::string Game::getPlayedTiles(Board *board, std::string boardString, int height)
{
    std::istringstream stringStream(boardString);

    std::string row;

    std::getline(stringStream, row);
    std::getline(stringStream, row);

    std::string tilesToString = "";

    unsigned int iterator = 0;
    int xPosition = -1;
    int yPosition = -1;

    for (int i = 0; i < height; ++i)
    {
        std::getline(stringStream, row);
        xPosition++;
        yPosition = -1;
        iterator = 0;

        while (iterator < row.length() - 3)
        {
            int boundary = row.find('|', iterator);
            yPosition++;
            iterator = boundary + 1;

            if (row.substr((boundary + 1), 2).compare("  ") != 0)
            {
                std::string tile = row.substr((boundary + 1), 2);
                std::string colour = {tile[0]};
                std::string shape = tile.substr(1, 1);

                char column = 'A' + xPosition;
                std::string xToString = {column};
                std::string yToString = std::to_string(yPosition);
                tilesToString.append(colour + shape + "@" + xToString + yToString + ", ");
            }
        }
    }
    return tilesToString;
}


// construct a board from a file 
void Game::constructBoard(Board* board, std::string boardString){
    std::istringstream stringStream(boardString);

    bool endOfFile = false;

    int subInt =0;
    for(unsigned int i =0; i < boardString.length()/7; ++i){
        std::string tileString;
        std::string coordString;
        if(i == 0){
            tileString = boardString.substr(subInt, 2);
            if(boardString.substr(subInt+6,1) == ","){
                coordString = boardString.substr(subInt+3, 3);
            }else{
                coordString = boardString.substr(subInt+3, 2);
            }
        }else{
            if(boardString.find(",", subInt) + 2 < boardString.size()){
                subInt = boardString.find(",", subInt) + 2;
                if(boardString.substr(subInt+6,1) == ","){
                    tileString = boardString.substr(subInt, 2);
                    coordString = boardString.substr(subInt+3, 3);
                }else{
                    tileString = boardString.substr(subInt, 2);
                    coordString = boardString.substr(subInt+3, 2);
                }
            }else{
                    endOfFile = true;
                }
        }
        if(!endOfFile){
            char colour = tileString[0];
            int shape = stoi(tileString.substr(1,1));

            int row = coordString[0];
            int col = 0;
            if(coordString.length() == 2){
                col = stoi(coordString.substr(1,1));
            }else{
                col = stoi(coordString.substr(1,2));
            }

            Tile* toFill = new Tile(colour, shape);
            board->setTile(row, col, toFill);
        }
    }
}

void Game::gameOver(std::vector<Player *> playerVect){
   std::cout << "Game Over: " << std::endl;
   for (unsigned int i =0; i < playerVect.size(); ++i){
       std::cout << "Score for " << playerVect[i]->getPlayerName() << ":" <<
       playerVect[i]->getPlayerScore() << std::endl;
    }

    int highscore = 0;
    std::string winningPlayer;

    if(playerVect.size() == 4){
        if(playerVect[0]->getPlayerScore() == playerVect[1]->getPlayerScore() && 
            playerVect[2]->getPlayerScore() == playerVect[3]->getPlayerScore() && 
            playerVect[1]->getPlayerScore() == playerVect[2]->getPlayerScore()){
            std::cout << "Draw Game!" << std::endl;
        }else{
            for(unsigned int i = 0; i < playerVect.size(); ++i){
                if(players[i]->getPlayerScore() > highscore){
                    highscore = players[i]->getPlayerScore();
                    winningPlayer = players[i]->getPlayerName();
                }
            }
            std::cout << "Player " << winningPlayer << " won!" << std::endl;
        }
    }else if(playerVect.size() == 3){
        if(playerVect[0]->getPlayerScore() == playerVect[1]->getPlayerScore() && 
            playerVect[1]->getPlayerScore() == playerVect[2]->getPlayerScore()){
            std::cout << "Draw Game!" << std::endl;
        }else{
            for(unsigned int i = 0; i < playerVect.size(); ++i){
                if(players[i]->getPlayerScore() > highscore){
                    highscore = players[i]->getPlayerScore();
                    winningPlayer = players[i]->getPlayerName();
                }
            }
            std::cout << "Player " << winningPlayer << " won!" << std::endl;
        }
    }else{
         if(playerVect[0]->getPlayerScore() == playerVect[1]->getPlayerScore()){
            std::cout << "Draw Game!" << std::endl;
        }else{
            if(playerVect[0]->getPlayerScore() > playerVect[1]->getPlayerScore()){
                winningPlayer = players[0]->getPlayerName();
            }else{
                winningPlayer = players[1]->getPlayerName();
            }
        }
        std::cout << "Player " << winningPlayer << " won!" << std::endl;
    }
    std::cout << "\nGoodbye" << std::endl;
}

void Game::playGame(std::vector<Player *> players, bool helpCommand, bool betterInvalidInput, bool morePlayers){
    if(isNewGame){
        currPlayer = players[0];
        for(unsigned int i = 0; i < players.size(); ++i){
            for(int j = 0; j < MAX_HAND_SIZE; ++j){
                players[i]->drawTile(bag);
            }
        }
    }
    do{
        printState(currPlayer);
        getMoveFromPlayer(currPlayer, helpCommand, betterInvalidInput, morePlayers);
        currPlayer = switchTurn(currPlayer, players);

    }while((bag->getSize() != 0 || (players[0]->getHandSize() != 0 && players[1]->getHandSize() != 0 
            && players[2]->getHandSize() != 0 && players[3]->getHandSize() != 0)) && !earlyExit);
    if(!earlyExit){gameOver(players);}
}
