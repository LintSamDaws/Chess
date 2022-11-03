#include "state_make_move.h"
#include "state_result_check.h"


#include <iostream>
#include <string>


void StateMakeMove::toggle(Board &board) {

    std::cout << "MakeMove\n";
    board.makeMove();

    board.setState(StateResultCheck::getInstance());
}


BoardState& StateMakeMove::getInstance()
{
    static StateMakeMove singleton;
    return singleton;
}
