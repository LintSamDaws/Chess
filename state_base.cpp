#include "state_base.h"
#include "state_exit.h"
#include "state_move_check.h"

#include <iostream>
#include <string>

void StateBase::toggle(Board &board) {

    if (board.GetMoveCount() == 0) {
        std::cout << "Game On\n";
    }
    board.printVecBoardChar();
    std::cout << "Enter the Move\n";
    std::string strMove;
    std::cin >> strMove;
    Move newMove(strMove);
    board.setMove(newMove);

    board.setState(StateMoveCheck::getInstance());
}

BoardState& StateBase::getInstance()
{
    static StateBase singleton;
    return singleton;
}
