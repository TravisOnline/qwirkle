#include <iostream>
#include <string>
#include "Tile.h"
#include "TileCodes.h"

Tile::Tile(Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
}


Colour Tile::getTileColour(){
    return this->colour;
}

Shape Tile::getTileShape(){
    return this->shape;
}

std::string Tile::getTileString(){
    // std::string i = "";
    // for ( int x = 0; x < 6; x++)
    // {
    //     if(getTileColour() == RED & getTileShape() == x){
    //         i = RED + x;
    //     }else if (getTileColour() == ORANGE & getTileShape() == x)
    //     {
    //         i = ORANGE + x;
    //     }else if (getTileColour() == YELLOW & getTileShape() == x)
    //     {
    //         i = YELLOW + x;
    //     }else if (getTileColour() == GREEN & getTileShape() == x)
    //     {
    //         i = GREEN + x;
    //     }else if (getTileColour() == BLUE & getTileShape() == x)
    //     {
    //         i = BLUE + x;
    //     }else if (getTileColour() == PURPLE & getTileShape() == x)
    //     {
    //         i = PURPLE + x;
    //     }
        
    // }
    // return i;
   std::string tileString = colour + std::to_string(shape);
   return tileString;
    
}

    

