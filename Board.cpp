#include "Board.h"

#include <iostream>

Board::Board()
{
    // width = 6;
    // height = 6;
    width = 26;
    height = 26;

    for (int i = 0; i < width; i++)
    {
        std::vector<Tile *> temp;
        for (int j = 0; j < height; j++)
        {
            temp.push_back(nullptr);
        }
        vBoard.push_back(temp);
    }
    betterInvalidInput = false;
}

Board::Board(int width, int height){
    this->width = width;
    this->height = height;

    for(int i =0 ; i < width; ++i){
        std::vector<Tile *> temp;
        for (int j = 0; j < height; j++){
            temp.push_back(nullptr);
        }
        vBoard.push_back(temp);
    }
    betterInvalidInput = false;
}

int Board::getRowSize()
{
    return vBoard.size();
}

int Board::getColumnSize()
{
    return vBoard[0].size();
}

bool Board::isEmpty()
{
    bool res = true;

    for (int i = 0; i < getRowSize(); i++)
    {
        for (int j = 0; j < getRowSize(); j++)
        {
            if (vBoard[i][j] != nullptr)
                res = false;
        }
    }

    return res;
}

void Board::setTile(char row, int col, Tile * tile) 
{
    int boardSize = getRowSize();
    if ((row - 'A') < boardSize && col < boardSize)
    {
        vBoard[row - 'A'][col] = tile;
    }else{
        std::cout << "\nInvalid position in Board";
    }
}

Tile * Board::getTile(int row, int col) 
{
    int boardSize = getRowSize();
    Tile * tile = nullptr;
    if (row < boardSize && col < boardSize)
    {
        tile = vBoard[row][col];
    }
    return tile;
}

int Board::validateLineVertical(char row, int col, Tile* newTile, bool checkVertical) 
{
    std::string errorMsg;
    bool isValid = true;
    int validityType = 1;
    int verticalTilesInLine = 1;
    
    int rowPos;
    int colPos;
    if (checkVertical) 
    {
        rowPos = 1;
        colPos = 0;
    } else {
        rowPos = 0;
        colPos = 1;
    }
    char rowIndex = row - 'A';
    bool colorValidationFailed = false;
    bool shapeValidationFailed = false;
    bool reachedEndOfLine = false;
    
    if (!isEmpty()) 
    {
        for (int i = 1;
            verticalTilesInLine <= 6 && isValid && rowIndex + (i * rowPos) < 26 && col + (i * colPos) < 26 && !reachedEndOfLine; ++i) 
            {
                Tile* boardTile = getTile(rowIndex + (i * rowPos), col + (i * colPos));
                if (boardTile == nullptr) 
                {
                    reachedEndOfLine = true;
                } else {
                        if (boardTile->getTileColour() != newTile->getTileColour()) 
                        {
                            colorValidationFailed = true;
                        }
                        if (boardTile->getTileShape() != newTile->getTileShape()) 
                        {
                            shapeValidationFailed = true;
                        }
                        if (boardTile->getTileColour() == newTile->getTileColour() && boardTile->getTileShape() == newTile->getTileShape()) 
                        {
                            shapeValidationFailed = true;
                            colorValidationFailed = true;
                        }
                        if (shapeValidationFailed && colorValidationFailed) 
                        {
                            isValid = false;
                            errorMsg = "Validation Error: Shape and Color in this line are not matching the new tile";
                        }
                        ++verticalTilesInLine;
                    }
            }
            colorValidationFailed = false;
            shapeValidationFailed = false;
            reachedEndOfLine = false;
            for (int i = 1; verticalTilesInLine <= 6 && isValid && rowIndex - (i * rowPos) >= 0
                && col - (i * colPos) >= 0 && !reachedEndOfLine; ++i) 
                {
                    Tile* boardTile = getTile(rowIndex - (i * rowPos), col - (i * colPos));
                    if (boardTile == nullptr) 
                    {
                        reachedEndOfLine = true;
                    } else {
                        if (boardTile->getTileColour() != newTile->getTileColour()) 
                        {
                            colorValidationFailed = true;
                        }
                        if (boardTile->getTileShape() != newTile->getTileShape()) 
                        {
                            shapeValidationFailed = true;
                        }
                        if (boardTile->getTileColour() == newTile->getTileColour()
                            && boardTile->getTileShape() == newTile->getTileShape()) 
                        {
                            shapeValidationFailed = true;
                            colorValidationFailed = true;
                        }
                        if (shapeValidationFailed && colorValidationFailed) 
                        {
                            isValid = false;
                            errorMsg = "Error: Shape and Color in this line are not matching the new tile";
                        }
                        ++verticalTilesInLine;
                    }
                }

      if (isValid && verticalTilesInLine > 6) {
         isValid = false;

         errorMsg = "Error: lines should not be longer than ";
         errorMsg += 6;


      }

      if (!isValid) {
         validityType = -1;
      } else if (verticalTilesInLine < 2) {
         validityType = 0;
      } else {
         validityType = 1;
      }
   }
   return validityType;
}

bool Board::validation(char row, int col, Tile* newTile) {
    
    std::string errorMsg = "";
    bool isValid = true;
    if (newTile == nullptr) 
    {
        isValid = false;
        std::cout << "Error: Tile is null" << std::endl;;
    }else if (row < 'A' || row > 'Z' || col < 0 || col > 26 - 1) 
    {
        isValid = false;
    }else if (getTile(row - 'A', col) != nullptr) 
    {
        isValid = false;
   } else {
        bool checkVertical = true;
        int validityTypeVertical = validateLineVertical(row, col, newTile, checkVertical);
        int validityTypeHorizontal;

        if (validityTypeVertical == -1) {
            isValid = false;
        } else {
            validityTypeHorizontal = validateLineVertical(row, col, newTile, !checkVertical);

            if (validityTypeHorizontal == -1) {
                isValid = false;
            } else if ((validityTypeVertical == 0 && validityTypeHorizontal == 0)) {
                isValid = false;
            }
        }
   }
   return isValid;
}

int Board::calScore(char row, int col, bool checkVertical) 
{
    int rowPos;
    int colPos;
    if (checkVertical) 
    {
        rowPos = 1;
        colPos = 0;
    } else {
        rowPos = 0;
        colPos = 1;
    }
    int scoreCounter = 0;
    bool reachedEndOfLine = false;
    char rowIndex = row - 'A';
    for (int i = 1; rowIndex + (i * rowPos) < 26 && col + (i * colPos) < 26 && !reachedEndOfLine; ++i)
    {
        Tile * boardTile = getTile(rowIndex + (i * rowPos), col + (i * colPos));
        if (boardTile == nullptr) 
        {
            reachedEndOfLine = true;
        } else {
            ++scoreCounter;
        }
    }

    reachedEndOfLine = false;
    for (int i = 1; rowIndex - (i * rowPos) >= 0 && col - (i * colPos) >= 0 && !reachedEndOfLine; ++i) 
    {
        Tile* boardTile = getTile(rowIndex - (i * rowPos), col - (i * colPos));
        if (boardTile == nullptr) 
        {
            reachedEndOfLine = true;
        } else {
            ++scoreCounter;
        }
    }

    if (scoreCounter > 0) 
    {
        ++scoreCounter;
    }

    return scoreCounter;
}

int Board::calTotalScore(char row, int col) 
{
    //bool checkQwirkle = false;

    int twoLinesScore = 0;
    int qwirkleScore = 0;

    bool checkVertical = true;
    int Vscore = calScore( row, col, checkVertical);
    int Hscore = calScore( row, col, !checkVertical);

    if (Vscore > 0 && Hscore > 0) 
    {
        twoLinesScore = 2;
    }

    if (Vscore == 6 || Hscore == 6 ) 
    {
        qwirkleScore += 6;
        std::cout << "Qwirkle!!" << std::endl;;
        //checkQwirkle = true;
    }

    int totalScore = Vscore + Hscore + twoLinesScore + qwirkleScore;
    return totalScore;
}

std::string Board::toString(){
    std::string result = "  ";
    int maxRow = getRowSize();
    for (int i = 0; i < maxRow; i++)
    {
        if ( i > 9)
        {
            result.append(" ");
        }else
        {
            result.append("  ");
        }
        result.append(std::to_string(i));
        
    }
    result.append("\n");
    result.append("  -");
    for (int i = 0; i < maxRow; i++)
    {
        result.append("---");
    }
    result.append("\n");
    for (int row = 0; row < maxRow; row++)
    {
        char letter = 'A' + row;
        std::string rowPos = " ";
        rowPos[0] = letter;
        result.append(rowPos);
        result.append(" |");
        for (int col = 0; col < maxRow; col++)
        {
           if (vBoard[row][col] != nullptr)
           {
               result.append(vBoard[row][col]->getTileString());
               result.append("|");
           }else
           {
               result.append("  |");
           }
            
        }
        result.append("\n");
        
    }
    return result;
    
    
}

Board::~Board()
{

    for (int i = 0; i < getRowSize(); i++)
    {
        for (int j = 0; j < getColumnSize(); j++)
        {
            if(vBoard[i][j] != nullptr){delete vBoard[i][j];}
        }
    }
    for (int i = 0; i < getRowSize(); i++)
    {
        vBoard[i].clear();
    }
    vBoard.clear();
}


