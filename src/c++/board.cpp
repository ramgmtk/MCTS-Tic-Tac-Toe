#include <iostream>
#include "board.h"
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
void board_state::set_value(unsigned int x, unsigned int y, bool b) {
    if (x >= 3 || y >= 3) std::cout << __func__ << ": Bad input provided." << std::endl;
    if (this->this_board[x][y] != empty) std::cout << __func__ << ": The space at [" << x << ","
        << y << "] is occupied." << std:: endl;
    char value = b ? 'O' : 'X';
    int new_spot = x * 3 + y;
    for (int i = 0; i < remaining_spots; i++) {
        if (remaining_spots_array[i] == new_spot) {
            remaining_spots_array[i] = remaining_spots_array[remaining_spots - 1];
            remaining_spots -= 1;
            break;
        }
    }
}

//output the board
void board_state::print() {
    std::cout << "_______" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "|";
        for (int j = 0; j < 3; j++) {
            std::cout << this->this_board[i][j] << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "_______" << std::endl;
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