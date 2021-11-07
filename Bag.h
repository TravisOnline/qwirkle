#ifndef BAG_H
#define BAG_H


#include <random>
#include <istream>
#include <string>
#include "LinkedList.h"


#define MAXIMUM_BAG_SIZE    72



// Must use a LinkedList for Bag as per section 2.3.4 in page 9

class Bag{
    
    public:
        Bag();
        Bag(std::string bagString);
        ~Bag();

        int getSize();
        Tile* pop_front();
        void push_back(Tile* toAdd);
        std::string printBag();
        void shuffleBag();

    private:
        LinkedList* bag;
        void fillBag(); //Only Bag class needs to fill the bag, therefore it is private
};


#endif // BAG_H
