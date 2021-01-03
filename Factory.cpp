#include "Factory.h"


Factory::Factory(int factoryID) {
    this->factoryID = factoryID;
}

Factory::Factory(int factoryID, vector<char> loadingTiles){
    this->tiles = loadingTiles;
    this->factoryID = factoryID;
}


Factory::~Factory() {

}

int Factory::getFactoryID() {
    return factoryID;
}

void Factory::removeF(){
    std::vector<char>::iterator position = std::find(this->tiles.begin(), this->tiles.end(), 'F');
    if (position != this->tiles.end()) 
    this->tiles.erase(position);
}

void Factory::addTiles(vector<char> newTiles) {
    //Adds the new tiles to the vector.
    int length = newTiles.size();

    for(int i = 0; i < length; i++) {
        this->tiles.push_back(newTiles[i]);
    }
}

bool Factory::containColor(char tileColour) {
    for(char tile: this->tiles) {
        if(tile == tileColour) {
            return true;
        }
    }
    return false;
}

bool Factory::isFactoryEmpty(){
    if(this->tiles.size()!=0){
        return false;
    }
    return true;
}

string Factory::toString(){
    std::stringstream ss;
    string tileStr;
    for(unsigned int index=0;index <tiles.size();index++){
        ss << tiles[index];
    }
    tileStr = ss.str();
    return tileStr;
}

string Factory::toConsole(){
    std::stringstream ss;
    string tileStr;

    ss << this->getFactoryID() << ": ";
    for(unsigned int index=0;index <tiles.size();index++){
        ss << tiles[index] << " ";
    }
    ss << "\n";
    tileStr = ss.str();
    return tileStr;
}

/*
    This functions remove all the same color tile from the factory
*/

vector<char> Factory::removeCentreTiles(char tileColour){
    vector<char> tilesToPlayerBoard;
    
    for(char tile: this->tiles){
        if(tile==tileColour){
            tilesToPlayerBoard.push_back(tile);
        }
    }
    this->tiles.erase(std::remove(this->tiles.begin(), this->tiles.end(), char(tileColour)), this->tiles.end());
    return tilesToPlayerBoard;
}

/*
this function returns 2 vector<char>,
1 is for passing into the centre Factory
1 is for passing into the player board
and then clear the factory
*/
vector<vector<char>> Factory::removeTiles(char tileColour) {
    vector<char> tilesToCentreFact;
    vector<char> tilesToPlayerBoard;
    vector<vector<char>> vectorToRet;

    for(char tile : this->tiles){
        if(tile==tileColour){
            tilesToPlayerBoard.push_back(tile);
        }else{
            tilesToCentreFact.push_back(tile);
        }
    }
    vectorToRet.push_back(tilesToCentreFact); //As index 0
    vectorToRet.push_back(tilesToPlayerBoard); //As index 1

    this->tiles.clear();

    return vectorToRet;
}