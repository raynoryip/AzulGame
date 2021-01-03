#ifndef  UTIL_H
#define  UTIL_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Types.h"

using std::string;
using std::cout;
using std::cin;

class Util{
    public:
        static void stringSlice(std::string originalStr, char delimiter, std::vector<std::string> &vectorToBeModified);
        static int userInput(int min_option, int max_option);
        static int BotOrHuman(string text);
};

#endif // ! UTIL_H