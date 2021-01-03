#ifndef TILEBAG_H
#define TILEBAG_H
#include "Types.h"

class TileBag {
public: 

    //Constructor/Deconstructor
    TileBag();
    ~TileBag();

    //Number of elements in the tile bag.
    int getRemainingTiles();

    //Populates the array with tiles.
    void addTiles(vector<char> newTiles);

    //Removes 20 tiles to populate factories.
    vector<char> removeTilesFromBag(int tilesToBeRemove);

    //function for loading
    void loadTiles(vector<char> tiles);

    //Repopulate the tile bag from the box lid
    void addLeftOverTiles(vector<char> boxLidTiles);

    //get remaining tiles in the bag
    string getRemaining();

private:

    //Holds all of the tiles left in the bag.
    vector<char> tiles;

    //Holds all of the tiles to be used in the factories.
    vector<char> factoryTiles;

    //Randomises the tiles in the tile bag.
    void randomiseTiles(vector<char> &tilesToBeShuffle);
};
#endif // TILEBAG_H! 