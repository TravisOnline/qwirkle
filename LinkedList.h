
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   LinkedList(std::string handString);
   ~LinkedList();

   int size();
   void clear();
   Tile* get(int index);
   Tile* getFront();
   Tile* getLast();   

   void addFront(Tile* data);
   void addBack(Tile* data);

   void deleteFront();
   void deleteBack();

   void deleteAt(int index);
   void addAt(int index, Tile* data);

   std::string listString();

private:
   Node* head;
   Node* tail;
};


#endif // ASSIGN2_LINKEDLIST_H
