#include <iostream>
#include "board.h"
#include <string>
//BOARD_STATE methods

//declare static variable establishing neighbors of each piece
//credit to user mfontanini https://stackoverflow.com/questions/13464325/static-map-initialization
std::unordered_map<int, std::vector<int>> board_state::neighbors = {
    {
        0, std::vector<int>({4, 1, 3})
    },
    {
        1, std::vector<int>({4, 0, 2})
    },
    {
        2, std::vector<int>({4, 1, 5})
    },
    {
        3, std::vector<int>({4, 0, 6})
    },
    {
        4, std::vector<int>({0, 1, 2, 3, 5, 6, 7, 8})
    },
    {
        5, std::vector<int>({4, 2, 8})
    },
    {
        6, std::vector<int>({4, 3, 7})
    },
    {
        7, std::vector<int>({4, 6, 8})
    },
    {
        8, std::vector<int>({4, 5, 7})
    },
};
//static board_state function
int board_state::spot_to_int(spot s) {
    return s.first * 3 + s.second;
}
//construct a base board
board_state::board_state() {
    empty = '#';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->this_board[i][j] = empty;
            this->remaining_spots_array[i * 3 + j] = i * 3 + j;
            this->player_value_array[0][i * 3 + j] = 0;
            this->player_value_array[1][i * 3 + j] = 0;
        }
    }
    this->remaining_spots = 9;
}

//copy values from the board state
board_state::board_state(const board_state& b) {
    empty = '#';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->this_board[i][j] = b.this_board[i][j];
            this->remaining_spots_array[i * 3 + j] = b.remaining_spots_array[i * 3 + j];
            this->player_value_array[0][i * 3 + j] = b.player_value_array[0][i * 3 + j];
            this->player_value_array[1][i * 3 + j] = b.player_value_array[1][i * 3 + j];
        }
    }
    this->remaining_spots = b.remaining_spots;
}

board_state::~board_state() {
    this->remaining_spots = 9;
}

//sets value and updates the remaining spots
//true boolean corresponds to 'O', false to 'X'
//does not check if a move is valid
void board_state::set_space(spot s, bool b) {
    char value = b ? 'O' : 'X';
    int new_spot = board_state::spot_to_int(s);
    this->this_board[s.first][s.second] = value;
    for (int i = 0; i < remaining_spots; i++) {
        if (remaining_spots_array[i] == new_spot) {
            remaining_spots_array[i] = remaining_spots_array[remaining_spots - 1];
            remaining_spots -= 1;
            break;
        }
    }
    this->set_value(s, b);
}

//helper function to check if a spot is available in the board
bool board_state::check_spot(spot s) {
    if (s.first >= 3 || s.second >= 3) {
        std::cout << __func__ << ": Bad input provided." << std::endl;
        return false;
    }
    if (this->this_board[s.first][s.second] != empty) {
        std::cout << __func__ << ": The space at [" << s.first << ","
        << s.second << "] is occupied." << std:: endl;
        return false;
    }
    return true;
}

//check winner brute force check every possible line.
bool board_state::check_winner() {
    char c = this->this_board[1][1];
    if (c != '#') {
        if (c == this->this_board[1][2] && c == this->this_board[1][0]) return true;
        if (c == this->this_board[0][1] && c == this->this_board[2][1]) return true;
        if (c == this->this_board[0][0] && c == this->this_board[2][2]) return true;
        if (c == this->this_board[0][2] && c == this->this_board[2][0]) return true;
    }
    c = this->this_board[0][0];
    if (c != '#') {
        if (c == this->this_board[0][1] && c == this->this_board[0][2]) return true;
        if (c == this->this_board[1][0] && c == this->this_board[2][0]) return true;
    }
    c = this->this_board[2][2];
    if (c != '#') {
        if (c == this->this_board[2][1] && c == this->this_board[2][0]) return true;
        if (c == this->this_board[1][2] && c == this->this_board[0][2]) return true;
    }
    return false;
}

//update the board control value of each player
//assumed input provided is a legitimate move
//very inefficient
void board_state::set_value(spot s, bool b) {
    int curr_index = b ? 1 : 0;
    int opposing_index = b ? 0 : 1;
    this->player_value_array[curr_index][board_state::spot_to_int(s)] += 1;
    this->player_value_array[opposing_index][board_state::spot_to_int(s)] = -1;
    for (int neighbor : board_state::neighbors[board_state::spot_to_int(s)]) {
        if (this->player_value_array[opposing_index][neighbor] != -1)
            this->player_value_array[curr_index][neighbor] += 1;
    }
}

//output the board
void board_state::print() {
    std::cout << "_|0_1_2_" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << i << "|";
        for (int j = 0; j < 3; j++) {
            std::cout << this->this_board[i][j] << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "--------" << std::endl;
    //output value array forx and 0
    std::cout << "board values for X and O" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "--------" << std::endl;
        for (int j = 0; j < 9; j++) {
            std::cout << this->player_value_array[i][j] << ",";
            if ((j+1) % 3 == 0) std::cout << std::endl;
        }
        std::cout << "--------" << std::endl;
    }

}

//BOARD Methods

//board constructor
board::board() {
    this->my_board = new board_state();
}
//board destructor
board::~board() {
    delete this->my_board;
}

//output the board
void board::display() {
    this->my_board->print();
}

//start game function
//we assume good input
void board::start_game() {
    std::string input;
    std::cout << "Tic Tac Toe" << std::endl;
    std::cout << "O or X" << std::endl;
    std::cout << "Please select your choice: " << std::endl;
    std::cin >> input;
    this->player_choice = input[0] == 'O' ? true : false;
    while (this->my_board->remaining_spots > 0) {
        this->display();
        this->player_turn();
        if (this->my_board->check_winner()) break;
        this->cpu_turn();
        if (this->my_board->check_winner()) break;
    }
    if (this->my_board->check_winner()) std::cout << "We have a winner!" << std::endl;
}

//try setting a value for the player
bool board::try_space(unsigned int x, unsigned int y) {
    if (!this->my_board->check_spot(spot(x, y))) return false;
    this->my_board->set_space(spot(x, y), this->player_choice);
    return true;
}

//method for player action;
//we assume good input for now.
void board::player_turn() {
    std::cout << "Input \'a\' to exit" << std::endl;
    std::cout << "Sample Input:" << std::endl;
    std::cout << "0,0" << std::endl;
    bool valid = false; 
    std::string input;
    while (!valid) {
        std::cout << "Please Select Coordinates: ";
        std::cin >> input;
        if (input[0] == 'a') throw;
        valid = this->try_space(input[0] - 48, input[2] - 48);
    }
}

//method for cpu action
void board::cpu_turn() {
    int s = this->my_board->remaining_spots_array[0];
    int x = s / 3;
    int y = s % 3;
    this->my_board->set_space(spot(x, y), !this->player_choice);
}

