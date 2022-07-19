#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

enum class Cell{block, peg, empty};

void print_board(const vector<vector<Cell>> &board);
void human_player_game(vector<vector<Cell>> &board,int board_choice, char game_mode);
void computer_game(vector<vector<Cell>> &board,int board_choice, char game_mode);
void get_position(vector<vector<Cell>> &board,char &positionLetter,int &positionNumber, int &direction,char game_mode,int board_choice);
void CreateAndFillBoard(vector<vector<Cell>> &board, int board_choice);
bool check_position(const vector<vector<Cell>> &board,char positionLetter,int positionNumber);
bool check_direction(vector<vector<Cell>> &board,char positionLetter,int positionNumber,int direction, int gamemode, int board_choice);
bool check_direction_6(vector<vector<Cell>> &board,char positionLetter,int positionNumber,int direction, char m);
bool isGameFinished(const vector<vector<Cell>> &board);
bool isGameFinished_6(const vector<vector<Cell>> &board);
bool find_valid_move(const vector<vector<Cell>> &board, int row, int column);
bool find_valid_move_6(const vector<vector<Cell>> &board, int row, int column);
void end_game(const vector<vector<Cell>> &board,int board_choice);
void calculate_score(const vector<vector<Cell>> &board);
void split(string& str);
void load_game(string& board_choiceStr);
void save_game(vector<vector<Cell>> &board,string& board_choiceStr,char game_mode,int board_choice);
