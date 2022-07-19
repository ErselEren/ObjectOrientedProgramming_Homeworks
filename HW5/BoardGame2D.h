
//Base class BoardGame2D decleration

#ifndef BOARDGAME2D_H
#define BOARDGAME2D_H

#include <vector>
#include <iostream>

using namespace std;

namespace space_BoardGame2D
{
    class BoardGame2D
    {
    public:
        BoardGame2D();
        virtual void playUser(string str) =  0;
        virtual void playUser()final;
        static void playVector(vector<BoardGame2D*> vct);
        virtual void playAuto() = 0;
        virtual void playAutoAll() final;
        virtual bool SingleStep() = 0;
        virtual bool endGame() = 0;
        virtual bool find_valid_move(int row, int column){return true;}
        virtual void print_board()const = 0;
        virtual int boardScore() = 0;
        virtual void initialize() = 0;
        virtual bool check_direction() = 0;
        virtual bool decompose_input(string str) = 0;
        friend ostream& operator<<(ostream& output, const BoardGame2D& game);
    };

}

#endif