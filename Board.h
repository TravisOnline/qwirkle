#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include "Tile.h"

//#include "Coordinate.h"

#include <algorithm>

class Board{


public:
    Board();
    Board(int width, int height);
    ~Board();

    int getRowSize();
    int getColumnSize();
    void printBoard();
    bool isEmpty();
    void setTile(char row, int col, Tile * tile);
    Tile * getTile(int r, int c);
    bool validation(char row, int col, Tile* newTile);
    int validateLineVertical(char row, int col, Tile* newTile, bool checkVertical);
    int calTotalScore(char row, int col);
    std::string toString();
    int calScore(char row, int col, bool checkVertical);
    bool betterInvalidInput = false;

private:

  std::vector<std::vector<Tile *>> vBoard;
  int width;
  int height;
};

#endif