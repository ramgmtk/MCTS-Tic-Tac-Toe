#ifndef BOARD_H
#define BOARD_H
#include <unordered_map>
#include <vector>
#include <utility>

using spot = std::pair<unsigned int, unsigned int>;
class board;

//Board State class manages the data ata  given state for a tic tac toe board;
class board_state {
    private:
        //static variable detailing reach tiles relation to one another
        static std::unordered_map<int, std::vector<int>> neighbors;
        //static variable detailing the boards dimensions
        static unsigned int dimension;
        //empty space character
        char empty;
        //the actual board
        char this_board[3][3];
        //calculate board value where index 0 is 'X', 1 is '0'
        int player_value_array[2][9];
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
        void set_space(spot s, bool b);
        //check if a spot is available
        bool check_spot(spot s);
        //check for winner
        bool check_winner();
        //updates the total value of each player on the board.
        //example picking a spot assigns 1 point to that spot, and 1 additional point to unoccupied spots
        void set_value(spot s, bool b);
        //static method for converting a spot into a single numerical value
        static unsigned int spot_to_uint(spot s);
        //static method for converting an int pair to a spot
        static spot int_to_spot(unsigned int i);
        //print
        void print();
        //classes that can freely acces functions
        friend class board;
        friend class mcts_node;

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