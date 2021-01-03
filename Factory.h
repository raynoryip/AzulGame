#ifndef FACTORY_H
#define FACTORY_H 

#include "Types.h"
#include <sstream>
#include <algorithm>

class Factory {
public: 

    // Constructor/Deconstructor
    Factory(int factoryID);
    //Constructor for loading
    Factory(int factoryID, vector<char> loadingTiles);
    ~Factory();

    //Returns the factoryID.
    int getFactoryID();

    //Adds first player token to the central factory.
    void addFirstPlayerToken();

    //Adds tiles to the factory.
    void addTiles(vector<char> newTiles);

    //Determines the number of tiles with the chosen colour that are in the factory.
    int selectTiles(char tileColour);

    //Determines if the select the tile color is in this factory
    bool containColor(char tileColour);

    //Determines if the factory is current filled or emptied
    bool isFactoryEmpty();

    //Specific funtion to remove F from the vector (Because of my architecture in M2)
    void removeF();

    //remove tiles from the centre factory,
    vector<char> removeCentreTiles(char tileColour);

    //remove tiles from the normal factory, and return unused tiles
    vector<vector<char>> removeTiles(char tileColour);

    //This function is to return all tiles in string format, e.g RYYU
    string toString();

    //This function outputs "1: R Y Y U"
    string toConsole();

private:

    //When a round starts, store up to 4 tiles into the vector  
    vector<char> tiles;

    //Uniquely identifies an individual factory.
    int factoryID;

};
#endif //FACTORY_H