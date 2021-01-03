#include <string>

#include "Mosaic.h"

//Modified for M2

Mosaic::Mosaic(int boardID) {
    this->boardID = boardID;
    for(int index=0;index<7;index++){
        this->brokenTiles.push_back('.');
    }
}

Mosaic::Mosaic(int boardID, vector<string> mosaicData){
    this->boardID = boardID;
    const int mosaicDataLen = 10;
    const int leftSideData = 4; 
    const int rightSideData = 9; 

    for(string str: mosaicData){
        cout << str << " " << str.length();
        cout << '\n';
    }

    //Processing left hand side
    int lineIndex = 0;
    for(int row = 0; row < mosaicDataLen; row++){
        string lineStr = mosaicData[row];
        if(row <= leftSideData){ //From line 0 to Line 4 
            lineIndex = row;
            leftParsing(lineIndex, lineStr);
        }else if(row > leftSideData && row <= rightSideData){ //From line 5 to line 9
            lineIndex = row - 5;
            rightParsing(lineIndex, lineStr);
        }else if(row==10){ //Last row
            brokenTiles = vector<char>(lineStr.begin(), lineStr.end());
        }
    }

} 

void Mosaic::leftParsing(int row, string lineData){
    int length = lineData.length();
    for(int index=0;index<length;index++){
        this->playerBoardLeftSide[row][boundary-index] = lineData[index];
    }
}

void Mosaic::rightParsing(int row, string lineData){
    int length = lineData.length();
    for(int index=0;index<length;index++){
        this->playerBoardRightSide[row][index] = lineData[index];
    }
}

Mosaic::~Mosaic() {

}

int Mosaic::getNumBrokenTiles() {
    return this->brokenTilesSize;
}

string Mosaic::getLeftSideMosaic() {
    string leftMosaicStr;
    for(int row=0;row<Board_Height;row++){
        for(int col=0;col <row+1;col++){
            leftMosaicStr += this->playerBoardLeftSide[row][boundary-col];  
        }
        leftMosaicStr += '\n';
    }

    return leftMosaicStr;
}

string Mosaic::getRightSideMosaic() {
    string rightMosaicStr;

    for(int row=0;row<Board_Height;row++){
        for(int index=0;index<Board_Length;index++){
            rightMosaicStr += this->playerBoardRightSide[row][index];
        }
        rightMosaicStr += '\n';
    }

    return rightMosaicStr;
}

string Mosaic::getBrokenTiles() {
    return string(brokenTiles.begin(), brokenTiles.end()); 
}

//Modified for M2.
//Current Usage -> return the entire PlayerBoard (Both left and right side)

vector<string> Mosaic::getRightBoard(){
    vector<string> rightBoard;
    string tempStr;
    for(int row=0;row< Board_Height;row++){
        tempStr = "";
        for(int col=0;col < Board_Length; col++){
            tempStr += this->playerBoardRightSide[row][col];
        }
        rightBoard.push_back(tempStr);
    }
    return rightBoard;
}

int Mosaic::getBoardID(){
    return this->boardID;
}


bool Mosaic::isRightSideRowCompleted(){
    int completed = 0;
    for(int row=0;row<Board_Height; row++){
        completed = 0;
        for(int col=0; col <Board_Length; col++){
            if(isupper(this->playerBoardRightSide[row][col])){
                completed += 1;
            }
        }
        if(completed==5){
            return true;
        }
    }
    return false;
}

bool Mosaic::isLeftSideRowFull(int row){
    int slotCheck = row+1;
    for(int col=0; col < slotCheck; col++){
        if(playerBoardLeftSide[row][boundary-col]=='.'){
            return false;
        }
    }
    return true;
}

int Mosaic::pointsCalculation(int status){
    int points = 0;
    int completedTile = 0;
    char currentSlot;
    char tileColour;

    if(status==ROUND_CALCULATION){
        //Update the right side of the board first
        for(int row=0; row < Board_Height; row++){

            if(isLeftSideRowFull(row)==true){
                
                int tileColIndex = 0;

                //Find the tileColour of that row and update right side
                tileColour = this->playerBoardLeftSide[row][boundary];
                for(int col=0; col < Board_Length; col++){
                    if(this->playerBoardRightSide[row][col]==std::tolower(tileColour)){
                        this->playerBoardRightSide[row][col] = tileColour;
                        tileColIndex = col;
                    }
                }

                //And then calculates points for that completed row
                //check consecutive tiles in the horizontal row;
                string colOfMosaic;
                string rowOfMosaic;
                for(int index=0; index < Board_Length; index++){
                    colOfMosaic += this->playerBoardRightSide[row][index];
                    rowOfMosaic += this->playerBoardRightSide[index][tileColIndex];
                } 

                int pointA, pointB;
                pointA = pointB = 0;
                pointA = consectiveCheck(colOfMosaic, tileColIndex);
                pointB = consectiveCheck(rowOfMosaic, row);
                if(pointA==1&&pointB==1){ //mean only one and no consective tile
                    points += 1;
                }else if(pointA==1||pointB==1)
                {
                    if(pointA==1){
                        points += pointB;
                    }else{
                        points += pointA;
                    }
                }else{
                    points += pointA + pointB;
                }
            }
        }
        //Deduce points on floor line
        int floorlineDeduction[brokenTilesSize] = {-1,-1,-2,-2,-2,-3,-3};
        for(int index=0; index < brokenTilesSize; index++){
            if(this->brokenTiles[index]!='.'){
                points -= floorlineDeduction[index];
            }
        }
    }
    if(status== ENDGAME_CALCULATION){
        
        //2 points for each completed row
        for(int row=0; row < Board_Height; row++){
            completedTile = 0;
            for(int col=0; col < Board_Length; col++){
                currentSlot = this->playerBoardRightSide[row][col];
                if(isupper(currentSlot)){
                    completedTile += 1;
                }
            }
            if(completedTile==5){
                points+=2;
            }
        }
        //7 points for each completed vertical line
        for(int col=0; col < Board_Length; col++){
            completedTile = 0;
            for(int row=0;row < Board_Height; row++){
                currentSlot = this->playerBoardRightSide[row][col];
                if(isupper(currentSlot)){
                    completedTile += 1;
                }
            }
            if(completedTile==5){
                points+=7;
            }
        }
        //10 points for each color you have placed all 5 tiles on the wall
        char colourList[5] = {'B', 'Y', 'R', 'U', 'L'};
        for(char colour: colourList){
            completedTile = 0;
            for(int row=0; row<Board_Height; row++){
                for(int col=0; col < Board_Length; col++){
                    currentSlot = this->playerBoardRightSide[row][col];
                    if(currentSlot==colour){
                        completedTile += 1;
                    }
                }
            }
            if(completedTile==5){
                points += 10;
            }
        }   
    }

    return points;
}

//Return the max number of Consective Capital Tiles on that row
int Mosaic::consectiveCheck(string rowOfMosaic, int needleIndex){
    //if the tile is at rightMost
    int points = 0;
    if(needleIndex==boundary){
        for(int col=boundary; col >= 0; col--){
            if(isupper(rowOfMosaic[col])){
                points += 1;
            }else{
                return points;
            }
        }
        return points;
    }
    //if the tile is at leftMost
    if(needleIndex==0){
        for(int col=0; col <= boundary; col++){
            if(isupper(rowOfMosaic[col])){
                points +=1;
            }else{
                return points;
            }
        }
        return points;
    }
    //if the tile is between rightMost and leftMost
    points += 1; //Default 1 point
    int index=needleIndex;
    bool stop = false;
    //check righthand side
    index = needleIndex + 1;
    while(stop==false && index <= boundary){
        if(isupper(rowOfMosaic[index])){
            points += 1;
            index += 1;;
        }else{
            stop=true;
        }
    }
    //check lefthand side
    stop = false;
    index = needleIndex-1;
    while(stop==false && index >= 0){
        if(isupper(rowOfMosaic[index])){
            points += 1;
            index += 1;;
        }else{
            stop=true;
        }
    }
    return points;
}

//After calculating score, clear the board

vector<char> Mosaic::clearTheBoard(){
    vector<char> tilesToBoxLid;

    int slot = 0; //no of slot on the current row
    //left Side -> clear the board 
    for(int row=0; row < Board_Height; row++){
        slot = row+1; 
        //if full remove all the tiles from the row and pass it to the vector
        if(isLeftSideRowFull(row)==true){

            for(int col=0; col < slot; col++){
                tilesToBoxLid.push_back(this->playerBoardLeftSide[row][boundary-col]);
               this->playerBoardLeftSide[row][boundary-col] = '.';
            }
        }
    }
    //and for the floor line
    for(int index=0; index < brokenTilesSize; index++){
        if(this->brokenTiles[index]!='.'){
            if(this->brokenTiles[index]!='F'){
                tilesToBoxLid.push_back(this->brokenTiles[index]);
            }
            this->brokenTiles[index] = '.';
        }
    }
    return tilesToBoxLid;
}


vector<string> Mosaic::getFullMosaic() {
    vector<string> fullMosaic;
    string tempStr;
    
     for(int row=0;row<Board_Height;row++){
        tempStr = std::to_string(row+1) + ".:";
        //from the left side
        for(int col=0;col<Board_Length;col++){
            tempStr += this->playerBoardLeftSide[row][col];
        }
        tempStr += "||";
        //to the right side
        for(int col=0;col<Board_Length;col++){
            tempStr += this->playerBoardRightSide[row][col];
        }
        fullMosaic.push_back(tempStr);
    }
    //and the floor line
    tempStr = "6 Broken: " + string(this->brokenTiles.begin(), this->brokenTiles.end());
    fullMosaic.push_back(tempStr);

    return fullMosaic;
}

/*
displaying two players board together
if more than 2 boards, would be display as follows:
        [ Baord A ]     [ Board B ]
        [ Board C ]     [ Board D ]   
*/
void Mosaic::displayCurrentBoard(vector<vector<string>> otherBoards, vector<string> otherPlayersName) {
    string tempStr;
    string board1Str, board2Str, board3Str, board4Str;
    string player2Name, player3Name, player4Name;
    string whiteSpace = "            ";
    vector<string> ourMosaic = this->getFullMosaic();
    vector<string> board2, board3, board4;

    int numOfOtherBoards =  otherBoards.size();
    //for only 2 players
    if(numOfOtherBoards >=1){
        board2 =  otherBoards[0];  
        player2Name = otherPlayersName[0];
    } // 3 players
    if(numOfOtherBoards >= 2){
        board3 = otherBoards[1];
        player3Name = otherPlayersName[1];
    } // 4 players
    if(numOfOtherBoards >= 3){
        player4Name = otherPlayersName[2];
        board4 = otherBoards[2];
    }

    cout <<  "[Mosaic For You]" << setw(30)  << "[Mosaic For " + player2Name + "]"+ "\n";
    
    //Getting every line of Board 1 & 2
    for(int index =0; index < Board_Length+1; index++){
            board1Str = ourMosaic[index];
            board2Str  = board2[index];
            cout << board1Str << setw(30) <<  board2Str + "\n";
            board1Str = "";
            board2Str= "";
    }

    cout << "\n";


    //3 Players
    if(numOfOtherBoards == 2){
            cout <<  "\n";
            cout <<  "[Mosaic For " + player3Name + "]"+ "\n";
            for(int index =0; index < Board_Length+1; index++){
                board3Str  = board3[index];
                cout << board3Str << setw(30) << "\n";
                board3Str = "";
            }
    }
    // 4 Players
    if(numOfOtherBoards == 3){
            cout << "\n";
            cout << "[Mosaic For " + player3Name + "]" << setw(30) << "[Mosaic For " + player4Name + "]"+ "\n";
            for(int index =0; index < Board_Length+1; index++){
                board3Str = board3[index];
                board4Str  = board4[index];
                cout << board3Str << setw(30) << board4Str + "\n";
                board3Str = "";
                board4Str= "";
            }
    }
}

/*
This function passing tilesToPlayerBoard and updates the current board,
if there is excessive tiles left from the floor line, they will be store in a vector and return it
*/

vector<char> Mosaic::updateLeftSideBoard(vector<char> tilesToPlayerBoard, char tileColour, int mosaicRow) {

    int rowIndex = mosaicRow -1;
    int col = 0;

    if(mosaicRow!=6){
        while(!tilesToPlayerBoard.empty() && col < mosaicRow){
            if(this->playerBoardLeftSide[rowIndex][boundary-col]=='.'){
                this->playerBoardLeftSide[rowIndex][boundary-col] = tileColour;
                tilesToPlayerBoard.pop_back();
            }
            col += 1;
        }
    }
    //so the remaining must be excessive and should place it to the floorline
    col = 0;
    if(!tilesToPlayerBoard.empty()){
        while(!tilesToPlayerBoard.empty() && col < this->brokenTilesSize){
            if(this->brokenTiles[col]=='.'){
                this->brokenTiles[col] = tileColour;
                tilesToPlayerBoard.pop_back();
            }
            col += 1;
        }
    }
    
    //In a rare case, if the tilesToPlayerBoard still not empty i.e. if the floor line can't hold the exccessive tiles
    //we return this vector and they should be placed in the boxLid

    return tilesToPlayerBoard;

}


void Mosaic::addTilesToBroken(char tile){
    for(int index=0; index < brokenTilesSize; index++){
        if(this->brokenTiles[index]=='.'){
            brokenTiles[index] = tile;
            return;
        }
    }
}

bool Mosaic::checkRightSideValid(int rowNumber, char tileColour) {
    /*  for a valid move:
        1) right side of the current row is empty
        2) or if it is not empty, it must contain the same color tile, excessive tiles moves to the floor line
        3) and the left side does not contain the same color tile
        if row == 6, means it is passing to the floor line,
        then automatically return true
    */
    int const boundary = 4;
    int rowIndex = rowNumber-1;
    int filled = 0;

    if(rowNumber==6){
        return true;
    }else{
        //check left side - if the current row is full
        for(int col=0; col < rowNumber; col++){
            if(playerBoardLeftSide[rowIndex][boundary-col]!='.'){
                if(playerBoardLeftSide[rowIndex][boundary-col]!=tileColour){
                    return false;
                }
                filled += 1;
            }
        }
        if(filled==rowNumber){
            return false;
        }

        //check right side
        for(int col=0; col < Board_Length; col++){
            if(playerBoardRightSide[rowIndex][col]==toupper(tileColour)){
                return false;
            }
        }
    }

    return true;
}

