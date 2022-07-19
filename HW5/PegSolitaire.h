
//PegSolitaire class decleration with inherit from BoardGame2D

#ifndef PEGSOLITAIRE_H
#define PEGSOLITAIRE_H

#include <vector>
#include "BoardGame2D.h"
using namespace space_BoardGame2D;

namespace space_PegSolitaire
{
    class PegSolitaire : public BoardGame2D
    {
        public:
            PegSolitaire();
            void playUser(string str);
            void print_board()const;
            void playAuto();
            bool SingleStep();
            bool check_position()const;
            bool check_direction();
            bool endGame();
            int boardScore();
            bool find_valid_move(int row, int column);
            void initialize();
            bool decompose_input(string str);

        private:
            bool input_validity;
            vector<vector<int>> board;
            int row,column,direction;
    };

}

#endif