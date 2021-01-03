#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "Types.h"
#include "Factory.h"
#include "Mosaic.h"
#include "TileBag.h"
#include "Util.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

#define GAMESAVE "saves.azul"
#define FSAVE "factories.save"
#define MSAVE "mosaic.save"
#define TSAVE "tilebag_boxlid.save"
#define PSAVE "players.save"

class Saveload{

    public: 

        Saveload();
        ~Saveload();

        //Save the game
        int saveGame(string factories, string mosaic, string tileBagBoxLid, string player, string gameName);
        //Check if saves.azul already contains the existing gameName to prevent duplicates.
        bool gameNameExist(string gameName);
        //get all saved game name if exists
        int getAllSavedFile();
        //check if all the files exist before loading
        int loadGameCheckFileStatus();
        //return the size of the listOfSavedGames
        int listOfSavedGamesSize();
        //return the list of All the game Saves
        vector<string> getListOfGameSaves();
        //load all the files
        vector<string> loadGame_factories(string gameName);
        vector<string> loadGame_mosaic(string gameName);
        vector<string> loadGame_tileBagBoxLid(string gameName);
        vector<string> loadGame_players(string gameName);


    
    private:        

        vector<string> listOfSavedGames;
};

#endif //SAVE_LOAD_H