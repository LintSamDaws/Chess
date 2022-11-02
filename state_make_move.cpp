#include "state_make_move.h"
#include "state_result_check.h"


#include <iostream>
#include <string>


void StateMakeMove::enter(Board* board) {

    board->toggle();

}

void StateMakeMove::toggle(Board* board) {

    // To ask Nick
    Move* move = board->GetMove();
    board->makeMove(*move);

    board->setState(StateResultCheck::getInstance());
}

void StateMakeMove::exit(Board* board) {

}

BoardState& StateMakeMove::getInstance()
{
    static StateMakeMove singleton;
    return singleton;
}
