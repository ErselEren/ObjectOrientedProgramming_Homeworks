#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include "EightPuzzle.h"
#include "BoardGame2D.h"

#define DELAY_TIME 1

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using namespace space_BoardGame2D;

namespace space_EightPuzzle
{

    //constructor, checks solvability of puzzle,
    EightPuzzle::EightPuzzle() : BoardGame2D(){
        while(1){ //it checks created board is solvable or not
            initialize();
            if(isSolvable()==1)break;      
        }
        emptyRow = 0;
        emptyColumn = 0;
        row = -1;
        column = -1;
        score = 0;
    }

    //decomposes given input into row and column value
    bool EightPuzzle::decompose_input(string str){
        if(str[0]-49>=0&&str[0]-49<3&&str[1]-65>=0&&str[1]-65<3){ //checks input
            if(board[str[0]-49][str[0]-49]!=0){
                setRow(str[0]-49);
                setColumn(str[1]-65);
                return 1;
            } 
        } 
        return 0;
    }

    //counts inverses of each number
    int EightPuzzle::getInvCount(int boardVec[]){
        int count = 0;
        for(int i=0;i<8;i++) //calculates inverses of all numbers
            for(int j=i+1;j<9;j++)
                if( boardVec[j] && boardVec[i] && boardVec[i]>boardVec[j]) count++;

        return count;
    }

    //decides solvability of board
    bool EightPuzzle::isSolvable(){
        //passing 2D vector to 1D int array
        int array[9];
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                array[i*3+j] = board[i][j];

        if(getInvCount(array)%2==0) return 1;
        else return 0;

    }

    //fills vector of puzzle randomly
    void EightPuzzle::initialize(){
        for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    board[i][j]=0; //fills vector with 0

            for(int i=0;i<9;i++){
                row = rand()%3;
                column = rand()%3;
                if(board[row][column]==0) board[row][column] = i; 
                else i--;
            }
    }

    //clears terminal screen and prints boards
    void EightPuzzle::print_board()const{
        cout << "\u001b[2J";
        cout << "\u001b[1000A";
        sleep_until(system_clock::now()+nanoseconds(DELAY_TIME));
       
        //printing letters
        auto letter = 'A';
        cout <<"==========\n"<<"    ";
        for(int i=0;i<board[0].size();i++,letter++)
            cout << letter <<" ";
        cout << endl;

        //printing board and numbers that aligned left
        for(int i=0;i<3;i++){
            cout << i+1 << "| ";
            for(int j=0;j<3;j++)
                if(board[i][j]!=0) cout <<" "<<board[i][j];  
                else cout <<" .";
            cout << endl;    
        }
        cout << endl;

    }

    //decomposes given input then checks direction, if direction returns 1, makes move
    void EightPuzzle::playUser(string str){
        if(decompose_input(str)==1){
            if(check_direction()==1) SingleStep();
            else cerr << "\nThere is no empty cell in board for any direction\n"; 
        }
        else cout << "\nINVALID MOVEMENT";
    }

    //if there is space around chosen cell, registers that position and returns true, else false
    bool EightPuzzle::check_direction(){
        for(int i=0;i<3;i++){
            if(board[i][column]==0){
                emptyRow = i;
                emptyColumn = column;
                return true;
            }
            else if(board[row][i]==0){
                emptyRow = row;
                emptyColumn = i;
                return true;
            }    
        }
        return false;
    }

    //makes move according empty row and column
    bool EightPuzzle::SingleStep(){
        if(emptyRow==row&&column<emptyColumn){//right
            for(int i=emptyColumn;i>column;i--){
                board[row][i]=board[row][i-1];
                board[row][i-1]=0;
            }
        }
        else if(emptyRow==row&&column>emptyColumn){//left
            for(int i=emptyColumn;i<column;i++){
                board[row][i]=board[row][i+1];
                board[row][i+1]=0;
            }
        }
        else if(emptyColumn==column&&row>emptyRow){//up
            for(int i=emptyRow;i<row;i++){
                board[i][column] = board[i+1][column];
                board[i+1][column] = 0;
            }
        }
        else{//down
            for(int i=emptyRow;i>row;i--){
                board[i][column] = board[i-1][column];
                board[i-1][column] = 0;
            }
        }

        return true;
    
    }

    //generate random row and column value and checks direction, if it returns 1, makes move and increase counter
    void EightPuzzle::playAuto(){
        while(1){
            row = rand()%3;
            column = rand()%3;
            if(check_direction()==1){ //returns after movement
                SingleStep();
                print_board();
                score++;
                return;
            }
        }

    }

    //if all numbers are ordered well, game is ended
    bool EightPuzzle::endGame(){
        int index = 1; //index is the control variable
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j] != index){
                    if(i==2&&j==2&&board[i][j]==0) return 0;
                    else return 1;
                } 
                index++;
            }
        }

        return 0;
    }

    //accessors and mutators
    void EightPuzzle::setRow(int r){
        cout << "\n R : "<<r<<endl;
        if(r>=0 && r<3) row = r;
        else {
            row = -1;
            column = -1;
            cout << "\nInvalid row value!";
        }
    }
    void EightPuzzle::setColumn(int c){
        cout << "\n C : "<<c<<endl;
        if(c>=0 && c<3) column = c;
        else{
            row = -1;
            column = -1;
            cout << "\nInvalid colunm value!";
        }
    }
    void EightPuzzle::set_emptyRow(int r){emptyRow = r;}
    void EightPuzzle::set_emptyColumn(int c){emptyColumn = c;}
    int EightPuzzle::getRow()const{return row;}
    int EightPuzzle::getColumn()const{return column;}
    int EightPuzzle::get_emptyRow()const{return emptyRow;}
    int EightPuzzle::get_emptyColumn()const{return emptyColumn;}
    int EightPuzzle::boardScore(){return score;}

}


