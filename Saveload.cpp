#include "Saveload.h"

Saveload::Saveload(){ 
    getAllSavedFile();
}
Saveload::~Saveload() { }

int Saveload::getAllSavedFile(){
    this->listOfSavedGames.clear();
    std::ifstream file{GAMESAVE};
    string gameNames = "";

    // if the saves.azul file exist get all Name
    if(file){
        while(file){
            std::getline(file, gameNames);
            if(gameNames.length()>0){ //To prevent passing in the empty Line
                this->listOfSavedGames.push_back(gameNames);
            }
        }

        file.close();
        return SAVEFILE_EXIST;
    }else{
        file.close();
        return SAVEFILE_DOESNT_EXIST;
    }
}

bool Saveload::gameNameExist(string gameName){
    
    if(std::find(this->listOfSavedGames.begin(), this->listOfSavedGames.end(), gameName) != this->listOfSavedGames.end()) {
        //if gameName Exist
        return true;
    }
    return false;
}

int Saveload::saveGame(string factories, string mosaic, string tileBagBoxLid, string player, string gameName){

    getAllSavedFile();
    //if saves.azul file exist and has game saved inside of it 
    if(gameNameExist(gameName)==false){
        //check if the gameName already exist, if not exist 
        //create saves.azul, append to it if the function is called again
         std::ofstream mainfile{GAMESAVE, std::ios::app};
        if (!mainfile)
        {
            // Print an error and return state
            std::cerr << "couldn't open the file " << GAMESAVE << '\n';
            return SAVEGAME_FAIL;
        }
        mainfile <<  gameName << '\n';
        mainfile.close();
    }

   
    string fileName = gameName + string("-");
    
    //create the factories.save

    std::ofstream frfile(fileName+FSAVE);
    if (!frfile)
    {
        // Print an error and return state
        std::cerr << "couldn't open the file " << FSAVE << '\n';
        return SAVEGAME_FAIL;
    }
    frfile << factories;
    frfile.close();

    //create the mosaic.save

    std::ofstream msfile(fileName+MSAVE);
    if (!msfile)
    {
        // Print an error and return state
        std::cerr << "couldn't open the file " << MSAVE << '\n';
        return SAVEGAME_FAIL;
    }
    msfile << mosaic;
    msfile.close();

    //create tilebag_boxlid.save 

    std::ofstream tbfile(fileName+TSAVE);
    if (!tbfile)
    {
        // Print an error and return state
        std::cerr << "couldn't open the file " << TSAVE << '\n';
        return SAVEGAME_FAIL;
    }
    tbfile << tileBagBoxLid;
    tbfile.close();

    //create players.save

    std::ofstream plfile(fileName+PSAVE);
    if (!plfile)
    {
        // Print an error and return state
        std::cerr << "couldn't open the file " << PSAVE << '\n';
        return SAVEGAME_FAIL;
    }
    plfile << player;
    plfile.close();

    return SAVEGAME_SUCCESS;
}

int Saveload::loadGameCheckFileStatus(){

    if(getAllSavedFile()==SAVEFILE_DOESNT_EXIST){
        return LOADGAME_FAIL;
    }

    string currentGame;
    string gameName = "";

    for(string currentGame: this->listOfSavedGames){
        gameName = currentGame + string("-");
        
        std::ifstream factorySave(gameName + FSAVE);
        if(!factorySave){
            std::cerr << "cannot open or located the " << FSAVE << " in " << currentGame << '\n';
            return LOADGAME_FAIL;
        }

        std::ifstream mosaicSave(gameName + MSAVE);
        if(!mosaicSave){
            std::cerr << "cannot open or located the " << MSAVE << " in " << currentGame << '\n';
            return LOADGAME_FAIL;
        }

        std::ifstream tileBagSave(gameName + TSAVE);
        if(!tileBagSave){
            std::cerr << "cannot open or located the " << TSAVE << " in " << currentGame << '\n';
            return LOADGAME_FAIL;
        }

        std::ifstream playersSave(gameName + PSAVE);
        if(!playersSave){
            std::cerr << "cannot open or located the " << PSAVE << " in " << currentGame << '\n';
            return LOADGAME_FAIL;
        }
    } 
    //if all the files exists
    return LOADGAME_SUCCESS;
};

vector<string> Saveload::getListOfGameSaves(){
    return this->listOfSavedGames;
}

int Saveload::listOfSavedGamesSize(){
    return this->listOfSavedGames.size();
}

vector<string> Saveload::loadGame_factories(string gameName){
    string fileName = gameName + string("-");
    std::ifstream file(fileName + FSAVE);
    string dataInput;
    vector<string> factoryData;

    while(file){
         std::getline(file, dataInput);
        if(dataInput.length()>0){ //To prevent passing in the empty Line
                factoryData.push_back(dataInput);
        }
    }
    return factoryData;
}

vector<string> Saveload::loadGame_mosaic(string gameName){
    string fileName = gameName + string("-");
    std::ifstream file(fileName + MSAVE);
    string dataInput;
    vector<string> mosaicData;

    while(file){
         std::getline(file, dataInput);
        if(dataInput.length()>0){ //To prevent passing in the empty Line
                mosaicData.push_back(dataInput);
        }
    }
    return mosaicData;
}
vector<string> Saveload::loadGame_tileBagBoxLid(string gameName){
    string fileName = gameName + string("-");
    std::ifstream file(fileName + TSAVE);
    string dataInput;
    vector<string> tileBoxLidData;

    while(file){
         std::getline(file, dataInput);
        if(dataInput.length()>0){ //To prevent passing in the empty Line
                tileBoxLidData.push_back(dataInput);
        }
    }
    return tileBoxLidData;
}
vector<string> Saveload::loadGame_players(string gameName){
    string fileName = gameName + string("-");
    std::ifstream file(fileName + PSAVE);
    string dataInput;
    vector<string> playerData;

    while(file){
         std::getline(file, dataInput);
        if(dataInput.length()>0){ //To prevent passing in the empty Line
                playerData.push_back(dataInput);
        }
    }
    return playerData;
}