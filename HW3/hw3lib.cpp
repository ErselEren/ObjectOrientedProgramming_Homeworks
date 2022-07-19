/*
      When program is executed, there isn't any active games. In the menu, user has to create a new game from 6 default board
    or load previous or arbitrary games from txt files. Both create and load functions make a new container for new game object in 2D PegSolitaire vector.
      All games have its own names. For example when player inputs "create game1", name of the created game is "game1". So at the saving procedure, name of the file will be game1.txt
    Therefore, at the loading procedure, when player inputs "load game2.txt", name of the loaded game will be "game2". 
      There is no save function in main menu.Save function is available in game_process function which makes movement.
    All games are stored in 2D PegSolitaire vector. In this way, user can create, play and changes games as much as he/she wants.
      Player can jump into another created or loaded games by inputting "change boardname".
      If user input 'playGame', after choosing board type, game will be played randomly until end of the game.
      There is also compare option by inputting 2 board names.

    In game_process function; player can input position and direction and make movement.
    If user press 'enter' key, program makes single random movement.
    If the user don't want to continue current game, writes 'return' and goes to main menu where he/she can create or load new game or change game.
    If the user don't save the game and returns main menu, game will be in 2D PegSolitaire object and playable as long as program runs.

    There is 3 arbitrary boards in folder.
*/


#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include "hw3.h"

using namespace std;

int PegSolitaire::AllPegNumber = 0;

//gets input and calls function according to it
void PegSolitaire::game_process(){
    string movement;
    
    if(check_endgame()==0){
        cerr << "!-This game is over-!\n";
        return;
    }
    
    while(1){ //printing menu
        cout << " >----------------------------------------------------------------------<\n";
        cout << " > Enter position and direction(D4-R - Column 4, Row 4, Direction Right)<\n";                           
        cout << " >              Press 'Enter' to process single step                    <\n";
        cout << " >              Write 'status' to show number of cells                  <\n";
        cout << " >                   Write 'save' to save game                          <\n";
        cout << " >                  Write 'return' to go to menu                        <\n";
        cout << " >----------------------------------------------------------------------<\n>>>";
        getline(cin,movement); 

        //user want to make movement by entering movement
        if(movement[0]<='Z' && movement[0]>='A' && movement[1]>='1' && movement[1]<='9' 
          &&(movement[3]=='U'||movement[3]=='D'||movement[3]=='R'||movement[3]=='L')){
            play(movement);
            if(check_endgame()==0){
                cout <<"Score is : "<<getScore();
                return;  
            } 
        }
        else if(movement[0]=='\0'){ //user want to make random move
            play();
            if(check_endgame()==0){
                cout <<"Score is : "<<getScore();
                return;
            } 
        }
        else if(movement.compare(0,8,"status")==0){ //user want to finish game by random and auto
            peg_status();
            cout << "There are "<<getPegCounter()<<" peg in board.\n";
            cout << "There are "<<getEmptyCounter()<<" empty in board.\n";
            cout << getEmptyCounter()-1<<" taken from board.\n";
        }
        else if(movement.compare(0,6,"return")==0) return; //returning to menu
        else if(movement.compare(0,4,"save")==0) save_game();//save game into txt file
        else cerr <<"\nINVALID COMMAND\n";
    }    
}

//gets input and calls function according to it
void game_control(vector<PegSolitaire> &objVector){
    string input,input1;
    int board_choice;
    while(1){
        PegSolitaire::print_menu();
        getline(cin,input);
        if(input.compare(0,4,"load")==0){ //loading game from txt
            if(input[4]!='\0'){
                //creating new object and pushing it back into vector
                //setting board name with input without '.txt'
                input.erase(input.find_first_of('.'),4); //erases first 4 char when it finds '.' char  
                create_new_game(input,objVector);
                input.append(".txt");
                objVector.back().load_game(input);
                objVector.back().print_board();
                objVector.back().game_process();
            }
        }
        else if(input.compare(0,6,"create")==0){
            if(input[6]!='\0'){
                //creating new object and pushing it back into vector
                create_new_game(input,objVector);
                objVector.back().setBoard_choice();
                objVector.back().CreateAndFillBoard();
                cin.ignore(100,'\n');
                objVector.back().print_board();
                objVector.back().game_process();
            }
        }
        else if(input.compare(0,6,"change")==0){
            if(input[6]!='\0'){
                split(input);
                for(int i=0;i<objVector.size();i++) //searches games
                    if(objVector[i].getBoard_name()==input){
                        objVector.back().print_board();
                        objVector[i].game_process();
                        break;
                    }
            }    
        }
        else if(input.compare(0,7,"compare")==0){
            if(input[7]!='\0'){
                //user enters two names, then it searches these games and compare number of pegs
                //then calls comparing function as member function of first game by passing second game.
                string board1,board2;
                cout <<"Enter name of the first board : ";
                cin >> board1;
                cout<<"Enter name of the second board : ";
                cin >> board2;
                for(int i=0;i<objVector.size();i++){
                    if(board1.compare(0,objVector[i].getBoard_name().length(),objVector[i].getBoard_name())){ //find first game
                        for(int j=0;j<objVector.size();j++){
                            if(board2.compare(0,objVector[j].getBoard_name().length(),objVector[j].getBoard_name())){ //find second game
                                //compareBoards returns 1, -1 and 0(for equality)
                                if(objVector[i].compareBoards(objVector[j])==0)
                                    cout << "These two boards have same amount of pegs\n";
                                else if(objVector[i].compareBoards(objVector[j])==1)
                                    cout<<objVector[i].getBoard_name()<<" has more pegs.\n";
                                else if(objVector[i].compareBoards(objVector[j])==-1)
                                    cout<<endl<<objVector[j].getBoard_name()<<" has more pegs.\n";
                            }
                        }
                    }
                }
                cin.ignore(100,'\n');
            }
        }
        else if(input.compare(0,8,"playGame")==0){ 
            if(input[8]!='\0'){
                create_new_game(input,objVector);
                objVector.back().playGame();
                cout << "\nGame over\n";
                cout << "SCORE IS : "<<objVector.back().getScore();
            }
        }
        else if(input.compare(0,4,"pegs")==0) cout <<"All pegs from all active games is =" 
                                                   <<PegSolitaire::AllPegs(objVector)<<endl; //counts all pegs from all active games
        else if(input.compare(0,4,"exit")==0) exit(0); //terminates program
        else cerr << "INVALID COMMAND";
    }
}

//create new object and push it back to vector
void create_new_game(string& input,vector<PegSolitaire> &objVector){  
    split(input);
    PegSolitaire newObject(0,input);
    objVector.push_back(newObject);  
}

//splits strings when it finds space between two words
void split(string& str){
    char seperator = ' ';
    int i=0;
    decltype(i) endIndex = 0;
    //using temp string
    while(i<=str.length()){
        if(str[i]==seperator||i==str.length()){
            endIndex = i;
            string subStr = "";
            subStr.append(str,i+1,str.length()-i-1);
            str = subStr;
            break;
        }
        i++;
    }
}

//printing main menu
void PegSolitaire::print_menu(){
    cout<< "\n>-------------------------MAIN MENU--------------------------------<\n";
    cout<< "> Create a game board__(write 'create boardname'                   <\n";
    cout<< "> Load a game from file__(write 'load boardname.txt')              <\n";
    cout<< "> Change game__(write 'change boardname')                          <\n";
    cout<< "> Compare two games in terms of peg amount__(write 'compare')      <\n";
    cout<< "> Count pegs of all active games__(write 'pegs')                   <\n";
    cout<< "> Autoplay__(write 'playGame boardname')                           <\n";
    cout<< "> Exit program__(write 'exit')                                     <\n";
    cout<< ">------------------------------------------------------------------<\n>>>";
}

//constructors
PegSolitaire::Cell::Cell():cell_type(Cells::block),row(0),column(0){}
PegSolitaire::Cell::Cell(Cells type) : cell_type(type),row(0),column(0){}
PegSolitaire::PegSolitaire(){}
PegSolitaire::PegSolitaire(int board_type, string name):board_choice(board_type),board_name(name){}

//getter and setters
inline int PegSolitaire::getEmptyCounter(){return emptyCounter;}
inline int PegSolitaire::getPegCounter(){return pegCounter;}
inline int PegSolitaire::getBoard_choice()const{return board_choice;}
inline void PegSolitaire::setBoard_name(string name){board_name = name;}
inline string PegSolitaire::getBoard_name() const{return board_name;}
inline char PegSolitaire::getGamemode()const{return gamemode;}

//gets input until valid board type value
void PegSolitaire::setBoard_choice(){ 
    while(1){
        cout<<"Choose board type (1-6) : ";
        cin >> board_choice;
        cout << "\n\nBoard Choice is :"<<board_choice<<endl;
        if(board_choice>=1&&board_choice<=6) break;
        else cerr << "INVALID BOARD TYPE INPUT\n";
    }
}

//setter for row and column variables
void PegSolitaire::setRowAndColumn(int r,int c){
    row = r;
    column = c;
}

void PegSolitaire::peg_status(){
    pegCounter = 0;
    emptyCounter = 0;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
           if(board[i][j].cell_type == Cells::peg) pegCounter++;
           if(board[i][j].cell_type == Cells::empty) emptyCounter++; 
        }   
    }
}

//saving game into txt file
void PegSolitaire::save_game(){
    string file_name;
    file_name = board_name;
    file_name.append(".txt"); //appending '.txt' back to name
    cout << "Name of the file saving-->|"<<file_name<<"|\n\n";
    ofstream textfile (file_name); //opening file 
    if(textfile.is_open()){
        textfile << board_choice<<endl;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){ //writing char by char into file
                if(board[i][j].cell_type==Cells::block) textfile<<'B';
                else if(board[i][j].cell_type==Cells::peg) textfile<<'P';
                else if(board[i][j].cell_type==Cells::empty) textfile<<'E';
            }
            textfile<<'|'<<endl;
        }
        textfile.close();
    }
    else cerr << "FILE COULDN'T OPEN\n";
}

/*it checks if given file name is exist then load board and enters game mode*/
void PegSolitaire::load_game(string& board_choiceStr){
    int j=0;
    board.clear();
    cout << "Name of the file loading|"<<board_choiceStr<<"|\n\n";
    ifstream textfile (board_choiceStr);
    string line;
    if(textfile.is_open()){
        getline(textfile,line);
        if(line[0]=='6') board_choice = 6;
        else board_choice = line[0]-'0';
        while(getline(textfile,line)){
            vector<Cell> temp;
            for(int i=0;i<line.length();i++){
                if(line[i]=='B'){
                    Cell cell(Cells::block);
                    temp.push_back(cell);
                } 
                else if(line[i]=='P'){
                    Cell cell(Cells::peg);
                    temp.push_back(cell);
                } 
                else if(line[i]=='E'){
                    Cell cell(Cells::empty);
                    temp.push_back(cell);
                } 
            }
            board.push_back(temp);
            j++;
        }
        textfile.close();
    }
    else cerr << "FILE IS NOT EXIST";
       
}

//filling 2D vector
void PegSolitaire::CreateAndFillBoard(){
    //here we create 6 different boards and copying into our vector

    Cell CellPeg(Cells::peg);
    Cell CellBlock(Cells::block);
    Cell CellEmpty(Cells::empty);

    if(board_choice==1)
    {
        vector<vector<Cell>> boardE
        {
        {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock},
        {CellBlock,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellBlock},
        {CellPeg,CellPeg,CellPeg,CellEmpty,CellPeg,CellPeg,CellPeg},
        {CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg},
        {CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg},
        {CellBlock,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellBlock},
        {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock}
        };
        //copying into our vector by using push.back function
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
    else if(board_choice==2)
    {
        vector<vector<Cell>> boardE
        {
            {CellBlock,CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg},
            {CellPeg,CellPeg,CellPeg,CellPeg,CellEmpty,CellPeg,CellPeg,CellPeg,CellPeg},
            {CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg},
            {CellBlock,CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
    else if(board_choice==3)
    {
        vector<vector<Cell>> boardE
        {
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg},
            {CellPeg,CellPeg,CellPeg,CellEmpty,CellPeg,CellPeg,CellPeg,CellPeg},
            {CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
    else if(board_choice==4)
    {
        vector<vector<Cell>> boardE
        {
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock},
            {CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg},
            {CellPeg,CellPeg,CellPeg,CellEmpty,CellPeg,CellPeg,CellPeg},
            {CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock},
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i)); 
    }
    else if(board_choice==5)
    {
        vector<vector<Cell>> boardE
        {
            {CellBlock,CellBlock,CellBlock,CellBlock,CellPeg,CellBlock,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock},
            {CellBlock,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellBlock},
            {CellPeg,CellPeg,CellPeg,CellPeg,CellEmpty,CellPeg,CellPeg,CellPeg,CellPeg},
            {CellBlock,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellBlock},
            {CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellBlock,CellPeg,CellPeg,CellPeg,CellBlock,CellBlock,CellBlock},
            {CellBlock,CellBlock,CellBlock,CellBlock,CellPeg,CellBlock,CellBlock,CellBlock,CellBlock}
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
    else if(board_choice==6)
    {
        vector<vector<Cell>> boardE
        {
                {CellBlock,CellBlock,CellBlock,CellBlock,CellEmpty,CellBlock,CellBlock,CellBlock,CellBlock},
                {CellBlock,CellBlock,CellBlock,CellPeg,CellBlock,CellPeg,CellBlock,CellBlock,CellBlock},
                {CellBlock,CellBlock,CellPeg,CellBlock,CellPeg,CellBlock,CellPeg,CellBlock,CellBlock},
                {CellBlock,CellPeg,CellBlock,CellPeg,CellBlock,CellPeg,CellBlock,CellPeg,CellBlock},
                {CellPeg,CellBlock,CellPeg,CellBlock,CellPeg,CellBlock,CellPeg,CellBlock,CellPeg}
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
}

//function for advance single step randomly
void PegSolitaire::play(){
    int randomDirection;
    while(1){
        setRowAndColumn((rand() % board.size() + 1),((rand() % board[0].size())+65));
        randomDirection = rand()%4 + 1;
        if(randomDirection==1) direction = Direction::up;
        else if(randomDirection==2) direction = Direction::down;
        else if(randomDirection==3) direction = Direction::left;
        else if(randomDirection==4) direction = Direction::right;
        if(SingleStep()==1) return;
    }
}

//function for advance single step
void PegSolitaire::play(string input){
    column = input[0];
    row = input[1]-48;
    if(input[3]=='U') direction = Direction::up;
    else if(input[3]=='D') direction = Direction::down;
    else if(input[3]=='L') direction = Direction::left;
    else if(input[3]=='R') direction = Direction::right;
    if(SingleStep()==0)
        cerr << "\nINVALID MOVEMENT INPUT\n";    
}

//function for advance single step
bool PegSolitaire::SingleStep(){
    if(check_position()==1){ // it checks whether chose position is peg or not
        if(board_choice==6){ //condition for 6th board
            if(check_direction6()==1){
                print_board();
                return 1;
            }
        } 
        else{ //other boards
            if(check_direction()==1){
                print_board();
                return 1;
            }
        } 
    }
    else return 0;

    return 0;
}

//plays auto until end of the game
void PegSolitaire::playGame(){
    setBoard_choice();
    CreateAndFillBoard();
    cin.ignore(100,'\n');
    print_board();
    while(1){
        if(getBoard_choice()==6){
            if(isGameFinished6()==0) return;
        }
        else{
            if(isGameFinished()==0) return;
        }
        play();
    }
}

//returns 1 if choosen cell is peg
bool PegSolitaire::check_position() const{
    //we get letter and number which is position. Then return 1 if that position is peg, else it return 0
    if(row>=1&&row<=board.size()&&column>='A'&&column<=('A'+board[0].size()))
        if(board[row-1][column-'A'].cell_type == Cells::peg)
            return 1;  

    return 0; 
}

//this function makes movement if it's valid 
bool PegSolitaire::check_direction(){
    /* 1-Up , 2-Down, 3-Left, 4-Right  */
    //first it check size of the board. It shouldnt exceed borders
    //then it trys to find peg and empty Cells in where it will move
    //if all conditions are true, it changes Cellss and returns 1, else returns 0
    
    if(direction==Direction::up){ //up  
        if((row-3)>=0){
            if((board[row-2][column-'A'].cell_type==Cells::peg)&&board[row-3][column-'A'].cell_type==Cells::empty){
                board[row-2][column-'A'].cell_type = Cells::empty;
                board[row-1][column-'A'].cell_type = Cells::empty;
                board[row-3][column-'A'].cell_type = Cells::peg;
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else if(direction==Direction::down){ //down
        if((row+2)<=board.size()){
            if((board[row][column-'A'].cell_type==Cells::peg)&&board[row+1][column-'A'].cell_type==Cells::empty){
                board[row-1][column-'A'].cell_type = Cells::empty;
                board[row][column-'A'].cell_type = Cells::empty;
                board[row+1][column-'A'].cell_type = Cells::peg;
                return 1;
            }
            else return 0;  
        }
        else return 0;  
    }
    else if(direction==Direction::left){ //left
        if((column-'A'-2)>=0){
            if((board[row-1][column-'A'-2].cell_type==Cells::empty)&&board[row-1][column-'A'-1].cell_type==Cells::peg){
                board[row-1][column-'A'].cell_type = Cells::empty;
                board[row-1][column-'A'-2].cell_type = Cells::peg;
                board[row-1][column-'A'-1].cell_type = Cells::empty;
                return 1;
            }
            else return 0; 
        }
        else return 0;
    }
    else if(direction==Direction::right){ //right
        if((column-'A'+2)<=board[0].size()){
            if((board[row-1][column-'A'+2].cell_type==Cells::empty)&&board[row-1][column-'A'+1].cell_type==Cells::peg){
                board[row-1][column-'A'].cell_type = Cells::empty;
                board[row-1][column-'A'+1].cell_type = Cells::empty;
                board[row-1][column-'A'+2].cell_type = Cells::peg;
                return 1;
            }
            else return 0;
        }
        else return 0; 
    }

    return 0;

}

//this function makes movement if it's valid 
bool PegSolitaire::check_direction6(){
    //1-Upper left cross, 2-Upper right cross, 3-Left, 4-Right, 5-Lower left cross, 6-Lower right cross 
    //first it controls if it reaches border of board
    //then search peg and empty Cells in that direction
    int flag = 0;
    char choice;
    if(direction==Direction::up){ 
        //sol üst çapraz ve sağ üst çapraza bak, ikisi de oluyorsa kullanıcıya sor. bir tanesi oluyorsa onu seç bilgisayar oynuyorsa random at
        if((row-3>=0) && (column-2-'A')>=0 && board[row-3][column-2-'A'].cell_type==Cells::empty && board[row-2][column-1-'A'].cell_type==Cells::peg ){
            flag = 1;
        }
        if((row-3>=0)&&(column+2-'A')<board[0].size()&&(board[row-3][column+2-'A'].cell_type==Cells::empty) && (board[row-2][column+1-'A'].cell_type==Cells::peg)){
            if(flag==1) flag = 2;
            else flag = 3;
        }
        
        if(flag==0){
            return 0;
        }
        else if(flag==1){
            //sol çapraz
            board[row-1][column-'A'].cell_type = Cells::empty;
            board[row-2][column-'A'-1].cell_type = Cells::empty;
            board[row-3][column-'A'-2].cell_type = Cells::peg;
            return 1;
        }
        else if(flag==3){
            //sağ çapraz
            board[row-1][column-'A'].cell_type = Cells::empty;
            board[row-2][column-'A'+1].cell_type = Cells::empty;
            board[row-3][column-'A'+2].cell_type = Cells::peg;
            return 1;
        }
        else if(flag==2){
            if(getGamemode() == 'c'){ // c is capital of computer which indicated gamemode
                board[row-1][column-'A'].cell_type = Cells::empty;
                board[row-2][column-'A'-1].cell_type = Cells::empty;
                board[row-3][column-'A'-2].cell_type = Cells::peg;
                return 1;
            }
            else{
                cout << "There are 2 possible movement for upwards. L(left) or R(right) : ";
                cin >> choice;
                if(choice=='L'){
                  board[row-1][column-'A'].cell_type = Cells::empty;
                  board[row-2][column-'A'-1].cell_type = Cells::empty;
                  board[row-3][column-'A'-2].cell_type = Cells::peg;
                  return 1;
                }
                else if(choice=='R'){
                  board[row-1][column-'A'].cell_type= Cells::empty;
                  board[row-2][column-'A'+1].cell_type = Cells::empty;
                  board[row-3][column-'A'+2].cell_type = Cells::peg;
                  return 1;
                }
            }
            
        }

    }
    if(direction==Direction::down){
        //sol alt çapraz ve sağ alt çapraza bak
        if(row+2<=board.size() && (column-'A'-2)>=0 && board[row][column-'A'-1].cell_type==Cells::peg && board[row+1][column-'A'-2].cell_type==Cells::empty){
            flag = 1;
        }
        if(row+2<=board.size()&& (column-'A'+2)<board[0].size()&&board[row][column-'A'+1].cell_type==Cells::peg && board[row+1][column-'A'+2].cell_type==Cells::empty){
            if(flag==1) flag = 2;
            else flag = 3;
        }
        if(flag==0){
            return 0;
        }
        else if(flag==1){
            //sol çapraz
            board[row-1][column-'A'].cell_type = Cells::empty;
            board[row][column-'A'-1].cell_type = Cells::empty;
            board[row+1][column-'A'-2].cell_type = Cells::peg;
            return 1;
        }
        else if(flag==3){
            //sağ çapraz
            board[row][column-'A'+1].cell_type = Cells::empty;
            board[row+1][column-'A'+2].cell_type = Cells::peg;
            board[row-1][column-'A'].cell_type = Cells::empty;
            return 1;
        }
        else if(flag==2){
            if(getGamemode()=='c'){
                board[row-1][column-'A'].cell_type = Cells::empty;
                board[row][column-'A'-1].cell_type = Cells::empty;
                board[row+1][column-'A'-2].cell_type = Cells::peg;
                return 1;
            }
            else{
                cout << "There are 2 possible movement for upwards. L(left) or R(right) : ";
                cin >> choice;
                if(choice=='L'){
                  board[row-1][column-'A'].cell_type = Cells::empty;
                  board[row][column-'A'-1].cell_type = Cells::empty;
                  board[row+1][column-'A'-2].cell_type = Cells::peg;
                  return 1;
                }
                else if(choice=='R'){
                  board[row][column-'A'+1].cell_type = Cells::empty;
                  board[row+1][column-'A'+2].cell_type = Cells::peg;
                  board[row-1][column-'A'].cell_type = Cells::empty;
                  return 1;
                }
            }
        }

    }
    //------------------------------------------------------------------------------------------------------------------
    if(direction==Direction::left){
        if(column-4-'A'>=0){
            if((board[row-1][column-'A'-2].cell_type==Cells::peg)&&(board[row-1][column-'A'-4].cell_type==Cells::empty)){
                board[row-1][column-'A'].cell_type = Cells::empty;
                board[row-1][column-'A'-2].cell_type = Cells::empty;
                board[row-1][column-'A'-4].cell_type = Cells::peg;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    if(direction==Direction::right){
        if(column+4-'A'<board[0].size()){
           if((board[row-1][column-'A'+2].cell_type==Cells::peg)&&(board[row-1][column-'A'+4].cell_type==Cells::empty)){
                board[row-1][column-'A'].cell_type = Cells::empty;
                board[row-1][column-'A'+2].cell_type = Cells::empty;
                board[row-1][column-'A'+4].cell_type = Cells::peg;
                return 1;
            } 
            return 0;
        }
        return 0;
    }
    //----------------------------------------------------------------------------------------------------------------- 
    return 0;
}

//checks end of the game for board 6
bool PegSolitaire::isGameFinished() const{
    //from upper left corner to lower right corner, it tries to find valid move
    //if it finds, it returns 1, else 0
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[i].size();j++)
            if(board[i][j].cell_type==Cells::peg)
                if(find_valid_move(i,j)==1)
                    return 1;
    return 0;
    
}

//checks end of the game for board 6
bool PegSolitaire::isGameFinished6() const{
    //end game control functions for 6th board
    //from upper left corner to lower right corner, it tries to find valid move
    //if it finds, it returns 1, else 0
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[i].size();j++)
            if(board[i][j].cell_type==Cells::peg)
                if(find_valid_move6(i,j)==1) return 1;
    return 0;
}

//searches valid movement
bool PegSolitaire::find_valid_move(int row, int column) const{
    //it controls respectively right, down, left and upwards and tries to find peg and empty cell in the direction of movement
    //if it finds a valid movement, it returns 1
    if((column+2) < board[0].size()) // checkng right
        if(board[row][column+1].cell_type==Cells::peg && board[row][column+2].cell_type==Cells::empty)
            return 1;

    if((row+2)<board.size()) //checking down
        if(board[row+1][column].cell_type==Cells::peg && board[row+2][column].cell_type==Cells::empty)
            return 1;
        
    if((column-2)>=0) //checking left
        if(board[row][column-1].cell_type==Cells::peg && board[row][column-2].cell_type==Cells::empty)
            return 1;
    
    if((row-2)>=0) //checking upwards
        if(board[row-1][column].cell_type==Cells::peg && board[row-2][column].cell_type==Cells::empty)
            return 1;

    return 0;
}

//searches valid movement for board 6
bool PegSolitaire::find_valid_move6(int row, int column)const{
    //it searchs a valid position. Respectively lower right cross, lower left cross, right, left, upper right, upper left
    //first it controls if it reaches border of board
    //then search peg and empty Cells in that direction
    //if it finds a valid move it returns 1

    if( (column+2 < board[0].size()) && row+2 < board.size()) //checking lower right cross
        if(board[row+1][column+1].cell_type==Cells::peg && board[row+2][column+2].cell_type==Cells::empty)
            return 1;

    if( row+2 < board.size() && column-2>=0 )//checking lower left cross
        if(board[row+1][column-1].cell_type==Cells::peg&&board[row+2][column-2].cell_type==Cells::empty)
            return 1;
        
    if((column+4)<board[0].size()) //checking right
        if(board[row][column+2].cell_type==Cells::peg&&board[row][column+4].cell_type==Cells::empty)
            return 1;
    
    if((column-4)>=0) //checking left
        if(board[row][column-2].cell_type==Cells::peg&&board[row][column-4].cell_type==Cells::empty)
            return 1;
        
    if(column+2 < board[0].size() && row-2>=0) //checking upper right
        if(board[row-1][column+1].cell_type==Cells::peg && board[row-2][column+2].cell_type==Cells::empty)
            return 1;
        
    if(row-2>=0 && column-2 >=0) //checking upper left
        if(board[row-1][column-1].cell_type==Cells::peg&&board[row-2][column-2].cell_type==Cells::empty)
            return 1;

    return 0;
}

//printing board
void PegSolitaire::print_board() const{
    cout<< "Board Name : "<<getBoard_name()<<endl;
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
            if(board[i][j].cell_type == Cells::block) cout<<"  ";
            else if(board[i][j].cell_type == Cells::peg) cout<<"P ";
            else cout<<". ";
        }
        cout << endl;
    }
    cout << endl;
}

//checks end of the game
bool PegSolitaire::check_endgame() const{
    if(getBoard_choice()==6){
        if(isGameFinished6()==0){
            cout << "\n\n--------->GAME OVER<----------\n\n";
            return 0;
        } 
    }
    else{
        if(isGameFinished()==0){
            cout << "\n\n--------->GAME OVER<----------\n\n";
            return 0;
        } 
    }
    return 1;
}

//counts all pegs of all boards
int PegSolitaire::AllPegs(vector<PegSolitaire> &objVector){
    AllPegNumber = 0;
    for(int i=0;i<objVector.size();i++) //passing each boards to function
       objVector[i].countPegs();
    return AllPegNumber;    
}

//counts all pegs of all boards
void PegSolitaire::countPegs() const{
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[i].size();j++)
            if(board[i][j].cell_type == Cells::peg) AllPegNumber++; 
    //AllPegNumber is static        
}

//compares pegs of two boards
int PegSolitaire::compareBoards(PegSolitaire& other){
    pegCounter = 0;
    other.pegCounter = 0;

    //counts pegs of first board
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[i].size();j++)
            if(board[i][j].cell_type == Cells::peg) pegCounter++;

    //counts pegs of other board    
    for(int i=0;i<other.board.size();i++)
        for(int j=0;j<other.board[i].size();j++)
            if(other.board[i][j].cell_type == Cells::peg) other.pegCounter++;
    
    //returns for each probability
    if(pegCounter > other.pegCounter) return 1;     
    else if(pegCounter < other.pegCounter) return -1;
    else return 0;
}

int PegSolitaire::getScore(){
    int peg=0;
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[i].size();j++)
            if(board[i][j].cell_type == Cells::peg) peg++;
    return peg; 
}