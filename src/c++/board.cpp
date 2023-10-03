#include <iostream>
#include "board.h"
#include <string>
//BOARD_STATE methods

//construct a base board
board_state::board_state() {
    empty = '#';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->this_board[i][j] = this->empty;
            this->remaining_spots_array[i * 3 + j] = i * 3 + j;
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
void board_state::set_space(unsigned int x, unsigned int y, bool b) {
    char value = b ? 'O' : 'X';
    int new_spot = x * 3 + y;
    this->this_board[x][y] = value;
    for (int i = 0; i < remaining_spots; i++) {
        if (remaining_spots_array[i] == new_spot) {
            remaining_spots_array[i] = remaining_spots_array[remaining_spots - 1];
            remaining_spots -= 1;
            break;
        }
    }
}

//helper function to check if a spot is available in the board
bool board_state::check_spot(unsigned int x, unsigned int y) {
    if (x >= 3 || y >= 3) {
        std::cout << __func__ << ": Bad input provided." << std::endl;
        return false;
    }
    if (this->this_board[x][y] != empty) {
        std::cout << __func__ << ": The space at [" << x << ","
        << y << "] is occupied." << std:: endl;
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
    if (!this->my_board->check_spot(x, y)) return false;
    this->my_board->set_space(x, y, this->player_choice);
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
    int spot = this->my_board->remaining_spots_array[0];
    int x = spot / 3;
    int y = spot % 3;
    this->my_board->set_space(x, y, !this->player_choice);
}

