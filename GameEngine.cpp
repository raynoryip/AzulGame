#include "GameEngine.h"

GameEngine::GameEngine() {
    saveloadObj = std::make_shared<Saveload>();
    tilebag = std::make_shared<TileBag>();
    userCommand = std::make_shared<Linked_List>();
    firstPlayerNextRound = 0;
 }
GameEngine::~GameEngine() { }

int GameEngine::start(int mode){

    //To ensure all the vectors are clean before starting a game
    centreFactories.clear();
    factories.clear();
    listOfPlayers.clear();
    playersMosaic.clear();
    botHumanList.clear();
    boxlid.clear();

    int gameState = GAME_RUNNING;

    cout << "Let's Play!" << "\n\n";

    if(mode==NEWGAME){              //New Game
            
        cout << "No of Players?" << '\n';
        cout << "2\n" << "3\n" << "4\n";
        this->numOfPlayer = Util::userInput(2, 4);

        //Also update the number of factory used in Game
        this->numOfFactory = this->numOfPlayer*2 + 1;

        cout << "-----------------------------------------" << '\n';
        cout << "Choose Bot or Human for each player:" << '\n';
        cout << "Please type [ B ] for bot player or [ H ] for human player" << '\n';
        cout << "e.g. Player 1: B" << '\n';

        for(int num=0; num < this->numOfPlayer; num++){
            string text = "Player " + std::to_string(num+1) +  " : ";
            this->botHumanList.push_back(Util::BotOrHuman(text));
        }

       cout << "----------------------------------------" << '\n';
       cout << "How many centre factories would you like?" << '\n';
       cout << "minimum 1, maximum 2, input 1 or 2" << '\n';
       this->numOfCentreFactory = Util::userInput(1,2);
       cout << "----------------------------------------" << '\n';
        //Start the new game
        newGame();
    }
    else{                                           //Load Game
        gameState = loadGame();
        if(gameState==LOADGAME_FAIL){ 
            cout << "Abort Loading. Program terminated" << endl;
            return GAME_EXIT;
        }
        if(gameState==LOADGAME_SUCCESS){
            gameState = GAME_RUNNING;
        }
        //else gameState = LOADGAME_SUCCESS == RUNNING -> continue
    }

    while(gameState==GAME_RUNNING){
        gameState = startRound();
        if(gameState==SAVEGAME_SUCCESS){
            cout << "Your game has been saved. See you next time" << endl;
            return GAME_EXIT;
        }
        if(gameState==SAVEGAME_FAIL){
            cout << "Abort saving. Program terminated" << endl;
            return GAME_EXIT;
        }
        if(gameState==ENDGAME_EXIT){
            cout << "Game Over! See you next time" << endl;
            return GAME_EXIT;
        }
    }

    return gameState;
}

void GameEngine::newGame(){
    this->objSetup();
    this->setUpPlayers();
}

int GameEngine::loadGame(){

    int noOfGameSave = this->saveloadObj->listOfSavedGamesSize();
    vector<string> gameSaves;
    int userInput;

    //if there is file to load in the directory 
    if(noOfGameSave > 0){

        const int startingIndex = 1;
        int index = 1;

        if(this->saveloadObj->loadGameCheckFileStatus()==LOADGAME_FAIL){
            return LOADGAME_FAIL;
        }

        gameSaves = this->saveloadObj->getListOfGameSaves();

        cout << "Which save would you like to load:" << '\n';
        for(string gameName : gameSaves){
            cout << index << " " << gameName << '\n'; 
            index += 1;
        }

        userInput = Util::userInput(startingIndex, noOfGameSave);

    }else{
        cout << "you don't have any saved game to load" << '\n';
        return LOADGAME_FAIL;
    }
    
    //Because startingIndex is 1, so -1 for position index

    string gameName = gameSaves[userInput-1];
    dataParsing(gameName);

    cout << "Game Loading Successful." << '\n';
    return LOADGAME_SUCCESS;
}

void GameEngine::dataParsing(string gameName){
    

    //parsing the factory data
    //clear the factories vector to ensure everything is clean
    this->factories.clear();
    this->centreFactories.clear();
    vector<string> factoriesData = this->saveloadObj->loadGame_factories(gameName);

    int dataIndex = 0;

    this->numOfCentreFactory =  std::stoi(factoriesData[dataIndex]);
    dataIndex += 1;
    this->numOfFactory = std::stoi(factoriesData[dataIndex]);
    dataIndex += 1;

    //Create factory base on the the content
    for(int index=0; index <= this->numOfCentreFactory; index++){       
            string tempStr = factoriesData[dataIndex];
            vector<char> tempData(tempStr.begin(), tempStr.end());
            Factory factory = Factory(index, tempData);
            this->centreFactories.push_back(factory);
            dataIndex += 1;
    }

    for(int index=0;index <= this->numOfFactory ;index++){
        string tempStr = factoriesData[dataIndex];
        vector<char> tempData(tempStr.begin(), tempStr.end());
        Factory factory = Factory(index, tempData);
        this->factories.push_back(factory);
        dataIndex += 1;
    }

    //---------------update Mosaic
    this->playersMosaic.clear();

    dataIndex = 0;

    //break the mosaic data into several vectors and then create obj and pass into the class
    vector<string> mosaicData = this->saveloadObj->loadGame_mosaic(gameName);

    this-> numOfPlayer = std::stoi(mosaicData[dataIndex]);
    dataIndex += 1;
    vector<string> mosaicDataVec;
    int boardID = 0;
    int const totalNumOfLineInMData = this->numOfPlayer*11 + 1;


    for(int index = dataIndex; index < totalNumOfLineInMData; index++){
        mosaicDataVec.push_back(mosaicData[index]);
        if(index%11==0){
            Mosaic mosaic = Mosaic(boardID, mosaicDataVec);
            this->playersMosaic.push_back(mosaic);
            boardID +=1;
            mosaicDataVec.clear();
        }
    } 

    //---------------update tileBag and BoxLid
    vector<string> tilebagBoxLidData = this->saveloadObj->loadGame_tileBagBoxLid(gameName);
    string tilebagData = tilebagBoxLidData[0];
    vector<char> tilebagVec(tilebagData.begin(), tilebagData.end());
    this->tilebag->loadTiles(tilebagVec);

    string boxLidData = tilebagBoxLidData[1];
    if(boxLidData!="EMPTY"){
        this->boxlid = vector<char>(tilebagData.begin(), tilebagData.end());
    }


    //---------------update playerData
    this->listOfPlayers.clear();
    vector<string> playerData = this->saveloadObj->loadGame_players(gameName);
    dataIndex = 0;
    this->currentPlayer = std::stoi(playerData[dataIndex]);
    int const totalNumOfLineInPData = this->numOfPlayer*3 + 1;

    string playerName = "";
    int score = 0;
    int humanBot = 0;
    int playerID = 0;
    dataIndex += 1;
    vector<string> tempStore;

    for(int index=dataIndex; index < totalNumOfLineInPData; index++){
        tempStore.push_back(playerData[index]);
        if(index%3==0){
            playerName = tempStore[0];
            score = std::stoi(tempStore[1]);
            humanBot =  std::stoi(tempStore[2]);
            Player player = Player(playerName, playerID, humanBot);
            player.setScore(score);
            this->listOfPlayers.push_back(player);
            playerID += 1;
            tempStore.clear();
        }
    }

}


int GameEngine::startRound(){

    cout << "=== Start Round ===" << '\n';
    cout << "You can save the game by the start of each round or press anything to continue" << '\n';
    cout << "If you want to save your game, input  [ save [your filename] ] e.g. save Azul1" << "\n\n"; 

    //Set Up Factories for each round
    setFactories();

    //By default player 0 will goes first
    this->currentPlayer=firstPlayerNextRound;

    vector<string> userPrompt_split;
    string filename;
    string userPrompt;
    bool saveFinish = false;

    //Waiting user Input, if input!= save, start next round
    do{
        userPrompt_split.clear();
        userPrompt = "";
        std::getline(cin, userPrompt);

        if (userPrompt.rfind("save", 0) == 0) {
            Util::stringSlice(userPrompt, ' ', userPrompt_split);
            if(userPrompt_split.size()>1){
                filename = userPrompt_split[1]; 
                 return saveloadObj->saveGame(getAllFactories(), getAllMosaic(), 
                    getTileBagBoxLid(), getPlayer(), filename); // return to main menu and eXit the game 
                saveFinish = true;
            }else{
                cout << "Please input a correct filename" << '\n';
            }
        }
        else{
            cout << "Starting next round!" << "\n\n";
            saveFinish = true;
        }

    }while(saveFinish==false);

    //Starting new round
    while(!checkEndOfRound()) {
        playerTurn();
    }
    cout << "\n< the following turns happen >" << '\n';
    this->userCommand->printTheList();

    //Round ends, and calculate points of each player
    int size = this->listOfPlayers.size();
    for(int index=0; index< size; index++){
        calculatePoints(index, ROUND_CALCULATION);
    }

    if(checkEndOfGame()) {

        int highest_score;
        vector<int> listOfScores;

        int size = this->listOfPlayers.size();
        for(int index=0; index<size; index++){
            calculatePoints(index, ENDGAME_CALCULATION);
        }   

        for(Player player: this->listOfPlayers){
            listOfScores.push_back(player.getPlayerScore());
        }

        vector<int> highestScorePos;
        highest_score = *std::max_element(listOfScores.begin(), listOfScores.end());

        cout << "Here is the score of all Players: " << '\n';
        //Check if more than 1 player got highest score and also output the score of other players

        size = listOfScores.size();
        for(int index=0; index < size; index++ ){
            if(listOfScores[index]==highest_score){
                highestScorePos.push_back(index);
            }
            cout << this->listOfPlayers[index].getPlayerName() << " with score " << listOfScores[index] << '\n';
        }

        if(highestScorePos.size()==1){
            cout << "The winner is " << this->listOfPlayers[highestScorePos[0]].getPlayerName();
        }else{
            cout << "Seems like more than 1 player got the same higest score! So we have winners and they are: \n";
            for(int index : highestScorePos){
                cout << this->listOfPlayers[index].getPlayerName() << '\n';
            }
        }
        cout << "Congratulation! Game Over" << endl;
        
        cout << "=== END OF GAME ===" << '\n';

        return ENDGAME_EXIT;
    }
    //Now as it is not end Game, we can clear the board for next round
    vector<char> tilesToBoxLid;
    size = this->playersMosaic.size();
    for(int index=0; index < size; index++){
        tilesToBoxLid = this->playersMosaic[index].clearTheBoard();
        addTilesToBoxLid(tilesToBoxLid);
    }
    cout << "=== END OF ROUND ===" << '\n';

    return GAME_RUNNING;

}

bool GameEngine::checkEndOfRound() {

    for(auto factory: this->centreFactories){
        if(!factory.isFactoryEmpty()) {
            return false;
        } 
    }
    for(auto factory: this->factories) {
        if(!factory.isFactoryEmpty()) {
            return false;
        } 
    }
    return true;
}

//Modified for M2

bool GameEngine::checkEndOfGame() {
    vector<string> playerBoard;

    //Check for all players
    for(Mosaic mosaic : this->playersMosaic){
        if(mosaic.isRightSideRowCompleted()){
            return true;
        }
    }
    return false;
}


//Modified for more than 2 players 

void GameEngine::playerTurn(){

    cout << "TURN FOR PLAYER: " << this->listOfPlayers[currentPlayer].getPlayerName() << '\n';
    cout << "CURRENT SCORE: " << this->listOfPlayers[currentPlayer].getPlayerScore() << '\n';
    cout << "PLAYER GO FIRST NEXT ROUND: " << this->listOfPlayers[firstPlayerNextRound].getPlayerName() << '\n';
    cout << "Centre Factory(s):" << '\n';
    for(Factory factory: this->centreFactories){
        cout << factory.toConsole();
    }
    cout << "Factories:" << '\n';
    for(Factory factory: this->factories){
        cout << factory.toConsole();
    }
    
    //Display boards
    int currentPlayerID = this->listOfPlayers[currentPlayer].getPlayerID();
    vector<vector<string>> otherBoards;
    vector<string> otherPlayersName;

    for(Mosaic board: this->playersMosaic){
        if(board.getBoardID()!=currentPlayerID){    
            otherBoards.push_back(board.getFullMosaic());
        }
    }
    for(Player player: this->listOfPlayers){
        if(player.getPlayerID()!=currentPlayerID){
            otherPlayersName.push_back(player.getPlayerName());
        }
    }

     this->playersMosaic[currentPlayerID].displayCurrentBoard(otherBoards, otherPlayersName);


    //Turn: User Input their moves
    bool validInput = false; 
    while(validInput==false){
        // return true if players Input is valid
        validInput = playerInput();
        if(validInput==false){
            cout << "Invalid Name or Move" << '\n';
        }
    } // if validInput == true stop the loop

    //changing current player
    if(this->currentPlayer < numOfPlayer-1){
        this->currentPlayer += 1;
    }else{ 
        this->currentPlayer = PLAYER_0;
    } 
}


bool GameEngine::playerInput(){
    vector<string> playersMove;
    playersMove.clear();
    bool isValid = true;
    string userInput = "";
    cout << "> ";
    std::getline(cin, userInput); 

    if(userInput.rfind("help", 0) == 0){
        cout << "You can input [ turn x y z ] to perform an action" << '\n';
        cout << "x = Factory No, y = TileColor in that Factory, and z = the row in board you want to place.\n";
        cout << "E.g. turn 3 B 4 -> put Tile B from Factory 3 into the 4th row of the Mosaic Board\n"; 
        cout << "Press anything to continue.\n"; 
        std::getline(cin, userInput);
        cout << "> ";
        std::getline(cin, userInput);
    }

    string turnCommand;
    int factoryNo = 0;
    char tileColour;
    int mosaicRow = 0;
    int centreFactToPlace = 0; //Either 0 or 1

    Util::stringSlice(userInput, ' ', playersMove);
    if(playersMove.size()!=4) { 
        return false;
    } 
    //try convert the player command into a int, if exception occurs means its not an int.
    try{
        //convert the first command "turn" into lowercase
        turnCommand = playersMove[0];
        std::transform(turnCommand.begin(), turnCommand.end(), turnCommand.begin(), ::tolower);
        //if the 1st argument not keyword "turn" and the 3rd argument is not a single char
        if(turnCommand.compare(string("turn"))!=0 || playersMove[2].length() > 1){  
            return false;
        }
        factoryNo = std::stoi(playersMove[1]);
        tileColour = playersMove[2][0];
        mosaicRow = std::stoi(playersMove[3]);

        if(this->numOfCentreFactory>1 && factoryNo > this->numOfCentreFactory-1){
            cout << "Which Centre Factory would you like to place, please input 0 or 1\n";
            centreFactToPlace = Util::userInput(0,1);
        }

    }catch(std::invalid_argument){
        return false;
    }
  
    isValid = (tileColour != 'F' && factoryValidate(factoryNo, tileColour) 
            && mosaicRowValidate(mosaicRow, tileColour) && centreFactoryValidate(centreFactToPlace));
    
    if(isValid){
        updateTurn(factoryNo, tileColour, mosaicRow, centreFactToPlace);
        cout << "Turn successful." << '\n' << '\n';
        if(this->currentPlayer==PLAYER_1){
            this->userCommand->addNodeAtTheBack(userInput, 'A');
        }else if(this->currentPlayer==PLAYER_2){
            this->userCommand->addNodeAtTheBack(userInput, 'B');
        }else if(this->currentPlayer==PLAYER_3){
            this->userCommand->addNodeAtTheBack(userInput, 'C');
        }else{
            this->userCommand->addNodeAtTheBack(userInput, 'D');
        }
        return isValid;
    }
    return isValid;
}

//-----------------------------------------------------//

void GameEngine::updateTurn(int factoryNo, char tileColour, int mosaicRow, int centreFactToPlace) {

    vector<char> tilesToCentreFact;
    vector<char> tilesToPlayerBoard;
    vector<vector<char>> tilesBeReturn;
    vector<char> toBoxLid; 

    //So if numOfCentreFactory = 2, then those 2 centre factory index must be 0 or 1
    if(factoryNo <= this->numOfCentreFactory-1){
        //If F exist in both factories means no one has every get tiles from the centre Factory
        if(this->centreFactories[0].containColor('F')){
            int size = this->centreFactories.size();
            for(int index=0; index < size; index++){
                this->centreFactories[index].removeF();
            }
              //Add this F to the player
            this->playersMosaic[this->currentPlayer].addTilesToBroken('F');
            //and he will become the next round first player
            this->firstPlayerNextRound = this->currentPlayer;
            
        }
        tilesToPlayerBoard = this->centreFactories[factoryNo].removeCentreTiles(tileColour);      

    }else{ //Not centre Factory
        factoryNo =  factoryNo - numOfCentreFactory;
        tilesBeReturn = this->factories[factoryNo].removeTiles(tileColour);
        tilesToCentreFact = tilesBeReturn[0];
        tilesToPlayerBoard = tilesBeReturn[1];

        cout << "tilesToCenFact -> \n"; 
        for(char c: tilesToCentreFact){
            cout << c;
        }
        cout << endl;
        cout << "tilesToPB -> \n"; 
        for(char c: tilesToPlayerBoard){
            cout << c;
        }
        cout << endl;

        this->centreFactories[centreFactToPlace].addTiles(tilesToCentreFact);
    }

    int numOfTiles = tilesToPlayerBoard.size();
    cout << "numOfTiles -> " << numOfTiles << endl;
    vector<char> tilesToBoxLid;
    tilesToBoxLid = this->playersMosaic[this->currentPlayer].updateLeftSideBoard(tilesToPlayerBoard, tileColour, mosaicRow);
    // put excessive tiles to boxLid if any
    addTilesToBoxLid(tilesToBoxLid); 

}

void GameEngine::addTilesToBoxLid(vector<char> tiles){
    int len = tiles.size();
    for(int index=0; index < len; index++){
        this->boxlid.push_back(tiles[index]);
    }
}

bool GameEngine::factoryValidate(int factoryNo, char tileColour){

    //! smaller than 0 or greater than [numOfFactory] + numOfCentreFactory] - 1
    //! is empty(true) and
    // contain that tileColour in that factory

    int maxFactoryIndex = this->numOfFactory + numOfCentreFactory - 1;
    if(factoryNo > numOfCentreFactory-1){
            int factoryIndex = factoryNo-numOfCentreFactory;

            return (!(factoryNo < 0  || factoryNo > maxFactoryIndex ) && !(this->factories[factoryIndex].isFactoryEmpty()) 
            && this->factories[factoryIndex].containColor(tileColour));
    }else{

        return (!(factoryNo < 0  || factoryNo > maxFactoryIndex ) && !(this->centreFactories[factoryNo].isFactoryEmpty()) 
            && this->centreFactories[factoryNo].containColor(tileColour));
    }

}

bool GameEngine::mosaicRowValidate(int mosaicRow, char tileColour){
    //! smaller than 1 or greater 6
    //! false in checkRightSideValid

    return !(mosaicRow < 1 || mosaicRow > 6) && (this->playersMosaic[this->currentPlayer].checkRightSideValid(mosaicRow, tileColour));
}

bool GameEngine::centreFactoryValidate(int cenFactoryNo){
    if(cenFactoryNo==0 || cenFactoryNo==1){
        return true;
    }
    return false; 
}

//Modified for M2

void GameEngine::calculatePoints(int playerIndex, int status) {
    int points = this->playersMosaic[playerIndex].pointsCalculation(status);
    this->listOfPlayers[playerIndex].addScore(points);
}


/*
    GameEngine::setUpPlayers()
    This function setUp players, get their name, and push back into the vector
*/

void GameEngine::setUpPlayers(){
    string playerName = "";
    int botNameIndex = 0;
    int botHumanState = HUMAN_PLAYER;

    //This loop get the names of all players. For bot player Name, e.g. BOT 1

    for(int num=0; num < this->numOfPlayer; num++){
        if(this->botHumanList[num]==HUMAN_PLAYER){
            do{
                cout << "Enter a name for player " << num << ": "<<endl;
                std::getline(cin, playerName);
                if(playerName.empty()){
                    cout << "Invalid Name" << endl;
                }
            }
            while(playerName.empty());
        }
        else{ //If player is a bot
            playerName = "BOT " + std::to_string(botNameIndex);
            botNameIndex += 1;
            botHumanState = BOT_PLAYER;
        }
        Player player = Player(playerName, num, botHumanState);
        this->listOfPlayers.push_back(player);
    }

    //player 1 goes first by default for a new Game
    this->currentPlayer = PLAYER_1;
}

void GameEngine::objSetup(){
    
    //Creating Player boards depend on num of players
    for(int index=0; index < this->numOfPlayer; index++){
        Mosaic playerMosaic(index); 
        this->playersMosaic.push_back(playerMosaic);
    }
}

void GameEngine::setFactories(){
    //if the tilebag has less than [4*numOfFactory] tiles, refill the bag with all the tiles inside the boxlid
    int tilesToBeRemove =  this->numOfFactory*4;
    if(this->tilebag->getRemainingTiles() < tilesToBeRemove) {
        //add all the tiles in boxLid to the tilebag.
        this->tilebag->addLeftOverTiles(this->boxlid);
        //clear the boxLid
        this->boxlid.clear();
    }

    //Tile bag already pre-generated all tiles, so now we get [4*numOfFactory] tiles per round
    vector<char> undistributed_tiles = this->tilebag->removeTilesFromBag(tilesToBeRemove);

    //Clear all the factories before start
    this->centreFactories.clear();
    this->factories.clear();
    int factoryIndex = 0;
    vector<char> token({'F'});

    //Creating factory for each round
    //adding First Player token to the both centre Factory
    for(int index=0; index < this->numOfCentreFactory; index++){
        Factory factory = Factory(factoryIndex);
        factory.addTiles(token);
        this->centreFactories.push_back(factory);
        factoryIndex += 1;
    }

    //creating other non-centre Factories
    for(int index=0 ;index < this->numOfFactory ;index++){
        Factory factory = Factory(factoryIndex);
        factory.addTiles(distributeTiles(undistributed_tiles));
        this->factories.push_back(factory);
        factoryIndex += 1;
    }
}


vector<char> GameEngine::distributeTiles(vector<char> &undistributed_tiles){
    vector<char> vectorRET;
    int count = 0;
    //this loop add the first element from the undistributed tile vector to the new vector 
    //take 4 elements from the undistributed tile vector until the vector is empty
    //if vector has less than 4 elements take all of them
    while(undistributed_tiles.size() > 0 && count < MAXTILES){
        vectorRET.push_back(undistributed_tiles[0]);
        undistributed_tiles.erase(undistributed_tiles.begin());
        count++;
    }
    return vectorRET;
}

string GameEngine::getAllFactories(){
    string factoriesStr = "";
    factoriesStr += std::to_string(this->numOfCentreFactory) + "\n";
    factoriesStr += std::to_string(this->numOfFactory) + "\n";
    for(unsigned int index=0; index < this->centreFactories.size(); index++){
        factoriesStr += this->centreFactories[index].toString() + "\n";
    }
    for(unsigned int index=0;index < this->factories.size(); index++){
        factoriesStr += this->factories[index].toString() + "\n";
    }
    return factoriesStr;
}

string GameEngine::getAllMosaic(){
    string mosaicStr = "";
    mosaicStr += std::to_string(this->numOfPlayer) + '\n';
    for(unsigned int index=0; index < this->playersMosaic.size();index++){
        mosaicStr += this->playersMosaic[index].getLeftSideMosaic();
        mosaicStr += this->playersMosaic[index].getRightSideMosaic();
        mosaicStr += this->playersMosaic[index].getBrokenTiles() + '\n';
    }
    return mosaicStr;
}

string GameEngine::getTileBagBoxLid(){
    string boxLidTileBagStr = "";
    string boxLidStr;
    
    boxLidTileBagStr += this->tilebag->getRemaining() + '\n';
    if(this->boxlid.size() > 0){
        boxLidTileBagStr += string(this->boxlid.begin(), this->boxlid.end()) + '\n';
    }else{
        boxLidTileBagStr += string("EMPTY")+ "\n";
    }
    return boxLidTileBagStr;
}

string GameEngine::getPlayer(){
    string finalStr = std::to_string(currentPlayer) + string("\n");
    for(unsigned int index=0;index<listOfPlayers.size();index++){
        finalStr += listOfPlayers[index].getPlayerName() + '\n';
        finalStr += std::to_string(listOfPlayers[index].getPlayerScore()) + '\n';
        finalStr += std::to_string(listOfPlayers[index].isBotorHuman()) + '\n';
    }
    return finalStr;
}