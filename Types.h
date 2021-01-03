#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

#define Red        R
#define Yellow     Y
#define Dark_Blue  B
#define Light_Blue L
#define Black      U

//State mainly used in GameEngine, Menu and Saveload Class 
#define SAVEGAME_FAIL 0
#define SAVEGAME_SUCCESS 1

#define LOADGAME_FAIL 0
#define LOADGAME_SUCCESS 1

#define ENDGAME_EXIT -1

#define EMPTY 0
#define SAVEFILE_EXIST 1
#define SAVEFILE_DOESNT_EXIST 0

#define MAXFACTORIES 5
#define MAXTILES 4
#define PLAYER_0 0
#define PLAYER_1 1
#define PLAYER_2 2
#define PLAYER_3 3

#define GAME_RUNNING 8
#define GAME_EXIT 0

#define MIN_OPTION 1
#define MAX_OPTION 5

#define NEWGAME 1
#define LOADGAME 2
#define CREDITS 3
#define ABOUT 4
#define QUIT 5

#define Board_Height 5
#define Board_Length 5

#define ROUND_CALCULATION 0
#define ENDGAME_CALCULATION 1
#define HUMAN_PLAYER 1
#define BOT_PLAYER 2
