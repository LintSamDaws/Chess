#include "state_exit.h"

#include <iostream>
#include <string>

void StateExit::enter(Board *board) {

    board->toggle();
}

void StateExit::toggle(Board *board) {
    std::cout << "The Game is Over\n";
}

void StateExit::exit(Board *board) {

}

BoardState& StateExit::getInstance() {
    static StateExit singleton;
    return singleton;
}
