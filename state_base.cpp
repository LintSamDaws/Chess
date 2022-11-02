#include "state_base.h"
#include "state_move_check.h"

#include <iostream>
#include <string>

void StateBase::enter(Board* board) {
    std::cout << "Game On\n";

    board->printVecBoardChar();

    std::cout << "Enter the Move\n";
    std::string strMove;
    std::cin >> strMove;
    Move newMove(strMove);
    board->setMove(&newMove);

    board->toggle();
}

void StateBase::toggle(Board* board) {

    board->setState(StateMoveCheck::getInstance());
}

void StateBase::exit(Board* board) {

}

BoardState& StateBase::getInstance()
{
    static StateBase singleton;
    return singleton;
}
