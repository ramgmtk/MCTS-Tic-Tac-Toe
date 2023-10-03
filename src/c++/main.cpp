#include <iostream>
#include "board.h"

int main () {
    board b;
    try {
        b.start_game();
    } catch(...) {
        std::cout << "Terminating Game." << std::endl;
    }
    return 0;
}