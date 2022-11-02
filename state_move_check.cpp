#include "state_move_check.h"
#include "state_base.h"
#include "state_make_move.h"
#include "state_exit.h"


#include <iostream>
#include <string>

void StateMoveCheck::enter(Board* board) {

    board->toggle();
}

void StateMoveCheck::toggle(Board* board) {

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

}

BoardState& StateMoveCheck::getInstance()
{
    static StateMoveCheck singleton;
    return singleton;
}
