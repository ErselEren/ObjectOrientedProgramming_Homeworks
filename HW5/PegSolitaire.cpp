#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include "PegSolitaire.h"
#include "BoardGame2D.h"

#define DELAY_TIME 300 
//by changing this value between 1-1000, set the speed of board

using namespace std;
using namespace std::this_thread;//sub-namespaces for delay
using namespace std::chrono; //sub-namespaces for delay
using namespace space_BoardGame2D;


namespace space_PegSolitaire
{

    //constructor, there is 2 sec delay delibaretly
    PegSolitaire::PegSolitaire():BoardGame2D(){
        cout << "\n--->PegSolitaire<----\n";
        sleep_until(system_clock::now()+seconds(2));
        initialize();
    }

    //getting input and decomposing it into row, column and direction
    bool PegSolitaire::decompose_input(string str){
        //stringi ayrıştır
        row = str[0]-48;
        column = str[1];
        //UP 1, DOWN 2, LEFT 3, RIGHT 4
        if(str[3]=='U') direction = 1;
        if(str[3]=='D') direction = 2;
        if(str[3]=='L') direction = 3;
        if(str[3]=='R') direction = 4;

        cout <<"\nRow : "<<row<<"| Column : "<<column<<" | direction : "<<direction << "| "<<str[3]-65;
        return check_position();
    }

    //fills vector of game
    void PegSolitaire::initialize(){
        vector<vector<int>> boardE
        {
            {0,0,0,1,1,1,0,0,0},
            {0,0,0,1,1,1,0,0,0},
            {0,0,0,1,1,1,0,0,0},
            {1,1,1,1,1,1,1,1,1},
            {1,1,1,1,2,1,1,1,1},
            {1,1,1,1,1,1,1,1,1},
            {0,0,0,1,1,1,0,0,0},
            {0,0,0,1,1,1,0,0,0},
            {0,0,0,1,1,1,0,0,0}, 
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }

    //first decomposes input, if it's succesfull, goes to SingleStep func
    void PegSolitaire::playUser(string str){
        //stringi ayrıştır
        if(decompose_input(str)==1)
            if(SingleStep()==0)cerr <<"\nInvalid Movement!";
    }

    //resets terminal screen and prints board
    void PegSolitaire::print_board()const{
        cout << "\u001b[2J";
        cout << "\u001b[1000A";
        
        auto letter = 'A';
        cout <<"=============================\n"<<"   ";
        //print letters on top of board
        for(int i=0;i<board[0].size();i++,letter++)
            cout << letter <<" ";
        
        cout << endl << endl;

        //printing board and numbers for each row
        for(int i=0;i<board.size();i++)
        {
            cout << i+1 << "| ";
            for(int j=0;j<board[i].size(); j++)
            {
                if(board[i][j] == 0) cout<<"  ";
                else if(board[i][j] == 1) cout<<"P ";
                else cout<<". ";
            }
            cout << endl;
        }
        cout << endl;
    }

    //generates random row, column and direction and tries to make a movement
    void PegSolitaire::playAuto(){
        cout << "\nPLAY AUTO\n";
        int randomDirection;
        while(1){
            row = rand()%board.size()+1;
            column = (rand()%board[0].size())+65;
            direction = rand()%4 + 1;
            if(SingleStep()==1) return;
        }
    }

    //first checks is chosen position is peg, then checks chosen direction
    bool PegSolitaire::SingleStep(){
        if(check_position()==1){ // it checks whether chosen position is peg or not
            if(check_direction()==1){
                sleep_until(system_clock::now()+milliseconds(DELAY_TIME));
                print_board();
                return 1;
            } 
        }
        return 0;
    }

    //checks given position is peg or not
    bool PegSolitaire::check_position() const{
        //we get letter and number which is position. Then return 1 if that position is peg, else it return 0
        if(row>=1&&row<=board.size()&&column>='A'&&column<=('A'+board[0].size()))
            if(board[row-1][column-'A']== 1)
                return 1;  

        return 0; 
    }

    //this function makes movement if it's valid 
    bool PegSolitaire::check_direction(){
        /* 1-Up , 2-Down, 3-Left, 4-Right  */
        //first it check size of the board. It shouldnt exceed borders
        //then it trys to find peg and empty Cells in where it will move
        //if all conditions are true, it changes Cellss and returns 1, else returns 0
        
        if(direction==1){ //up  
            if((row-3)>=0){
                if((board[row-2][column-'A']==1)&&board[row-3][column-'A']==2){
                    board[row-2][column-'A'] =2;
                    board[row-1][column-'A'] =2;
                    board[row-3][column-'A'] = 1;
                    return 1;
                }
                else return 0;
            }
            else return 0;
        }
        else if(direction==2){ //down
            if((row+2)<=board.size()){
                if((board[row][column-'A']==1)&&board[row+1][column-'A']==2){
                    board[row-1][column-'A'] =2;
                    board[row][column-'A'] =2;
                    board[row+1][column-'A'] = 1;
                    return 1;
                }
                else return 0;  
            }
            else return 0;  
        }
        else if(direction==3){ //left
            if((column-'A'-2)>=0){
                if((board[row-1][column-'A'-2]==2)&&board[row-1][column-'A'-1]==1){
                    board[row-1][column-'A'] =2;
                    board[row-1][column-'A'-2] = 1;
                    board[row-1][column-'A'-1] =2;
                    return 1;
                }
                else return 0; 
            }
            else return 0;
        }
        else if(direction==4){ //right
            if((column-'A'+2)<=board[0].size()){
                if((board[row-1][column-'A'+2]==2)&&board[row-1][column-'A'+1]==1){
                    board[row-1][column-'A'] =2;
                    board[row-1][column-'A'+1] =2;
                    board[row-1][column-'A'+2] = 1;
                    return 1;
                }
                else return 0;
            }
            else return 0; 
        }

        return 0;

    }

    //end of the game control, if there isnt any valid move, returns 1
    bool PegSolitaire::endGame(){

        //from upper left corner to lower right corner, it tries to find valid move
        //if it finds, it returns 1, else 0
        for(int i=0;i<board.size();i++)
            for(int j=0;j<board[i].size();j++)
                if(board[i][j]==1)
                    if(find_valid_move(i,j)==1)
                        return 1;
        return 0;

    }

    //searchs valid move in the board
    bool PegSolitaire::find_valid_move(int row, int column){
        //it controls respectively right, down, left and upwards and tries to find peg and empty cell in the direction of movement
        //if it finds a valid movement, it returns 1
        if((column+2) < board[0].size()) // checkng right
            if(board[row][column+1]==1 && board[row][column+2]==2)
                return 1;

        if((row+2)<board.size()) //checking down
            if(board[row+1][column]==1 && board[row+2][column]==2)
                return 1;
            
        if((column-2)>=0) //checking left
            if(board[row][column-1]==1 && board[row][column-2]==2)
                return 1;
        
        if((row-2)>=0) //checking upwards
            if(board[row-1][column]==1 && board[row-2][column]==2)
                return 1;

        return 0;


    }

    //counts all pegs and returns it
    int PegSolitaire::boardScore(){
        int counter = 0;
        for(int i=0;i<board.size();i++) //counting pegs
            for(int j=0;j<board[j].size();j++)
                if(board[i][j]==1) counter++;
            
        if(counter==1) return 0;
        else return counter;

    }

}


