#include "Player.h"

Player::Player(string player_Name, int player_Id, int botOrHuman){
    this->playerName = player_Name;
    this->playerScore = 0;
    this->playerID = player_Id;
    this->botOrHuman = botOrHuman;
}

void Player::setScore(int score){
    this->playerScore = score;
    if(this->playerScore < 0) {
        this-> playerScore = 0;
    }
}

void Player::addScore(int score){
    this->playerScore += score;
      if(this->playerScore < 0) {
        this-> playerScore = 0;
    }
}

string Player::getPlayerName(){
    return this->playerName;
}

int Player::getPlayerScore(){
    return this->playerScore;
}

int Player::getPlayerID(){
    return this->playerID;
}

int Player::isBotorHuman(){
    return this->botOrHuman;
}

