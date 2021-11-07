#include "Player.h"

Player::Player()
{

}

Player::Player(std::string playerName, LinkedList* newHand){
    this->playerName = playerName;
    this->score = 0;
    this->hand = newHand;
}

Player::Player(std::string playerName, int score, LinkedList* savedHand){
    this->playerName = playerName;
    this->score = score;
    this->hand = savedHand;
}

Player::~Player(){
    delete hand;
}

std::string Player::getPlayerName(){
    return this->playerName;
}

LinkedList* Player::getPlayerHand(){
    return hand;
}

int Player::getPlayerScore(){
    return this->score;
}

void Player::setPlayerName(std::string name){
    this->playerName = playerName;
}

void Player::setPlayerScore(int score){
    this->score += score;
}

// find a tile in hand at certain index
int Player::searchHand(std::string toFind)
{
    char findColor = toFind.at(0);
    int findShape = toFind.at(1) - '0';
    int tilePos = -1;
    for (int i = 0; tilePos==-1 && i < hand->size(); i++)
    {
        if(hand->get(i)->getTileColour() == findColor && 
        hand->get(i)->getTileShape() == findShape)
        {
            tilePos = i;
        }
    }
    return tilePos;
}


// delete a tile in hand at certain index
Tile* Player::pop_at(int index)
{
    Tile *toSend = nullptr;
    if (hand->size() > 0)
    {
        toSend = new Tile(*(hand->get(index)));
        hand->deleteAt(index);
    }
    return toSend;
}


// add a tile to hand at certain index
void Player::push_at(int index, Tile *data)
{
    hand->addAt(index, data);
}

void Player::push_back(Tile *data)
{
    hand->addBack(data);
}

// length of the hand tile list
int Player::getHandSize()
{
    return hand->size();
}

// print hand tiles as a string
std::string Player::printHand()
{
    return hand->listString();
}

//pull tile from bag
void Player::drawTile(Bag* bag){
    if(bag->getSize() > 0){
        hand->addBack(bag->pop_front());
    }
}

void Player::drawFromString(std::string handString){
    int subInt = 0;
    for(unsigned int i =0; i <= (handString.length()/4); ++i){

        std::string tileString;
        if(i == 0){
            tileString = handString.substr(subInt, 2);
        }else{
            subInt = handString.find(",", subInt) + 2;
            tileString = handString.substr(subInt, 2);
        }
        char colour = tileString[0];
        int shape = stoi(tileString.substr(1,1));
        Tile* toFill = new Tile(colour, shape);
        hand->addBack(toFill);
    }
}
