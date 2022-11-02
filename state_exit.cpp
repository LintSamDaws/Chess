#include "state_exit.h"

#include <iostream>
#include <string>
#include <conio.h>

void StateExit::enter(Board *board) {
    std::cout << "Entering Exit\n";
    getch();
    board->toggle();
}

void StateExit::toggle(Board *board) {
    std::cout << "The Game is Over\n";
}

void StateExit::exit(Board *board) {
    std::cout << "Exiting Exit\n";
}

BoardState& StateExit::getInstance() {
    static StateExit singleton;
    return singleton;
}
