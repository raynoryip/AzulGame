#ifndef PLAYER_H
#define PLAYER_H

#include "Types.h"

class Player{
    public:
        Player(string player_Name, int player_Id, int botOrHuman);
        void setScore(int score);
        void addScore(int score);
        string getPlayerName();
        int getPlayerScore();
        int getPlayerID(); 
        int isBotorHuman();

    private:
        string playerName;
        int playerScore;
        int playerID;
        int botOrHuman;

};
#endif // !PLAYER_H