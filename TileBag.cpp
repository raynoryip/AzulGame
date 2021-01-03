#include <algorithm>
#include <random>
#include <chrono>

#include "TileBag.h"

TileBag::TileBag() {

    //Populating the tile bag with 100 tiles. 20 tiles of each colour.
    for(int i = 0; i < 100; i++) {
        if(i < 20) {
            tiles.push_back('R');
        } else if(i < 40) {
            tiles.push_back('Y');
        } else if(i < 60) {
            tiles.push_back('B');
        } else if(i < 80) {
            tiles.push_back('L');
        } else {
            tiles.push_back('U');
        }
    }

    //Shuffle the initial tiles.
    randomiseTiles(this->tiles);
}

TileBag::~TileBag() {

}

int TileBag::getRemainingTiles() {
    return this->tiles.size();
}

void TileBag::loadTiles(vector<char> tiles){
    this->tiles = tiles;
}

vector<char> TileBag::removeTilesFromBag(int tilesToBeRemove) {
    factoryTiles.clear();

    //in case the bag has less than [tilesToBeRemove] tiles
    if(int(this->tiles.size()) < tilesToBeRemove){
        tilesToBeRemove = this->tiles.size();
    }

    //Adds tiles from the bag to intermediate vector before being added to factories. 
    for(int i = 0; i < tilesToBeRemove; i++) {
        factoryTiles.push_back(tiles[i]);
    }

    //Removes tiles from tile bag and updates number of remaining tiles.
    tiles.erase(tiles.begin(), tiles.begin() + tilesToBeRemove);

    return factoryTiles;
}

void TileBag::randomiseTiles(vector<char> &tilesToBeShuffle) {
    //Creates a seed for randomisation.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    //Randomises the tiles in the bag.
    shuffle(tilesToBeShuffle.begin(), tilesToBeShuffle.end(), std::default_random_engine(seed));
}

string TileBag::getRemaining(){
    
    string remainTileStr(this->tiles.begin(), this->tiles.end());
    return remainTileStr;
}

void TileBag::addLeftOverTiles(vector<char> boxLidTiles){
    //Shuffle the boxLid first so it wont change the order of the pre-generated tiles inside the tileBag
    randomiseTiles(boxLidTiles); 
    for(char tile : boxLidTiles){
        this->tiles.push_back(tile);
    }
}