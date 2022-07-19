/*
    Comments from HW1 part-->
        In main, first programs asks user to choice board then gamemode.
        Then according to user position and movement input, program first check if that position is peg then it checks direction.
        In computer game, position and movement is random generated.
        As assistant said that user knows just 4 directions, there are only 4 directions that user can select.
        On 6th board, when user want to move up or down and if there are 2 possible ways, user will choose left or right.
        If gamemode is "computer game" and if there 2 possible ways, program will choose left side.
        Movement input should be in X0-Y format like C5-R or H1-D(X letter, 0 number, Y direction).

    Comments from HW2 part--> 
        When choosing board, user can load saved games but cannot save game at this state of game because there is nothing to save
        After user choosed board, both save and load is available.
        If user save the game after board input, this saved game will be 'computer' game
        Also user can save and load files while giving column and letter input 
        Because we need to save game, computer game progress step by step when user enters 'w' key. So we can save board in this way.
        Also game mode is saving into file. Because of that, if user save game while playing 'player game' , when that file is loaded it will be 'player game' mode
        When getting input, program checks first char of input and second char which should be '\0' char. If its not, it checks load and save command than pass it to 
        split function to get file name from string input.

        There are 3 arbitrary boards in another file which is not for lose original ones.
    
    make
    ./program   
*/

#include "hw2.h" 

int main()
{
    //-------------neccessary declerations----------------
     vector<vector<Cell>> board; // declaring empty vector 
     srand(time(NULL));
     string board_choiceStr, game_modeStr;
     int board_choice,gamemode_choice;
     char seperator = ' ';
    
    //================================BOARD TYPE==================================
    while(1){
        cout << "Enter board type between 1-6 : ";
        getline(cin, board_choiceStr);
        //user enters board number
        if((board_choiceStr[0]=='1'||board_choiceStr[0]=='2'||board_choiceStr[0]=='3'||board_choiceStr[0]=='4'||board_choiceStr[0]=='5'||board_choiceStr[0]=='6')&&board_choiceStr[1]=='\0'){
            board_choice = board_choiceStr[0]-'0';
            CreateAndFillBoard(board,board_choice);
            break;
        }
        else if(board_choiceStr.compare(0,4,"load")==0) //user enters load command
            load_game(board_choiceStr);
        else if(board_choiceStr.compare(0,4,"save")==0) //user enters save command
            cerr << "THERE IS NOTHING TO SAVE FOR NOW\n"; //There is no saving in this step of game
        else cerr <<"INVALID COMMAND\n"; //invalid command
    }

    //================================GAME MODE===================================
    while(1){
        cout << "Enter game mode 'p' for player game, 'c' for computer game : ";
        getline(cin,game_modeStr);
        if(game_modeStr[0]=='p'&&game_modeStr[1]=='\0') human_player_game(board,board_choice,game_modeStr[0]);
        else if(game_modeStr[0]=='c'&&game_modeStr[1]=='\0') computer_game(board,board_choice,game_modeStr[0]);
        else if(game_modeStr.compare(0,4,"load")==0)
            load_game(game_modeStr);
        else if(game_modeStr.compare(0,4,"save")==0)
            save_game(board,game_modeStr,'c',board_choice);
        else cerr <<"INVALID COMMAND\n";
    }

    return 0;
    //--------------------------------END OF MAIN---------------------------------
}