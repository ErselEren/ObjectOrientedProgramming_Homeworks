#include "hw2.h"

/*this function manages player game*/
void human_player_game(vector<vector<Cell>> &board,int board_choice,char game_mode){
    int positionNumber, direction;
    char positionLetter;
    /*============================================PLAYER GAME====================================================*/
    while(1){
        print_board(board);
        end_game(board,board_choice); //controlling end of the game and terminate program
        while(1){
                //while loop continues until we made a valid move
                //after getting position, control if position is 'peg'
                //then it checks move in check_direction and make move if it's valid
                get_position(board,positionLetter,positionNumber,direction,game_mode,board_choice);
                if(true == check_position(board,positionLetter,positionNumber)){  
                    if(board_choice==6){
                        if(check_direction_6(board,positionLetter,positionNumber,direction,'p')==1) break;
                        else cerr << "--INVALID MOVEMENT--\n";
                    }
                    else{
                        if(check_direction(board,positionLetter,positionNumber,direction,1,board_choice)==1)break;
                        else cerr << "---INVALID MOVEMENT---\n";
                    }
                }
                else cerr << "---INVALID POSITION---\n";     
        }  
    }
    /*===========================================================================================================*/
}

/*this functions manages computer game with random movements*/
void computer_game(vector<vector<Cell>> &board,int board_choice,char game_mode){
    int positionNumber,direction;
    char positionLetter,next_move;
    string input;
    /*============================================================================================================*/
    while(1){
        print_board(board);
        end_game(board,board_choice);
        cout << "Press 'w' for next step : ";
        getline(cin,input);
        if(input[0]=='w'&&input[1]=='\0'){
            //if game is not ended, program enters while loop
            //while loop iterates until it find valid move
            while(1){
                //generating random numbers for position and direction
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
        else if(input.compare(0,4,"load")==0)
            load_game(input);
        else if(input.compare(0,4,"save")==0)
            save_game(board,input,game_mode,board_choice);
        else cerr <<"INVALID COMMAND\n";
        /*============================================================================================================*/
    }
}

/*filling vector by chosen board*/
void CreateAndFillBoard(vector<vector<Cell>> &board, int board_choice){
    
    //here we create 6 different boards and copying into our vector
    if(board_choice==1)
    {
        vector<vector<Cell>> boardE
        {
        {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block},
        {Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::block},
        {Cell::peg,Cell::peg,Cell::peg,Cell::empty,Cell::peg,Cell::peg,Cell::peg},
        {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
        {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
        {Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::block},
        {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block}
        };
        //copying into our vector by using push.back function
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
    else if(board_choice==2)
    {
        vector<vector<Cell>> boardE
        {
            {Cell::block,Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
            {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::empty,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
            {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
            {Cell::block,Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
    else if(board_choice==3)
    {
        vector<vector<Cell>> boardE
        {
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
            {Cell::peg,Cell::peg,Cell::peg,Cell::empty,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
            {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
    else if(board_choice==4)
    {
        vector<vector<Cell>> boardE
        {
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block},
            {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
            {Cell::peg,Cell::peg,Cell::peg,Cell::empty,Cell::peg,Cell::peg,Cell::peg},
            {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block},
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i)); 
    }
    else if(board_choice==5)
    {
        vector<vector<Cell>> boardE
        {
            {Cell::block,Cell::block,Cell::block,Cell::block,Cell::peg,Cell::block,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block},
            {Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::block},
            {Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::empty,Cell::peg,Cell::peg,Cell::peg,Cell::peg},
            {Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::block},
            {Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::block,Cell::peg,Cell::peg,Cell::peg,Cell::block,Cell::block,Cell::block},
            {Cell::block,Cell::block,Cell::block,Cell::block,Cell::peg,Cell::block,Cell::block,Cell::block,Cell::block}
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
    else if(board_choice==6)
    {
        vector<vector<Cell>> boardE
        {
                {Cell::block,Cell::block,Cell::block,Cell::block,Cell::empty,Cell::block,Cell::block,Cell::block,Cell::block},
                {Cell::block,Cell::block,Cell::block,Cell::peg,Cell::block,Cell::peg,Cell::block,Cell::block,Cell::block},
                {Cell::block,Cell::block,Cell::peg,Cell::block,Cell::peg,Cell::block,Cell::peg,Cell::block,Cell::block},
                {Cell::block,Cell::peg,Cell::block,Cell::peg,Cell::block,Cell::peg,Cell::block,Cell::peg,Cell::block},
                {Cell::peg,Cell::block,Cell::peg,Cell::block,Cell::peg,Cell::block,Cell::peg,Cell::block,Cell::peg}
        };
        for(size_t i{ };i<boardE.size();i++) board.push_back(boardE.at(i));
    }
}

/*function that prints board*/
void print_board(const vector<vector<Cell>> &board){

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
            if(board[i][j]== Cell::block) cout<<"  ";
            else if(board[i][j]== Cell::peg) cout<<"P ";
            else cout<<". ";
        }
        cout << endl;
    }
    cout << endl;
}

/*it checks if given position corresponds peg*/
bool check_position(const vector<vector<Cell>> &board,char positionLetter,int positionNumber){
    //we get letter and number which is position. Then return 1 if that position is peg, else it return 0
    if(positionNumber>=1&&positionNumber<=board.size()&&positionLetter>='A'&&positionLetter<=('A'+board[0].size()))
        if(board[positionNumber-1][positionLetter-'A']== Cell::peg)
            return 1;  

    return 0; 
}

/*this function checks movement and make movement*/
bool check_direction(vector<vector<Cell>> &board,char positionLetter,int positionNumber,int direction, int gamemode, int board_choice){

    /* 1-Up , 2-Down, 3-Left, 4-Right  */
    //first it check size of the board. It shouldnt exceed borders
    //then it trys to find peg and empty cell in where it will move
    //if all conditions are true, it changes cells and returns 1, else returns 0
    
    if(direction==1){ //up  
        if((positionNumber-3)>=0){
            if((board[positionNumber-2][positionLetter-'A']==Cell::peg)&&board[positionNumber-3][positionLetter-'A']==Cell::empty){
                board[positionNumber-2][positionLetter-'A'] = Cell::empty;
                board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                board[positionNumber-3][positionLetter-'A'] = Cell::peg;
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else if(direction==2){ //down
        if((positionNumber+2)<=board.size()){
            if((board[positionNumber][positionLetter-'A']==Cell::peg)&&board[positionNumber+1][positionLetter-'A']==Cell::empty){
                board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                board[positionNumber][positionLetter-'A'] = Cell::empty;
                board[positionNumber+1][positionLetter-'A'] = Cell::peg;
                return 1;
            }
            else return 0;  
        }
        else return 0;  
    }
    else if(direction==3){ //left
        if((positionLetter-'A'-2)>=0){
            if((board[positionNumber-1][positionLetter-'A'-2]==Cell::empty)&&board[positionNumber-1][positionLetter-'A'-1]==Cell::peg){
                board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                board[positionNumber-1][positionLetter-'A'-2] = Cell::peg;
                board[positionNumber-1][positionLetter-'A'-1] = Cell::empty;
                return 1;
            }
            else return 0; 
        }
        else return 0;
    }
    else if(direction==4){ //right
        if((positionLetter-'A'+2)<=board[0].size()){
            if((board[positionNumber-1][positionLetter-'A'+2]==Cell::empty)&&board[positionNumber-1][positionLetter-'A'+1]==Cell::peg){
                board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                board[positionNumber-1][positionLetter-'A'+1] = Cell::empty;
                board[positionNumber-1][positionLetter-'A'+2] = Cell::peg;
                return 1;
            }
            else return 0;
        }
        else return 0; 
    }

    return 0;
}  

/*reads movement from console and decomposes it*/ 
void get_position(vector<vector<Cell>> &board,char& positionLetter,int& positionNumber, int& direction,char game_mode,int board_choice){ 
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
            else cerr << "---INVALID DIRECTION---\n";
            
        }
        else if(movement.compare(0,4,"load")==0)
            load_game(movement);
        else if(movement.compare(0,4,"save")==0)
            save_game(board,movement,game_mode,board_choice);
        else cerr << "--1-INVALID POSITION---\n";
    }
}

/*checks end of the game*/
bool isGameFinished(const vector<vector<Cell>> &board){
    //from upper left corner to lower right corner, it tries to find valid move
    //if it finds, it returns 1, else 0
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[i].size();j++)
            if(board[i][j]==Cell::peg)
                if(find_valid_move(board,i,j)==1)
                    return 1;
    return 0;
}

/*it search valid move for around every peg*/
bool find_valid_move(const vector<vector<Cell>> &board, int row, int column){
    //it controls respectively right, down, left and upwards and tries to find peg and empty cell in the direction of movement
    //if it finds a valid movement, it returns 1
    if((column+2) < board[0].size()) // checkng right
        if(board[row][column+1]==Cell::peg && board[row][column+2]==Cell::empty)
            return 1;

    if((row+2)<board.size()) //checking down
        if(board[row+1][column]==Cell::peg&&board[row+2][column]==Cell::empty)
            return 1;
        
    if((column-2)>=0) //checking left
        if(board[row][column-1]==Cell::peg&&board[row][column-2]==Cell::empty)
            return 1;
    
    if((row-2)>=0) //checking upwards
        if(board[row-1][column]==Cell::peg&&board[row-2][column]==Cell::empty)
            return 1;

    return 0;
}

/*checks end of the game for 6th board*/
bool isGameFinished_6(const vector<vector<Cell>> &board){
    //end game control functions for 6th board
    //from upper left corner to lower right corner, it tries to find valid move
    //if it finds, it returns 1, else 0
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[i].size();j++)
            if(board[i][j]==Cell::peg)
                if(find_valid_move_6(board,i,j)==1) return 1;
    return 0;
}

/*this function checks movement and make movement for 6th board*/
bool check_direction_6(vector<vector<Cell>> &board,char positionLetter,int positionNumber,int direction, char m){
    //1-Upper left cross, 2-Upper right cross, 3-Left, 4-Right, 5-Lower left cross, 6-Lower right cross 
    //first it controls if it reaches border of board
    //then search peg and empty cell in that direction
    int flag = 0;
    char choice;
    if(direction==1){ 
        //sol üst çapraz ve sağ üst çapraza bak, ikisi de oluyorsa kullanıcıya sor. bir tanesi oluyorsa onu seç bilgisayar oynuyorsa random at
        if((positionNumber-3>=0) && (positionLetter-2-'A')>=0 && board[positionNumber-3][positionLetter-2-'A']==Cell::empty && board[positionNumber-2][positionLetter-1-'A']==Cell::peg ){
            flag = 1;
        }
        if((positionNumber-3>=0)&&(positionLetter+2-'A')<board[0].size()&&(board[positionNumber-3][positionLetter+2-'A']==Cell::empty) && (board[positionNumber-2][positionLetter+1-'A']==Cell::peg)){
            if(flag==1) flag = 2;
            else flag = 3;
        }
        
        if(flag==0){
            return 0;
        }
        else if(flag==1){
            //sol çapraz
            board[positionNumber-1][positionLetter-'A'] = Cell::empty;
            board[positionNumber-2][positionLetter-'A'-1] = Cell::empty;
            board[positionNumber-3][positionLetter-'A'-2] = Cell::peg;
            return 1;
        }
        else if(flag==3){
            //sağ çapraz
            board[positionNumber-1][positionLetter-'A'] = Cell::empty;
            board[positionNumber-2][positionLetter-'A'+1] = Cell::empty;
            board[positionNumber-3][positionLetter-'A'+2] = Cell::peg;
            return 1;
        }
        else if(flag==2){
            if(m == 'c'){ // c is capital of computer which indicated gamemode
                board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                board[positionNumber-2][positionLetter-'A'-1] = Cell::empty;
                board[positionNumber-3][positionLetter-'A'-2] = Cell::peg;
                return 1;
            }
            else{
                cout << "There are 2 possible movement for upwards. L(left) or R(right) : ";
                cin >> choice;
                if(choice=='L'){
                  board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                  board[positionNumber-2][positionLetter-'A'-1] = Cell::empty;
                  board[positionNumber-3][positionLetter-'A'-2] = Cell::peg;
                  return 1;
                }
                else if(choice=='R'){
                  board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                  board[positionNumber-2][positionLetter-'A'+1] = Cell::empty;
                  board[positionNumber-3][positionLetter-'A'+2] = Cell::peg;
                  return 1;
                }
            }
            
        }

    }
    if(direction==2){
        //sol alt çapraz ve sağ alt çapraza bak
        if(positionNumber+2<=board.size() && (positionLetter-'A'-2)>=0 && board[positionNumber][positionLetter-'A'-1]==Cell::peg && board[positionNumber+1][positionLetter-'A'-2]==Cell::empty){
            flag = 1;
        }
        if(positionNumber+2<=board.size()&& (positionLetter-'A'+2)<board[0].size()&&board[positionNumber][positionLetter-'A'+1]==Cell::peg && board[positionNumber+1][positionLetter-'A'+2]==Cell::empty){
            if(flag==1) flag = 2;
            else flag = 3;
        }
        if(flag==0){
            return 0;
        }
        else if(flag==1){
            //sol çapraz
            board[positionNumber-1][positionLetter-'A'] = Cell::empty;
            board[positionNumber][positionLetter-'A'-1] = Cell::empty;
            board[positionNumber+1][positionLetter-'A'-2] = Cell::peg;
            return 1;
        }
        else if(flag==3){
            //sağ çapraz
            board[positionNumber][positionLetter-'A'+1] = Cell::empty;
            board[positionNumber+1][positionLetter-'A'+2] = Cell::peg;
            board[positionNumber-1][positionLetter-'A'] = Cell::empty;
            return 1;
        }
        else if(flag==2){
            if(m=='c'){
                board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                board[positionNumber][positionLetter-'A'-1] = Cell::empty;
                board[positionNumber+1][positionLetter-'A'-2] = Cell::peg;
                return 1;
            }
            else{
                cout << "There are 2 possible movement for upwards. L(left) or R(right) : ";
                cin >> choice;
                if(choice=='L'){
                  board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                  board[positionNumber][positionLetter-'A'-1] = Cell::empty;
                  board[positionNumber+1][positionLetter-'A'-2] = Cell::peg;
                  return 1;
                }
                else if(choice=='R'){
                  board[positionNumber][positionLetter-'A'+1] = Cell::empty;
                  board[positionNumber+1][positionLetter-'A'+2] = Cell::peg;
                  board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                  return 1;
                }
            }
        }

    }
    //------------------------------------------------------------------------------------------------------------------
    if(direction==3){
        if(positionLetter-4-'A'>=0){
            if((board[positionNumber-1][positionLetter-'A'-2]==Cell::peg)&&(board[positionNumber-1][positionLetter-'A'-4]==Cell::empty)){
                board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                board[positionNumber-1][positionLetter-'A'-2] = Cell::empty;
                board[positionNumber-1][positionLetter-'A'-4] = Cell::peg;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    if(direction==4){
        if(positionLetter+4-'A'<board[0].size()){
           if((board[positionNumber-1][positionLetter-'A'+2]==Cell::peg)&&(board[positionNumber-1][positionLetter-'A'+4]==Cell::empty)){
                board[positionNumber-1][positionLetter-'A'] = Cell::empty;
                board[positionNumber-1][positionLetter-'A'+2] = Cell::empty;
                board[positionNumber-1][positionLetter-'A'+4] = Cell::peg;
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
bool find_valid_move_6(const vector<vector<Cell>> &board, int row, int column){
    //it searchs a valid position. Respectively lower right cross, lower left cross, right, left, upper right, upper left
    //first it controls if it reaches border of board
    //then search peg and empty cell in that direction
    //if it finds a valid move it returns 1

    if( (column+2 < board[0].size()) && row+2 < board.size()) //checking lower right cross
        if(board[row+1][column+1]==Cell::peg && board[row+2][column+2]==Cell::empty)
            return 1;

    if( row+2 < board.size() && column-2>=0 )//checking lower left cross
        if(board[row+1][column-1]==Cell::peg&&board[row+2][column-2]==Cell::empty)
            return 1;
        
    if((column+4)<board[0].size()) //checking right
        if(board[row][column+2]==Cell::peg&&board[row][column+4]==Cell::empty)
            return 1;
    
    if((column-4)>=0) //checking left
        if(board[row][column-2]==Cell::peg&&board[row][column-4]==Cell::empty)
            return 1;
        
    if(column+2 < board[0].size() && row-2>=0) //checking upper right
        if(board[row-1][column+1]==Cell::peg && board[row-2][column+2]==Cell::empty)
            return 1;
        
    if(row-2>=0 && column-2 >=0) //checking upper left
        if(board[row-1][column-1]==Cell::peg&&board[row-2][column-2]==Cell::empty)
            return 1;

    return 0;
}

/*after game is ended, it calculates score and prints it*/
void calculate_score(const vector<vector<Cell>> &board){
    int score = 0;
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[i].size(); j++)
           if(board[i][j]==Cell::peg) score++;
    cout << "GAME IS ENDED - SCORE = "<<score<<endl;
}

/*splits load and save words from string*/
void split(string& str){
    char seperator = ' ';
    int i=0;
    decltype(i) currIndex = 0;
    decltype(i) endIndex = 0;
    decltype(i) startIndex = 0;
    //using temp string
    while(i<=str.length()){
        if(str[i]==seperator||i==str.length()){
            endIndex = i;
            string subStr = "";
            subStr.append(str,i+1,str.length()-i-1);
            cout << "Substring |"<<subStr<<"|"<<endl;
            str = subStr;
            break;
        }
        i++;
    }
}

/*it checks if given file name is exist then load board and enters game mode*/
void load_game(string& board_choiceStr){
    int gamemode_choice,board_choice,j=0;
    vector<vector<Cell>> board;
    split(board_choiceStr);

    cout << "Name of the file loading|"<<board_choiceStr<<"|\n\n";
    ifstream textfile (board_choiceStr);
    string line;
    if(textfile.is_open()){
        getline(textfile,line);
        gamemode_choice = line[0];
        if(line[2]=='6') board_choice = 6;
        else board_choice = line[2]-'0';
        while(getline(textfile,line)){
            vector<Cell> temp;
            for(int i=0;i<line.length();i++){
                if(line[i]=='B') temp.push_back(Cell::block);
                else if(line[i]=='P') temp.push_back(Cell::peg);
                else if(line[i]=='E') temp.push_back(Cell::empty);
            }
            board.push_back(temp);
            j++;
        }
        textfile.close();
        if(gamemode_choice=='c')computer_game(board,board_choice,gamemode_choice);
        else human_player_game(board,board_choice,gamemode_choice);
    }
    else cerr << "FILE IS NOT EXIST";
       
}

/*saving current status of board, gamemode and board type informations*/
void save_game(vector<vector<Cell>> &board,string& board_choiceStr,char game_mode,int board_choice=0){
    //after saving, user can continue current game
    split(board_choiceStr);//we get name of the file
    cout << "Name of the file saving-->|"<<board_choiceStr<<"|\n\n";
    ofstream textfile (board_choiceStr); //opening file
         
    if(textfile.is_open()){
        textfile << game_mode <<"|"<<board_choice<<endl;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]==Cell::block) textfile<<'B';
                else if(board[i][j]==Cell::peg) textfile<<'P';
                else if(board[i][j]==Cell::empty) textfile<<'E';
            }
            textfile<<'|'<<endl;
        }
        textfile.close();
    }
    else cerr << "FILE COULDN'T FOUND\n";
}

/*terminates program if game is finished*/
void end_game(const vector<vector<Cell>> &board,int board_choice){
        //controlling end of the game at every successful movement
        if(board_choice==6){
            if(isGameFinished_6(board)==0) 
            {
                calculate_score(board);
                exit(0);
            }  
        }
        else{
            if(isGameFinished(board)==0)
            {
                calculate_score(board);
                exit(0);
            }
        }
}