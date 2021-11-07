#include "Node.h"

Node::Node(Node* prev, Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
   this->prev = prev;
}

Node::Node(Node& other)
{
   this->tile = new Tile(*other.tile);
   this->next = other.next;
   this->prev = other.prev;
}

Node::~Node()
{
   delete tile;
}