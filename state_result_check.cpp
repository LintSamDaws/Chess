#include "state_result_check.h"
#include "state_base.h"
#include "state_exit.h"

#include <iostream>
#include <string>
#include <conio.h>

void StateResultCheck::enter(Board *board) {
    std::cout << "Entering ResultCheck\n";
    getch();
    board->toggle();
}

void StateResultCheck::toggle(Board *board) {
    std::cout << "Toggling ResultCheck\n";
    if (board->IsCheckMate()) {
        board->setState(StateExit::getInstance());
    }
    else {
        board->setState(StateBase::getInstance());
    }
}

void StateResultCheck::exit(Board *board) {
    std::cout << "Exiting ResultCheck\n";
}

BoardState& StateResultCheck::getInstance() {
    static StateResultCheck singleton;
    return singleton;
}
