#include "Util.h"

void Util::stringSlice(std::string originalStr, char delimiter, std::vector<std::string> &vectorToBeModified){
    std::string tempStr;
    int startIndex = 0;
    const unsigned int lastCharIndex = originalStr.length()-1;
    for(unsigned index=0;index<originalStr.length();index++){
        if(originalStr[index]==delimiter || index==lastCharIndex){
            if(index==lastCharIndex){
                tempStr = originalStr.substr(startIndex);
            }else{
                tempStr = originalStr.substr(startIndex, index-startIndex);
            }
            vectorToBeModified.push_back(tempStr);
            startIndex = index+1;
        }
    }
}

int Util::userInput(int min_option, int max_option){  
    int option = 0;  
    string tempInput;  
    do{
        cout << ">";
        std::getline(cin, tempInput);
        if(tempInput.length()==1 && std::all_of(tempInput.begin(), tempInput.end(), ::isdigit)){
            option = std::stoi(tempInput);
            if(option >= min_option && option <= max_option){
                return option;
            }
        }
        cout << "Invalid Input" << '\n';
    }while(true);

    return option;
}

int Util::BotOrHuman(string text){
    string input;
    const string human = "H";
    const string bot = "B";
    do{
        cout << text;
        std::getline(cin, input);
        if(input.compare(bot)==0){
            return BOT_PLAYER;
        }
        else if(input.compare(human)==0){
            return HUMAN_PLAYER;
        }else{
            std::cout << "Invalid Input" << '\n';
        }
    }while(true);
}


