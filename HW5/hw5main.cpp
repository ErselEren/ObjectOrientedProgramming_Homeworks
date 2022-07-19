#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include "EightPuzzle.h"
#include "PegSolitaire.h"
#include "Klotski.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using namespace space_BoardGame2D;
using namespace space_EightPuzzle;
using namespace space_Klotski;
using namespace space_PegSolitaire;

//creates 2 objects for each class, adds them into vector and plays until end
void test_playVector(){

    PegSolitaire *peg1 = new PegSolitaire;
    PegSolitaire *peg2 = new PegSolitaire;
    EightPuzzle *eight1 = new EightPuzzle;
    EightPuzzle *eight2 = new EightPuzzle;
    Klotski *klot1 = new Klotski;
    Klotski *klot2 = new Klotski;

    vector<BoardGame2D*> games;
    games.push_back(peg1);
    games.push_back(peg2);
    games.push_back(eight1);
    games.push_back(eight2);
    games.push_back(klot1);
    games.push_back(klot2);

    BoardGame2D::playVector(games); //here all functions of each class will be used and tested.
}

void test_playUser(){ //creates one instance of each class end tests playUser function

    PegSolitaire peg;
    string input;
    while(1){
        peg.print_board();
        cout << "\n('---' to exit)Enter input : ";
        cin >> input;
        if(input == "---"|| peg.endGame()==0) break;
        else peg.playUser(input);
    }

    EightPuzzle eight;
    while(1){
        eight.print_board();
        cout << "\n('---' to exit)Enter input : ";
        cin >> input;
        if(input == "---"|| eight.endGame()==0) break;
        else eight.playUser(input);
    }

    Klotski klot;
    while(1){
        klot.print_board();
        cout << "\n('---' to exit)Enter input : ";
        cin >> input;
        if(input == "---" || klot.endGame()==0) break;
        else klot.playUser(input);
    }


    //printing results
    cout << "\nScore of PegSolitaire : "<<peg.boardScore();
    cout << "\nScore of EightPuzzle : "<<eight.boardScore();
    cout << "\nScore of Klotski : "<<klot.boardScore()<<endl;

}

void test_playUser_no_parameter(){
    PegSolitaire peg;
    peg.BoardGame2D::playUser();

    EightPuzzle eight;
    eight.BoardGame2D::playUser();
    
    Klotski klot;
    klot.BoardGame2D::playUser();
}


int main(){
    srand(time(NULL));

    //except playUser function, all other functions will be tested in test_playVector() function
         test_playVector();

    
    //testing playUser(string) function for each class, REMOVE COMMENT
    //      test_playUser_with_parameter();


    //testing playUser() function for each class, REMOVE COMMENT
    //      test_playUser_no_parameter();

    return 0;
}