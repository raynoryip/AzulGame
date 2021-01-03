#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <memory>
#include <algorithm>
#include "Types.h"
#include "Factory.h"
#include "Mosaic.h"
#include "TileBag.h"
#include "Player.h"
#include "Util.h"
#include "Saveload.h"
#include "Linked_List.h"

class GameEngine{
    public:

        GameEngine();
        ~GameEngine();

        //a function start the game engine, return 0 if the game ends or hit a save;
        int start(int mode);

    private:
        //the save load object
        std::shared_ptr<Saveload> saveloadObj;
        //the tilebag object
        std::shared_ptr<TileBag> tilebag;
        //the boxlid vector
        vector<char> boxlid;
        //All Centre Factory
        vector<Factory> centreFactories;
        //All Non-Centre Factories 
        vector<Factory> factories;
        //Vector to store all players
        vector<Player> listOfPlayers;
        //Vector to store all mosaic board for players
        vector<Mosaic> playersMosaic;
        //Current player for the round, represented by an integer
        int currentPlayer;
        //First player for next round, -1 indicates a new game
        int firstPlayerNextRound;
        //Number of player
        int numOfPlayer;
        //Number of Factory
        int numOfFactory;
        //Number of Center Factory
        int numOfCentreFactory;
        //Floor Line or broken
        vector<char> floorLine;
        //User Turn Command in a linkedList
        std::shared_ptr<Linked_List> userCommand;  
        //BotHumanList for players
        vector<int> botHumanList;


        //when user starts a new game, game engine calls this method
        void newGame();
        //game engine calls this method to load a game.
        int loadGame();
        //Parsing Data
        void dataParsing(string gameName);
        //this function is used to get userName and create player objects
        void setUpPlayers();
        //this function setup all the objects for the new game
        void objSetup();
        //this function set up factories for each round
        void setFactories();
        //this function returns a 4 or less elements vector array
        vector<char> distributeTiles(vector<char> &undistributed_tiles);
        //Add tiles into the boxLid
        void addTilesToBoxLid(vector<char> tiles);
        //below functions are different phases of the game
        int startRound();
        bool checkEndOfRound();
        bool checkEndOfGame();
        void playerTurn();
        bool playerInput();
        void updateTurn(int factoryNo, char tileColour, int mosaicRow, int centreFactToPlace);
        bool factoryValidate(int factoryNo, char tileColour);
        bool mosaicRowValidate(int mosaicRow, char tileColour);
        bool centreFactoryValidate(int factoryNo);
        void calculatePoints(int playerIndex, int status);
        //All the getters to get the string info of the game
        string getAllFactories();
        string getAllMosaic();
        string getTileBagBoxLid();
        string getPlayer();
        
};
#endif // !GAME_ENGINE_H