#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include "hw3.h"

using namespace std;

int main()
{   
    vector<PegSolitaire> objVector;   
    game_control(objVector);
    return 0;
}