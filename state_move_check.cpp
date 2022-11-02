#include "state_move_check.h"
#include "state_base.h"
#include "state_make_move.h"
#include "state_exit.h"


#include <iostream>
#include <string>
#include <conio.h>

void StateMoveCheck::enter(Board* board) {

    std::cout << "Entering MoveCheck\n";
    std::cout << "Your notation is " << board->GetMove()->GetNotation() << "\n";
    getch();
    board->toggle();
}

void StateMoveCheck::toggle(Board* board) {

    std::cout << "Toggling MoveCheck\n";
    if (board->GetMove()->GetNotation() == "quit") {
        board->setState(StateExit::getInstance());
        return;
    }

    if (true) {
        board->setState(StateMakeMove::getInstance());
    }
    else {
        board->setState(StateBase::getInstance());
    }
}

void StateMoveCheck::exit(Board* board) {

    std::cout << "Exiting MoveCheck\n";

}

BoardState& StateMoveCheck::getInstance()
{
    static StateMoveCheck singleton;
    return singleton;
}
