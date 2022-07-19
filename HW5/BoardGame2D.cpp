#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include "BoardGame2D.h"
#include "EightPuzzle.h"
#include "PegSolitaire.h"
#include "Klotski.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;


namespace space_BoardGame2D
{
    //constructor
    BoardGame2D::BoardGame2D(){}

    //calls playAuto() function which makes a one step, until end of the game
    void BoardGame2D::playAutoAll(){
        while(1){
            if(this->endGame()==0) break;
            else this->playAuto();
        }

        cout << "\nGAME IS FINISHED\n";
        cout << "Score : "<< this->boardScore()<<endl<<endl;
        sleep_until(system_clock::now()+seconds(3)); //after printing score, waits for 3 seconds
    }

    //gets input from user until game is over. It calls playUser(string) function to related object
    void BoardGame2D::playUser(){
        string input;
        while(1){
            print_board();
            if(this->endGame()==0) break;
            cout << "\nEnter move : ";
            cin >> input;
            playUser(input);
        }
        cout << "\nGAME IS FINISHED\n";
        cout << "Score : "<< this->boardScore();
        sleep_until(system_clock::now()+seconds(3)); //after printing score, waits for 3 seconds
    }

    //plays all games in the vector, in the end prints all scores.
    void BoardGame2D::playVector(vector<BoardGame2D*> vct){
        for(int i=0;i<vct.size();i++) vct[i]->playAutoAll();
          
        for(int i=0;i<vct.size();i++) cout <<endl<< "Score of "<<i+1<<". game : "<<vct[i]->boardScore()<<endl;
    }

    ostream& operator<<(ostream& output, const BoardGame2D& game){
        game.print_board();
        return output;
    }

}