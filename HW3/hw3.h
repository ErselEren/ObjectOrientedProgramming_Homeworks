using namespace std;

enum class Cells{block, peg, empty};
enum class Direction{up,down,left,right};

class PegSolitaire{
    public:
        class Cell{
            public:
                Cell();
                Cell(Cells type);
                int row,column;
                Cells cell_type;  
        };
        PegSolitaire();
        PegSolitaire(int board_type, string name);
        int compareBoards(PegSolitaire& other);
        void print_board() const;
        void game_process();
        void setRowAndColumn(int r,int c);
        void load_game(string& board_choiceStr);
        void CreateAndFillBoard();
        void setBoard_choice();
        static int AllPegs(vector<PegSolitaire> &objVector);
        static void print_menu();
        int getPegCounter();
        int getEmptyCounter();
        int getBoard_choice() const;
        void setBoard_name(string name);
        void playGame();
        void CreateSquare(string input);
        string getBoard_name() const;
        char getGamemode()const;
        int row, column;
        Direction direction;
        int getScore();
    private:
        void countPegs() const;
        void save_game();
        bool SingleStep();
        bool isGameFinished() const;
        bool isGameFinished6() const;
        bool find_valid_move(int i,int j) const;
        bool find_valid_move6(int row, int column) const;
        bool check_position()const;
        bool check_direction();
        bool check_direction6();
        void play(string input);
        void play(Direction direction);
        void play();
        bool check_endgame() const;
        void peg_status();
        vector<PegSolitaire> Games;
        vector<vector<Cell>> board;
        string board_name;
        int board_choice;
        char gamemode;
        static int AllPegNumber;
        int pegCounter,emptyCounter;
};

void game_control(vector<PegSolitaire> &objVector);
void create_new_game(string& input,vector<PegSolitaire>& objVector);
void split(string& str);