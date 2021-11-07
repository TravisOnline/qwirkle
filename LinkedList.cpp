
#include "LinkedList.h"

LinkedList::LinkedList()
{
   head = nullptr;
   tail = nullptr;
}

LinkedList::~LinkedList()
{
   clear();
}

LinkedList::LinkedList(std::string handString){
   LinkedList* hand = new LinkedList();
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

int LinkedList::size()
{
   int length = 0;

   Node *current = head;
   while (current != nullptr)
   {
      ++length;
      current = current->next;
   }
   return length;
}

void LinkedList::clear()
{
   if (head == nullptr)
   {
      return;
   }

   Node *upto = head;

   while (upto != nullptr)
   {
      //set node to be deleted
      Node *toBeDeleted = upto;

      //go to next node
      upto = upto->next;

      //delete the previously selected node
      delete toBeDeleted;
   }
   head = nullptr;
}

Tile *LinkedList::get(int index)
{
   Tile *returnedTile = nullptr;

   if (index >= 0 && index < size())
   {
      int counter = 0;
      Node *current = head;

      while (counter < index)
      {
         ++counter;
         current = current->next;
      }
      returnedTile = current->tile;
   }
   return returnedTile;
}

Tile *LinkedList::getFront()
{
   Tile *returnedTile = nullptr;
   if (head != nullptr)
   {
      returnedTile = head->tile;
   }
   return returnedTile;
}

Tile *LinkedList::getLast()
{
   Tile *returnedTile = nullptr;
   if (tail != nullptr)
   {
      returnedTile = tail->tile;
   }
   return returnedTile;
}

void LinkedList::addFront(Tile *data)
{
   if (head == nullptr && tail == nullptr)
   {
      head = new Node(nullptr, data, nullptr);
      tail = head;
   }
   else
   {
      head->prev = new Node(nullptr, data, head);
      head = head->prev;
   }
}

void LinkedList::addBack(Tile *data)
{
   if (head == nullptr && tail == nullptr)
   {
      head = new Node(nullptr, data, nullptr);
      tail = head;
   }
   else
   {
      tail->next = new Node(tail, data, nullptr);
      tail = tail->next;
   }
}

void LinkedList::deleteFront()
{
   if (size() > 0)
   {
      if (size() == 1)
      {
         delete head;
         head = nullptr;
         tail = nullptr;
      }
      else
      {
         Node *newHead = head->next;
         delete head;
         newHead->prev = nullptr;
         head = newHead;
      }
   }
}

void LinkedList::deleteBack()
{
   if (size() > 0)
   {
      if (size() == 1)
      {
         delete head;
         head = nullptr;
         tail = nullptr;
      }
      else
      {
         Node *newTail = tail->prev;
         delete tail;
         newTail->next = nullptr;
         tail = newTail;
      }
   }
}

//input: index must be >=0 and <size
void LinkedList::deleteAt(int index)
{
   if (this->size() > 0 && (index >= 0 && index < size()))
   {

      if (this->size() == 1)
      {
         delete head;
         head = nullptr;
         tail = nullptr;
      }
      else
      {
         if (index == 0)
         {
            deleteFront();
         }
         else if (index + 1 == this->size())
         {
            deleteBack();
         }
         else
         {
            int count = 0;
            Node *current = head;
            while (count < index)
            {
               current = current->next;
               count++;
            }
            Node *prv = current->prev;
            Node *nxt = current->next;
            delete current;
            prv->next = nxt;
            nxt->prev = prv;
         }
      }
   }
}

void LinkedList::addAt(int index, Tile *data)
{
   if (index == 0)
   {
      addFront(data);
   }
   else if (index > 0 && index < this->size())
   {
      int count = 0;
      Node *temp = head;
      for (int i = 0; i < index; i++)
      {
         temp = temp->next;
         count++;
      }
      // Node* addPrev = temp->prev;
      // Node* add = new Node(temp->prev, data, temp);
      // addPrev->next = add;
      // temp->prev = add;

      temp->prev->next = new Node(temp->prev, data, temp);
      temp->prev = temp->prev->next;
   }
   else if (index == this->size())
   {
      addBack(data);
   }
}

std::string LinkedList::listString()
{
   std::string tileList = "";
   for (int i = 0; i < size(); i++)
   {
      tileList.append(get(i)->getTileString());
      if(i < size() - 1)

      {
         tileList.append(", ");
      }
   }
   return tileList;
}
