
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <iostream>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Tile(Colour colour, Shape shape);

  
   Colour getTileColour();
   Shape getTileShape();
   std::string getTileString();

private:
   Colour colour;
   Shape  shape;

   
};

#endif // ASSIGN2_TILE_H
