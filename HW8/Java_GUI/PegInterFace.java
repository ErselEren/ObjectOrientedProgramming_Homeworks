interface PegInterFace{
    boolean check_endgame();
    boolean make_move(int direction);
    void directionButtons(int i, int j);
    void play_game();
    void fill_board();
    void undo();
    void save_game();
    void load_game();
    int getStepCounter();
    void end_of_game();
    int getPegCounter();
    void reset_board();
}
