#include "Bag.h"
#include <fstream>
#include <random>

Bag::Bag()
{
    bag = new LinkedList();
    fillBag();
}

//TODO: Defensive Programming!
Bag::Bag(std::string bagString){
    bag = new LinkedList();

    int subInt = 0;
    if(bagString != "")
    {
    for(unsigned int i =0; i <= (bagString.length()/4); ++i){

        std::string tileString;
        if(i == 0){
            tileString = bagString.substr(subInt, 2);
        }else{
            subInt = bagString.find(",", subInt) + 2;
            tileString = bagString.substr(subInt, 2);
        }
        char colour = tileString[0];
        int shape = stoi(tileString.substr(1,1));
        
        Tile* toFill = new Tile(colour, shape);
        
        bag->addBack(toFill);
    }        
    }

}

Bag::~Bag()
{
    delete bag;
}

void Bag::fillBag()
{
    std::ifstream file("Bag.txt");
    char tileColour = 'a';
    int tileShape = 0;
    Tile* toFill = nullptr;
    while(!file.eof())
    {
        file >> tileColour;
        file >> tileShape;
        toFill = new Tile(tileColour, tileShape);
        bag->addBack(toFill);
    }
    file.close();
}

int Bag::getSize()
{
    return bag->size();
}


Tile *Bag::pop_front()
{
    Tile *toSend = nullptr;
    if (bag->size() > 0)
    {
        toSend = new Tile(*(bag->getFront()));
        bag->deleteFront();
    }
    return toSend;
}

void Bag::push_back(Tile *toAdd)
{
    bag->addBack(toAdd);
}

std::string Bag::printBag()
{
    return bag->listString();
}

void Bag::shuffleBag()
{
    std::random_device engine;
    LinkedList* tempBag = new LinkedList();
    int toMove = 0;
    Tile* moveTile = nullptr;
    while(bag->size() > 0)
    {
        std::uniform_int_distribution<int> uniform_dist(0, bag->size()-1);
        toMove = uniform_dist(engine);
        moveTile = bag->get(toMove);
        tempBag->addBack(new Tile(*moveTile));
        bag->deleteAt(toMove);
    }
    delete bag;
    bag = tempBag;
}
