#include "state_base.h"
#include "state_exit.h"
#include "state_move_check.h"

#include <iostream>
#include <string>

void StateBase::toggle(Board &board) {

    board.printVecBoardChar();
    GetMoveFromUser(board);

    board.setState(StateMoveCheck::getInstance());
}

void StateBase::GetMoveFromUser(Board &board) {
    std::cout << "Enter the Move\n";
    std::string strMove;
    std::cin >> strMove;
    Move newMove(strMove);
    board.setMove(newMove);
}

BoardState& StateBase::getInstance()
{
    static StateBase singleton;
    return singleton;
}
