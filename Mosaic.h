#ifndef MOSAIC_H
#define MOSAIC_H
#include "Types.h"
#include <algorithm>
#include <iomanip>

using std::toupper;
using std::isupper;
using std::setw;
using std::endl;

class Mosaic {
public: 

    // Constructor/Deconstructor
    Mosaic(int boardID);
    //Constructor for loading 
    Mosaic(int boardID, vector<string> mosaicData); 
    ~Mosaic();

    //Returns the number of broken tiles to calculate scoring.
    int getNumBrokenTiles();

    //Returns the left hand side of the mosaic.
    string getLeftSideMosaic();

    //Returns the right hand side of the mosaic.
    string getRightSideMosaic();

    //Returns the list of broken tiles.
    string getBrokenTiles();

    //Get right side of the board in vector<string>
    vector<string> getRightBoard();

    //Returns entire mosaic as a vector.
    vector<string> getFullMosaic();

    //Check if the right side of the board has completed a row
    bool isRightSideRowCompleted();

   //Check if the input row is full on the left side 
    bool isLeftSideRowFull(int row);

    //Return the boardID
    int getBoardID();

    //Update the right side, and return their score
    int pointsCalculation(int status);

    // Display players board
   void displayCurrentBoard(vector<vector<string>> otherBoards, vector<string> otherPlayersName);

    // Update a players left side board after a turn
    vector<char> updateLeftSideBoard(vector<char> tilesToPlayerBoard, char tileColour, int mosaicRow);

    // clear the left side if the row is full, Broken tiles are removed also 
    vector<char> clearTheBoard();

    //Add a tile into the vector brokenTiles 
    void addTilesToBroken(char tile);

    //Checks if user input is valid on the player board.
    bool checkRightSideValid(int rowNumber, char tileColour);

    //Updates the completed rows at the end of a round.
    bool completedRow(int currentRow);

    //Moves all used tiles to the box lid.
    vector<char> removeTiles(); 

private:

    void leftParsing(int row, string lineData);
    void rightParsing(int row, string lineData);
    int consectiveCheck(string currentRow, int needleIndex);

    //Modification -> from 1 board split into 2 boards

    char playerBoardLeftSide[Board_Height][Board_Length] = 
    {
     {' ',' ',' ',' ','.'},   
     {' ',' ',' ','.','.'},
     {' ',' ','.','.','.'},
     {' ','.','.','.','.'},
     {'.','.','.','.','.'}
    };

    char playerBoardRightSide[Board_Height][Board_Length] =
    {
      {'b','y','r','u','l'},  
      {'l','b','y','r','u'},
      {'u','l','b','y','r'},
      {'r','u','l','b','y'},
      {'y','r','u','l','b'}
    };


    //Contains all the broken tiles to be discarded at the end of the round.
    vector<char> brokenTiles;

    //Uniquely identifies an individual player board.
    int boardID;

    //SizeOfTheBrokenTile
    const int brokenTilesSize = 7;

    //Max Index of the board
    const int boundary = 4;
};
#endif //MOSAIC_H