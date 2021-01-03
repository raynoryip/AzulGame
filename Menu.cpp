#include <memory>
#include "Types.h"
#include "GameEngine.h"

void runMenu();
int menuDisplay();
int userInput();
void credits();
void aboutThisGame();


void runMenu(){
    int userOption = 0;
    int currentGameState = GAME_RUNNING;
    

    std::unique_ptr<GameEngine> gameEngine = std::make_unique<GameEngine>();

    do{
        cout << "------------------" << endl;
        cout << "Welcome to Azul!" << endl;
        cout << "-------------------\n" << endl;
        cout << "Menu" << endl;
        cout << "----" << endl;
        cout << "1. New Game\n" << "2. Load Game \n" << "3. Credits\n" << "4. About this Game\n" << "5. Quit\n" << endl;
        //check if the user input is within MIN_option 1, and Max_option 5
        userOption = Util::userInput(MIN_OPTION, MAX_OPTION);

        if(userOption==NEWGAME){
            
            currentGameState = gameEngine->start(NEWGAME);
            if(currentGameState==GAME_EXIT) {
                    return;
            }
        }

        if(userOption==LOADGAME){
                currentGameState = gameEngine->start(LOADGAME);
                if(currentGameState==GAME_EXIT){    
                    return;
                }
        }
        else if(userOption==CREDITS){
            credits();
        }
        else if(userOption==ABOUT){
            aboutThisGame();
        }
        else if(userOption==QUIT){
            cout << "Goodbye" << endl;
            return;
        }


        if(currentGameState==GAME_EXIT){
            return;
        }
        cout << endl << endl;
        cout << "**************************" << endl;

    }while(currentGameState==GAME_RUNNING);
}

void credits(){
    
    string credits_wailam = 
    "Name: <Wailam Yip>\nStudent ID: <s3598673>\nEmail: <s3598673@student.rmit.edu.au>";
    string credits_jack = 
    "Name: <Jack Doyle>\nStudent ID: <s3786287>\nEmail: <s3786287@student.rmit.edu.au>";
    string credits_jonathan =
    "Name: <Jonathan Vernik>\nStudent ID: <s3786227>\nEmail: <s3786227@student.rmit.edu.au>";
    cout << "----------------------------------" << endl;
    cout << credits_wailam << endl;
    cout << credits_jack << endl;
    cout << credits_jonathan << endl;
    cout << "----------------------------------" << endl;
}

void aboutThisGame(){
    cout << "Here is the instruction for this game: " << '\n';
    cout << "If there are two users, 5 factories would be used" << '\n';
    cout << "If there are three users, 7 factories would be used" << '\n';
    cout << "If there are four users, 9 factories would be used" << '\n';
    cout << "You can choose whether you want 1 or 2 center factory(s)" << "\n\n\n";
    cout << "In each Turn, if only 1 center factory, the instructions are as follows" << '\n';
    cout << "    e.g. turn  3 D 2" << '\n';
    cout << "Indicates you are [Taking 'D' tile from Factory no.3 into row 2 of your board]" << '\n';
    cout << "For 2 center factories, command are as follows" << '\n';
    cout << "    e.g. turn 3 D 2 1" << '\n';
    cout << "the last number indicates which center factory your excessive tiles are placing." << "\n\n\n";
    cout << "For each round, you could save your game by the following command:" << '\n';
    cout << "    save [ filename ]" << '\n';
    cout << "    e.g. save Azul1 " << "\n\n";
    cout << "You can terminate the game anytime by pressing Ctrl-D (Window). " << '\n';
    cout <<  "[ ---- The end of Instruction ----]\n";
    cout << "Press anykey to back to the main menu...";
    string input;
    std::getline(cin, input);
    return;
}

//The main body
int main(int argc, char *argv[]){

    runMenu();

    return EXIT_SUCCESS;
}
