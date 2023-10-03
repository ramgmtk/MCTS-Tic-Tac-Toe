#include <iostream>
#include "board.h"

int main () {
    board b;
    try {
        b.start_game();
    } catch(...) {
        std::cout << "Terminating Game." << std::endl;
    }
    system("pause");
    return 0;
}