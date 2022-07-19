#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include "Klotski.h"
#include "BoardGame2D.h"
#define DELAY_TIME 1


using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using namespace space_BoardGame2D;

namespace space_Klotski
{

    //constructor for Klotski puzzle
    Klotski::Klotski() : BoardGame2D(){
        score = 0;
        initialize();
    }
    //constructor for inner class cell
    Klotski::Klotski_Cell::Klotski_Cell(){}

    //filling vector of puzzle
    void Klotski::initialize(){
        vector<vector<char>> boardE
        {
            {'G','J','J','H'},
            {'G','J','J','H'},
            {'F','E','E','I'},
            {'F','B','C','I'},
            {'A','0','0','D'},
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
        print_board();
    }

    //clears terminal screen and prints board with delay
    void Klotski::print_board()const{
        cout << "\u001b[2J";
        cout << "\u001b[1000A";
        sleep_until(system_clock::now()+nanoseconds(DELAY_TIME));
        cout <<"==========\n"<<"    ";
        cout << endl;
        for(int i=0;i<5;i++){
            for(int j=0;j<4;j++)
                if(board[i][j]!='0') cout <<" "<<board[i][j];  
                else cout <<" .";
            cout << endl;    
        }
        cout << endl;
    }

    //if J blocks are in these positions game is ended
    bool Klotski::endGame(){
        if( board[3][1]=='J'&&board[4][2]=='J') return 0; //game is over
        else return 1; //game is not over
    }

    //clears blocks vector, generates random numbers to chose block and direction
    void Klotski::playAuto(){
        while(1){
            blocks.clear();
            block = rand()%10+65;
            direction = rand()%4+1;
            
            if(check_direction()==1){
                SingleStep();
                print_board();
                score++;
                return;
            }
        }
    }

    //decides random generated direction is valid or not
    void Klotski::find_direction(){
        flag = 0;
        //----------------------------------------------------------------------------------------
        if(direction==1){
            //check down
            for(int k=0;k<blocks.size();k++)
            {
                if(blocks[k].get_cell_row()+1<5)
                {
                    if( board[blocks[k].get_cell_row()+1][blocks[k].get_cell_column()] == block ||
                        board[blocks[k].get_cell_row()+1][blocks[k].get_cell_column()] == '0'){
                        flag = 1;
                    }
                    else{ flag=0; break;}
                }
                else{flag=0; break;}
            }
            if(flag == 1){ valid_direction=1;} 
        }
        else if(direction==2){
            //check up
            for(int k=0;k<blocks.size();k++){
                if(blocks[k].get_cell_row()-1>=0){
                    if(board[blocks[k].get_cell_row()-1][blocks[k].get_cell_column()] == block ||
                    board[blocks[k].get_cell_row()-1][blocks[k].get_cell_column()] == '0'){
                        flag = 1;
                    }
                    else{flag=0;break;}
                }
                else{flag=0;break;}
            }
            if(flag == 1){valid_direction = 2;}     
        }
        //----------------------------------------------------------------------------------------
        else if(direction==3){
            //check left
            for(int k=0;k<blocks.size();k++){
                if(blocks[k].get_cell_column()-1>=0){
                    if(board[blocks[k].get_cell_row()][blocks[k].get_cell_column()-1] == block ||
                    board[blocks[k].get_cell_row()][blocks[k].get_cell_column()-1] == '0'){
                        flag = 1;
                    }
                    else{flag=0; break;}
                }
                else{flag=0; break;}
            }
            if(flag == 1){valid_direction = 3;} 
        }    
        //----------------------------------------------------------------------------------------
        else if(direction==4){
            //check right
            for(int k=0;k<blocks.size();k++){
                if(blocks[k].get_cell_column()+1<4){
                    if(board[blocks[k].get_cell_row()][blocks[k].get_cell_column()+1] == block ||
                    board[blocks[k].get_cell_row()][blocks[k].get_cell_column()+1] == '0'){
                        flag = 1;
                    }
                    else{flag=0; break;}
                }
                else{flag=0; break;}
            }
            if(flag == 1){valid_direction = 4;} 
        }
        //----------------------------------------------------------------------------------------

    }

    //adds all chosen blocks to vector of Klotski_Cell then calls find_direction()
    bool Klotski::check_direction(){
        valid_direction = 0;
        Klotski_Cell cell;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]==block){
                    cell.set_cell_row(i);
                    cell.set_cell_column(j);
                    blocks.push_back(cell);   
                }
            }
        }

        find_direction();
        if(valid_direction!=0) return true;
        else return false;
    }

    //makes move, here there is special conditions for each block type
    bool Klotski::SingleStep(){
        for(int k=0;k<blocks.size();k++){
            
            if(valid_direction==1){//down
                if(board[blocks[k].get_cell_row()+1][blocks[k].get_cell_column()] == block){ //eğer aynı harfe denk geldiyse
                    board[blocks[k].get_cell_row()+1][blocks[k].get_cell_column()] = block; // aşağıdaki bloğa kopyala
                    board[blocks[k].get_cell_row()][blocks[k].get_cell_column()] = '0'; //kendisine 0 ata
                }    
                else{//aynı harf değilse 0'a denk gelmiştir 
                    //A B C D'den biriyse ve 0'a denk geldiyse
                    if(block=='A'||block=='B'||block=='C'||block=='D'||block=='E'){
                        board[blocks[k].get_cell_row()][blocks[k].get_cell_column()] = '0';
                        board[blocks[k].get_cell_row()+1][blocks[k].get_cell_column()] = block;
                    }
                    else board[blocks[k].get_cell_row()+1][blocks[k].get_cell_column()] = block;  
                }
            } 
            
            else if(valid_direction==2){//up
                if(board[blocks[k].get_cell_row()-1][blocks[k].get_cell_column()] == block){ //eğer aynı harfe denk geldiyse
                    board[blocks[k].get_cell_row()-1][blocks[k].get_cell_column()] = block; // yukarıdaki bloğa kopyala
                    board[blocks[k].get_cell_row()][blocks[k].get_cell_column()] = '0'; //kendisine 0 ata
                }    
                else{//aynı harf değilse 0'a denk gelmiştir 
                    //A B C D'den biriyse ve 0'a denk geldiyse
                    if(block=='A'||block=='B'||block=='C'||block=='D'||block=='E'){
                        board[blocks[k].get_cell_row()][blocks[k].get_cell_column()] = '0';
                        board[blocks[k].get_cell_row()-1][blocks[k].get_cell_column()] = block;
                    }
                    else board[blocks[k].get_cell_row()-1][blocks[k].get_cell_column()] = block;  
                }
            }  
            
            else if(valid_direction==3){ //left
                if(board[blocks[k].get_cell_row()][blocks[k].get_cell_column()-1] == block){ //eğer aynı harfe denk geldiyse
                    board[blocks[k].get_cell_row()][blocks[k].get_cell_column()-1] = block; // soldaki bloğa kopyala
                    board[blocks[k].get_cell_row()][blocks[k].get_cell_column()] = '0'; //kendisine 0 ata
                }    
                else{//aynı harf değilse 0'a denk gelmiştir 
                    //A B C D F H I ' dan biriyse ve 0'a denk geldiyse
                    if(block=='A'||block=='B'||block=='C'||block=='D'||block=='G'||block=='F'||block=='H'||block=='I'){
                        board[blocks[k].get_cell_row()][blocks[k].get_cell_column()] = '0';
                        board[blocks[k].get_cell_row()][blocks[k].get_cell_column()-1] = block;
                    }
                    else board[blocks[k].get_cell_row()][blocks[k].get_cell_column()-1] = block;  
                }
            }  
            
            else if(valid_direction==4){ //right
                if(board[blocks[k].get_cell_row()][blocks[k].get_cell_column()+1] == block){ //eğer aynı harfe denk geldiyse
                    board[blocks[k].get_cell_row()][blocks[k].get_cell_column()+1] = block; // sağdaki bloğa kopyala
                    board[blocks[k].get_cell_row()][blocks[k].get_cell_column()] = '0'; //kendisine 0 ata
                }    
                else{//aynı harf değilse 0'a denk gelmiştir 
                    //A B C D F H I ' dan biriyse ve 0'a denk geldiyse
                    if(block=='A'||block=='B'||block=='C'||block=='D'||block=='G'||block=='F'||block=='H'||block=='I'){
                        board[blocks[k].get_cell_row()][blocks[k].get_cell_column()] = '0';
                        board[blocks[k].get_cell_row()][blocks[k].get_cell_column()+1] = block;
                    }
                    else board[blocks[k].get_cell_row()][blocks[k].get_cell_column()+1] = block;  
                }
            }    
        }

        return true;
    }

    //decompose given input 
    void Klotski::playUser(string str){
        blocks.clear();
        if(decompose_input(str)==1){
            if(check_direction()==1){
                SingleStep();
                print_board();
                score++;
            }
            else cerr << "\nINVALID MOVEMENT";
        }
    }

    //decomposes given input into block type and direction
    bool Klotski::decompose_input(string str){
        if(str[0]>='A'&&str[0]<='J'&&(str[2]=='U'||str[2]=='D'||str[2]=='L'||str[2]=='R')){ //controls validity
            setBlock(str[0]);
            if(str[2]=='D') setDirection(1);
            if(str[2]=='U') setDirection(2);
            if(str[2]=='L') setDirection(3);
            if(str[2]=='R') setDirection(4);
            return true;
        }else return false;
    }

    //accessors and mutators
    int Klotski::boardScore(){return score;}
    void Klotski::setDirection(int d){direction = d;}
    void Klotski::setBlock(char c){block = c;}
    char Klotski::getBlock(){return block;}
    int Klotski::getDirection(){return direction;}
    void Klotski::Klotski_Cell::set_cell_row(int r){cell_row = r;}
    void Klotski::Klotski_Cell::set_cell_column(int c){cell_column = c;}
    int Klotski::Klotski_Cell::get_cell_row(){return cell_row;}
    int Klotski::Klotski_Cell::get_cell_column(){return cell_column;}


}