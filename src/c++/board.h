#ifndef BOARD_H
#define BOARD_H

class board;

//Board State class manages the data ata  given state for a tic tac toe board;
class board_state {
    private:
        //empty space character
        char empty;
        //the actual board
        char this_board[3][3];
        //The remaining spots to be filled
        //The array is used to ekep account of which wpots in the board are open. the index value does
        //necessarily indicate the position on the board. We adjust remaining spots to limit how much of the array we see
        //as all used values bet pushed to the back of the array.
        int remaining_spots_array[9];
        int remaining_spots;

    public:
        //constructors destructores
        board_state();
        board_state(const board_state&);
        board_state& operator=(const board_state&) = delete;
        ~board_state();
        //setter
        void set_space(unsigned int x, unsigned int y, bool b);
        //check if a spot is available
        bool check_spot(unsigned int x, unsigned int y);
        //chec for winner
        bool check_winner();
        //print
        void print();
        friend class board;

};

class board {
    private:
        //!player_choice represens cpu choice
        bool player_choice;
        board_state* my_board;
        bool try_space(unsigned int x, unsigned int y);
        void cpu_turn();
        void player_turn();
    public:
        board();
        board(const board&) = delete;
        board& operator=(const board&) = delete;
        ~board();
        void start_game();
        void display();
        //player try function
        
};
#endif