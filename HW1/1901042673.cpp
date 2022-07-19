/*
    In main, first programs asks user to choice board then gamemode.
    Then according to user position and movement input, program first check if that position is peg then it checks direction.
    In computer game, position and movement is random generated.
    As assistant said that user knows just 4 directions, there are only 4 directions that user can select.
    On 6th board, when user want to move up or down and if there are 2 possible ways, user will choose left or right.
    If gamemode is "computer game" and if there 2 possible ways, program will choose left side.
    Movement input should be in X0-Y format like C5-R or H1-D(X letter, 0 number, Y direction).
*/

#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

void print_board(vector<vector<int>> board);
void human_player_game(int board_choice);
void computer_game(int board_choice);
void get_position(vector<vector<int>> board,char &positionLetter,int &positionNumber, int &direction);
void CreateAndFillBoard(vector<vector<int>> &board, int board_choice);
bool check_position(vector<vector<int>> board,char positionLetter,int positionNumber);
bool check_direction(vector<vector<int>> &board,char positionLetter,int positionNumber,int direction, int gamemode, int board_choice);
bool check_direction_6(vector<vector<int>> &board,char positionLetter,int positionNumber,int direction, char m);
bool isGameFinished(vector<vector<int>> board);
bool isGameFinished_6(vector<vector<int>> board);
bool find_valid_move(vector<vector<int>> board, int row, int column);
bool find_valid_move_6(vector<vector<int>> board, int row, int column);
void calculate_score(vector<vector<int>> board);

int main()
{
    srand(time(NULL));
    int board_choice,gamemode_choice;
    enum Cells {block,peg,empty};
    //selecting board type
    cout << "Please enter board type : ";
    while(1){
        cin >> board_choice;
        if(board_choice>=1&&board_choice<=6) break;
        else cout<<"Please enter between 1-6 : ";
    }
    
    //selecting game mode
    cout << " Choose : 1-Human Player Game\n          2-Computer Game\n";
    while(1){
        cin >> gamemode_choice;
        if(gamemode_choice !=1&&gamemode_choice!=2) cout<<"Please enter 1 or 2 : ";
        else break;
    }
         
    if(gamemode_choice == 1){
        human_player_game(board_choice);
    }
    else if(gamemode_choice == 2){
        computer_game(board_choice); 
    }

    return 0;
}

/*this function manages player game*/
void human_player_game(int board_choice){

    vector<vector<int>> board; // declaring empty vector 
    CreateAndFillBoard(board,board_choice); //filling empty vector in function
    int positionNumber, direction;
    char positionLetter;
    /*========================================================================================================*/
    while(1){
        print_board(board);
        
        //controlling end of the game at every successful movement
        if(board_choice==6){
            if(isGameFinished_6(board)==0) 
            {
                calculate_score(board);
                break; 
            }  
        }
        else{
            if(isGameFinished(board)==0)
            {
                calculate_score(board);
                break;
            }
        }
        
        while(1){
                //while loop continues until we made a valid move
                get_position(board,positionLetter,positionNumber,direction); /* */
                if(1 == check_position(board,positionLetter,positionNumber)){  
                    if(board_choice==6){
                        if(check_direction_6(board,positionLetter,positionNumber,direction,'p')==1){
                            break;
                        }
                        else{
                            cout << "--INVALID MOVEMENT--\n";
                        }
                    }
                    else{
                        if(check_direction(board,positionLetter,positionNumber,direction,1,board_choice)==1){
                            break;
                        }
                        else{
                            cout << "---INVALID MOVEMENT---\n";
                        }
                    }
                }
                else{
                    cout << "---INVALID POSITION---\n";
                }
        }  
    }
    /*========================================================================================================*/
}

/*this functions manages computer game with random movements*/
void computer_game(int board_choice){
    // bir tuşa basıldığında geçerli bir hareket yapana kadar dene
    vector<vector<int>> board;
    CreateAndFillBoard(board,board_choice);

    int positionNumber,direction;
    char positionLetter,next_move;
    
    while(1){
        //controlling end of the game at every successful movement
        if(board_choice==6){
            if(isGameFinished_6(board)==0){
                calculate_score(board);
                break;
            }  
        }
        else{
            if(isGameFinished(board)==0)
            {
                calculate_score(board);
                break;
            }  
        }
                while(1){
                    //generating randon numbers for position
                    positionNumber = rand() % board.size();
                    positionLetter = (rand() % board[0].size())+65;
                    direction = rand()%4 + 1;
                    if(check_position(board,positionLetter,positionNumber+1)==1){ // it checks whether chose position is peg or not
                        if(board_choice==6){ //condition for 6th board
                            if(check_direction_6(board,positionLetter,positionNumber+1,direction,'c')==1){
                            print_board(board);
                            break;
                            }
                        } 
                        else{ //other boards
                            if(check_direction(board,positionLetter,positionNumber+1,direction,0,board_choice)==1){
                              print_board(board);
                              break;
                            }
                        } 
                    }
                } 
            
    }
}

/*filling vector by chosen board*/
void CreateAndFillBoard(vector<vector<int>> &board, int board_choice){
    enum Cells {block,peg,empty};
    //here we create 6 different boards and copying into our vector
    
    if(board_choice==1)
    {
        vector<vector<int>> boardE
        {
        {block,block,peg,peg,peg,block,block},
        {block,peg,peg,peg,peg,peg,block},
        {peg,peg,peg,empty,peg,peg,peg},
        {peg,peg,peg,peg,peg,peg,peg},
        {peg,peg,peg,peg,peg,peg,peg},
        {block,peg,peg,peg,peg,peg,block},
        {block,block,peg,peg,peg,block,block}
        };
        
        //copying into our vector by using push.back function
        for(size_t i{ };i<boardE.size();i++)
        {
          board.push_back(boardE.at(i));
        }

    }
    else if(board_choice==2)
    {
        vector<vector<int>> boardE
        {
            {block,block,block,peg,peg,peg,block,block,block},
            {block,block,block,peg,peg,peg,block,block,block},
            {block,block,block,peg,peg,peg,block,block,block},
            {peg,peg,peg,peg,peg,peg,peg,peg,peg},
            {peg,peg,peg,peg,empty,peg,peg,peg,peg},
            {peg,peg,peg,peg,peg,peg,peg,peg,peg},
            {block,block,block,peg,peg,peg,block,block,block},
            {block,block,block,peg,peg,peg,block,block,block},
            {block,block,block,peg,peg,peg,block,block,block},
        };
        for(size_t i{ };i<boardE.size();i++)
        {
          board.push_back(boardE.at(i));
        }
    }
    else if(board_choice==3)
    {
        vector<vector<int>> boardE
        {
            {block,block,peg,peg,peg,block,block,block},
            {block,block,peg,peg,peg,block,block,block},
            {block,block,peg,peg,peg,block,block,block},
            {peg,peg,peg,peg,peg,peg,peg,peg},
            {peg,peg,peg,empty,peg,peg,peg,peg},
            {peg,peg,peg,peg,peg,peg,peg,peg},
            {block,block,peg,peg,peg,block,block,block},
            {block,block,peg,peg,peg,block,block,block},
            {block,block,peg,peg,peg,block,block,block},
        };
        for(size_t i{ };i<boardE.size();i++)
        {
          board.push_back(boardE.at(i));
        }
    }
    else if(board_choice==4)
    {
        vector<vector<int>> boardE
        {
            {block,block,peg,peg,peg,block,block},
            {block,block,peg,peg,peg,block,block},
            {peg,peg,peg,peg,peg,peg,peg},
            {peg,peg,peg,empty,peg,peg,peg},
            {peg,peg,peg,peg,peg,peg,peg},
            {block,block,peg,peg,peg,block,block},
            {block,block,peg,peg,peg,block,block},
        };
        for(size_t i{ };i<boardE.size();i++)
        {
          board.push_back(boardE.at(i));
        }
    }
    else if(board_choice==5)
    {
        vector<vector<int>> boardE
        {
            {block,block,block,block,peg,block,block,block,block},
            {block,block,block,peg,peg,peg,block,block,block},
            {block,block,peg,peg,peg,peg,peg,block,block},
            {block,peg,peg,peg,peg,peg,peg,peg,block},
            {peg,peg,peg,peg,empty,peg,peg,peg,peg},
            {block,peg,peg,peg,peg,peg,peg,peg,block},
            {block,block,peg,peg,peg,peg,peg,block,block},
            {block,block,block,peg,peg,peg,block,block,block},
            {block,block,block,block,peg,block,block,block,block}
        };
        for(size_t i{ };i<boardE.size();i++)
        {
          board.push_back(boardE.at(i));
        }
    }
    else if(board_choice==6)
    {
        vector<vector<int>> boardE
        {
                {block,block,block,block,empty,block,block,block,block},
                {block,block,block,peg,block,peg,block,block,block},
                {block,block,peg,block,peg,block,peg,block,block},
                {block,peg,block,peg,block,peg,block,peg,block},
                {peg,block,peg,block,peg,block,peg,block,peg}
        };
        for(size_t i{ };i<boardE.size();i++)
        {
          board.push_back(boardE.at(i));
        }
    }
}

/*function that prints board*/
void print_board(vector<vector<int>> board){

    char letter = 'A';
    cout <<"=============================\n";
    cout <<"   ";
    
    //print letters on top of board
    for(int i=0;i<board[0].size();i++,letter++)
        cout << letter << " ";

    cout << endl << endl;

    //printing board and numbers for each row
    for(int i=0;i<board.size();i++)
    {
        cout << i+1 << "| ";
        for(int j=0;j<board[i].size(); j++)
        {
          if(board[i][j]==0) cout<<"  ";
          else if(board[i][j]==1) cout<<"P ";
          else cout<<". ";
        }
        cout << endl;
    }
    cout << endl;
}

/*it checks if given position corresponds peg*/
bool check_position(vector<vector<int>> board,char positionLetter,int positionNumber){
    //we get letter and number which is position. Then return 1 if that position is peg, else it return 0
    if(positionNumber>=1&&positionNumber<=board.size()&&positionLetter>='A'&&positionLetter<=('A'+board[0].size())){
        if(board[positionNumber-1][positionLetter-'A']==1){
          return 1;  
        } 
    }
    return 0; 
}

/*this function checks movement and make movement*/
bool check_direction(vector<vector<int>> &board,char positionLetter,int positionNumber,int direction, int gamemode, int board_choice){

    /* 1-Up , 2-Down, 3-Left, 4-Right  */
    //first it check size of the board. It shouldnt exceed borders
    //then it trys to find peg and empty cell in where it will move
    //if all conditions are true, it changes cells and returns 1, else returns 0
    
    if(direction==1){ //up  
        if(board_choice==6){
            //sağ üst ve sol üste bak, bir tane yer varsa ona git, iki tane varsa kullanıcı oynuyorsa sor, bilgisayarsa random
        }
        else{
            if((positionNumber-3)>=0){
                if((board[positionNumber-2][positionLetter-'A']==1)&&board[positionNumber-3][positionLetter-'A']==2){
                  board[positionNumber-2][positionLetter-'A'] = 2;
                  board[positionNumber-1][positionLetter-'A'] = 2;
                  board[positionNumber-3][positionLetter-'A'] = 1;
                  return 1;
            }
                else{
                  return 0;
                }
            }
            else{
                return 0;
            }
        }

        
    }
    else if(direction==2){ //down
        if((positionNumber+2)<=board.size()){
            if((board[positionNumber][positionLetter-'A']==1)&&board[positionNumber+1][positionLetter-'A']==2){
                board[positionNumber-1][positionLetter-'A'] = 2;
                board[positionNumber][positionLetter-'A'] = 2;
                board[positionNumber+1][positionLetter-'A'] = 1;
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
                return 0;
        }
    }
    else if(direction==3){ //left
        if((positionLetter-'A'-2)>=0){
            if((board[positionNumber-1][positionLetter-'A'-2]==2)&&board[positionNumber-1][positionLetter-'A'-1]==1){
                board[positionNumber-1][positionLetter-'A'] = 2;
                board[positionNumber-1][positionLetter-'A'-2] = 1;
                board[positionNumber-1][positionLetter-'A'-1] = 2;
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else if(direction==4){ //right
        if((positionLetter-'A'+2)<=board[0].size()){
            if((board[positionNumber-1][positionLetter-'A'+2]==2)&&board[positionNumber-1][positionLetter-'A'+1]==1){
                board[positionNumber-1][positionLetter-'A'] = 2;
                board[positionNumber-1][positionLetter-'A'+1] = 2;
                board[positionNumber-1][positionLetter-'A'+2] = 1;
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
                return 0;
        }
    }
    else{
        return 0;
    }
    return 0;
}  

/*reads movement from console and decomposes it*/ 
void get_position(vector<vector<int>> board,char& positionLetter,int& positionNumber, int& direction){
    
    /* 1-Up , 2-Down, 3-Left, 4-Right  */
    string movement;
    while(1){
        cout << "Enter movement(letternumber-direction)(ex:B4-R) : ";
        getline(cin, movement);
        if(movement[0]<='Z' && movement[0]>='A' && movement[1]>='1' && movement[1]<='9'){
            positionLetter = movement[0];
            positionNumber = movement[1]-48;
            if(movement[3]=='U'||movement[3]=='D'||movement[3]=='R'||movement[3]=='L'){
                if(movement[3]=='U') direction = 1;
                else if(movement[3]=='D') direction = 2;
                else if(movement[3]=='L') direction = 3;
                else if(movement[3]=='R') direction = 4;
                break;
            }
            else{
                cout << "---INVALID DIRECTION---\n";
            }
        }
        else{
            cout << "--1-INVALID POSITION---\n";
        }
    }
    
}

/*checks end of the game*/
bool isGameFinished(vector<vector<int>> board){

    //from upper left corner to lower right corner, it tries to find valid move
    //if it finds, it returns 1, else 0
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j]==1){
                if(find_valid_move(board,i,j)==1){
                    return 1;
                }
            }
        }
    }
    return 0;
}

/*it search valid move for around every peg*/
bool find_valid_move(vector<vector<int>> board, int row, int column){
    //it controls respectively right, down, left and upwards and tries to find peg and empty cell in the direction of movement
    //if it finds a valid movement, it returns 1
    if((column+2) < board[0].size()){ // checkng right
        if(board[row][column+1]==1 && board[row][column+2]==2){
            return 1;
        }
    }

    if((row+2)<board.size()){ //checking down
        if(board[row+1][column]==1&&board[row+2][column]==2){
            return 1;
        }
    }

    if((column-2)>=0){ //checking left
        if(board[row][column-1]==1&&board[row][column-2]==2){
            return 1;
        }
    }

    if((row-2)>=0){ //checking upwards
        if(board[row-1][column]==1&&board[row-2][column]==2){
            return 1;
        }
    }

    return 0;
}

/*checks end of the game for 6th board*/
bool isGameFinished_6(vector<vector<int>> board){
    //end game control functions for 6th board
    //from upper left corner to lower right corner, it tries to find valid move
    //if it finds, it returns 1, else 0
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j]==1){
                if(find_valid_move_6(board,i,j)==1){
                    return 1;
                }
            }
        }
    } 
    return 0;
}

/*this function checks movement and make movement for 6th board*/
bool check_direction_6(vector<vector<int>> &board,char positionLetter,int positionNumber,int direction, char m){
    //1-Upper left cross, 2-Upper right cross, 3-Left, 4-Right, 5-Lower left cross, 6-Lower right cross 
    //first it controls if it reaches border of board
    //then search peg and empty cell in that direction
    int flag = 0;
    char choice;
    if(direction==1){ 
        //sol üst çapraz ve sağ üst çapraza bak, ikisi de oluyorsa kullanıcıya sor. bir tanesi oluyorsa onu seç bilgisayar oynuyorsa random at
        if((positionNumber-3>=0) && (positionLetter-2-'A')>=0 && board[positionNumber-3][positionLetter-2-'A']==2 && board[positionNumber-2][positionLetter-1-'A']==1 ){
            flag = 1;
        }
        if((positionNumber-3>=0)&&(positionLetter+2-'A')<board[0].size()&&(board[positionNumber-3][positionLetter+2-'A']==2) && (board[positionNumber-2][positionLetter+1-'A']==1)){
            if(flag==1) flag = 2;
            else flag = 3;
        }
        if(flag==0){
            return 0;
        }
        else if(flag==1){
            //sol çapraz
            board[positionNumber-1][positionLetter-'A'] = 2;
            board[positionNumber-2][positionLetter-'A'-1] = 2;
            board[positionNumber-3][positionLetter-'A'-2] = 1;
            return 1;
        }
        else if(flag==3){
            //sağ çapraz
            board[positionNumber-1][positionLetter-'A'] = 2;
            board[positionNumber-2][positionLetter-'A'+1] = 2;
            board[positionNumber-3][positionLetter-'A'+2] = 1;
            return 1;
        }
        else if(flag==2){
            if(m == 'c'){ // c is capital of computer which indicated gamemode
                board[positionNumber-1][positionLetter-'A'] = 2;
                board[positionNumber-2][positionLetter-'A'-1] = 2;
                board[positionNumber-3][positionLetter-'A'-2] = 1;
                return 1;
            }
            else{
                cout << "There are 2 possible movement for upwards. L(left) or R(right) : ";
                cin >> choice;
                if(choice=='L'){
                  board[positionNumber-1][positionLetter-'A'] = 2;
                  board[positionNumber-2][positionLetter-'A'-1] = 2;
                  board[positionNumber-3][positionLetter-'A'-2] = 1;
                  return 1;
                }
                else if(choice=='R'){
                  board[positionNumber-1][positionLetter-'A'] = 2;
                  board[positionNumber-2][positionLetter-'A'+1] = 2;
                  board[positionNumber-3][positionLetter-'A'+2] = 1;
                  return 1;
            }
            }
            
        }

    }
    if(direction==2){
        //sol alt çapraz ve sağ alt çapraza bak
        if(positionNumber+2<=board.size() && (positionLetter-'A'-2)>=0 && board[positionNumber][positionLetter-'A'-1]==1 && board[positionNumber+1][positionLetter-'A'-2]==2){
            flag = 1;
        }
        if(positionNumber+2<=board.size()&& (positionLetter-'A'+2)<board[0].size()&&board[positionNumber][positionLetter-'A'+1]==1 && board[positionNumber+1][positionLetter-'A'+2]==2){
            if(flag==1) flag = 2;
            else flag = 3;
        }
        if(flag==0){
            return 0;
        }
        else if(flag==1){
            //sol çapraz
            board[positionNumber-1][positionLetter-'A'] = 2;
            board[positionNumber][positionLetter-'A'-1] = 2;
            board[positionNumber+1][positionLetter-'A'-2] = 1;
            return 1;
        }
        else if(flag==3){
            //sağ çapraz
            board[positionNumber][positionLetter-'A'+1] = 2;
            board[positionNumber+1][positionLetter-'A'+2] = 1;
            board[positionNumber-1][positionLetter-'A'] = 2;
            return 1;
        }
        else if(flag==2){
            if(m=='c'){
                board[positionNumber-1][positionLetter-'A'] = 2;
                board[positionNumber][positionLetter-'A'-1] = 2;
                board[positionNumber+1][positionLetter-'A'-2] = 1;
                return 1;
            }
            else{
                cout << "There are 2 possible movement for upwards. L(left) or R(right) : ";
                cin >> choice;
                if(choice=='L'){
                  board[positionNumber-1][positionLetter-'A'] = 2;
                  board[positionNumber][positionLetter-'A'-1] = 2;
                  board[positionNumber+1][positionLetter-'A'-2] = 1;
                  return 1;
                }
                else if(choice=='R'){
                  board[positionNumber][positionLetter-'A'+1] = 2;
                  board[positionNumber+1][positionLetter-'A'+2] = 1;
                  board[positionNumber-1][positionLetter-'A'] = 2;
                  return 1;
                }
            }
        }

    }
    //------------------------------------------------------------------------------------------------------------------
    if(direction==3){
        if(positionLetter-4-'A'>=0){
            if((board[positionNumber-1][positionLetter-'A'-2]==1)&&(board[positionNumber-1][positionLetter-'A'-4]==2)){
                board[positionNumber-1][positionLetter-'A'] = 2;
                board[positionNumber-1][positionLetter-'A'-2] = 2;
                board[positionNumber-1][positionLetter-'A'-4] = 1;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    if(direction==4){
        if(positionLetter+4-'A'<board[0].size()){
           if((board[positionNumber-1][positionLetter-'A'+2]==1)&&(board[positionNumber-1][positionLetter-'A'+4]==2)){
                board[positionNumber-1][positionLetter-'A'] = 2;
                board[positionNumber-1][positionLetter-'A'+2] = 2;
                board[positionNumber-1][positionLetter-'A'+4] = 1;
                return 1;
            } 
            return 0;
        }
        return 0;
    }
    //----------------------------------------------------------------------------------------------------------------- 
    return 0;
}

/*it search valid move for around every peg for 6th board*/
bool find_valid_move_6(vector<vector<int>> board, int row, int column){
    //it searchs a valid position. Respectively lower right cross, lower left cross, right, left, upper right, upper left
    //first it controls if it reaches border of board
    //then search peg and empty cell in that direction
    //if it finds a valid move it returns 1

    if( (column+2 < board[0].size()) && row+2 < board.size()){ //checking lower right cross
        if(board[row+1][column+1]==1 && board[row+2][column+2]==2){
            return 1;
        }
    }

    if( row+2 < board.size() && column-2>=0 ){ //checking lower left cross
        if(board[row+1][column-1]==1&&board[row+2][column-2]==2){
            return 1;
        }
    }

    if((column+4)<board[0].size()){ //checking right
        if(board[row][column+2]==1&&board[row][column+4]==2){
            return 1;
        }
    }

    if((column-4)>=0){ //checking left
        if(board[row][column-2]==1&&board[row][column-4]==2){
            return 1;
        }
    }

    if(column+2 < board[0].size() && row-2>=0){ //checking upper right
        if(board[row-1][column+1]==1 && board[row-2][column+2]==2){
            return 1;
        }
    }

    if(row-2>=0 && column-2 >=0){ //checking upper left
        if(board[row-1][column-1]==1&&board[row-2][column-2]==2){
            return 1;
        }
    }

    return 0;
}

/*after game is ended, it calculates score and prints it*/
void calculate_score(vector<vector<int>> board){
    int score = 0;
    for(int i=0;i<board.size();i++)
    {
        for(int j=0;j<board[i].size(); j++)
           if(board[i][j]==1) score++;
    }
    cout << "GAME IS ENDED - SCORE = "<<score<<endl;
}