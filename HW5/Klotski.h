//Klotski class decleration with inherit from BoardGame2D

#ifndef KLOTSKI_H
#define KLOTSKI_H

#include <string>
#include <vector>
#include "BoardGame2D.h"

using namespace space_BoardGame2D;

namespace space_Klotski
{

    class Klotski : public BoardGame2D
    {
        public:
            class Klotski_Cell
            {
                public:
                    Klotski_Cell();
                    int get_cell_row();
                    int get_cell_column();
                    void set_cell_row(int);
                    void set_cell_column(int);
                private:
                    int cell_row, cell_column;
            };
            Klotski();
            void initialize();
            int boardScore();
            void print_board()const;
            bool endGame();
            void playAuto();
            bool check_direction();
            bool SingleStep();
            void find_direction();
            void playUser(string str);
            bool decompose_input(string str);
            void setDirection(int);
            void setBlock(char);
            char getBlock();
            int getDirection();
        private:
            int flag;
            char block;
            int score;
            int valid_direction;
            int direction;
            vector<Klotski_Cell> blocks;
            vector<vector<char>> board;
    };

}



#endif