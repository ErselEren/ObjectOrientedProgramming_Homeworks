
//EightPuzzle class decleration with inherit from BoardGame2D

#ifndef EIGHTPUZZLE_H
#define EIGHTPUZZLE_H

#include <vector>
#include "BoardGame2D.h"

using namespace space_BoardGame2D;

namespace space_EightPuzzle
{

    class EightPuzzle : public BoardGame2D
    {
        public:
            EightPuzzle();
            void initialize();
            void print_board()const;
            void playAuto();
            void playUser(string str);
            bool endGame();
            bool SingleStep();
            bool check_direction();
            bool check_position();
            bool isSolvable();
            bool decompose_input(string str);
            void setRow(int r);
            void setColumn(int c);
            void set_emptyRow(int r);
            void set_emptyColumn(int c);
            int getInvCount(int boardVec[]);
            int getRow()const;
            int getColumn()const;
            int get_emptyRow()const;
            int get_emptyColumn()const;
            int boardScore();
        private:
            bool input_validity;
            int score;
            int emptyRow, emptyColumn;
            int row, column;
            vector<vector<int>> board
            {
                {0,0,0},
                {0,0,0},
                {0,0,0},
            };
    };

}

#endif