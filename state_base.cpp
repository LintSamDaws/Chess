#include "state_base.h"
#include "state_move_check.h"

#include <iostream>
#include <string>

void StateBase::enter(Board* board) {
    std::cout << "Game On\n";
    std::cout << "Entering Base\n";
    board->printVecBoardChar();
    std::cout << "Enter the Move\n";
    std::string strMove;
    std::cin >> strMove;
    Move newMove(strMove);
    board->setMove(&newMove);
    board->toggle();
}

void StateBase::toggle(Board* board) {

    std::cout << "Toggling Base\n";
    board->setState(StateMoveCheck::getInstance());
}

void StateBase::exit(Board* board) {

    std::cout << "Exiting Base\n";
    std::cout << "Your move is " << board->GetMove() << "\n";
    std::cout << "Your notation is " << board->GetMove()->GetNotation() << "\n";
}

BoardState& StateBase::getInstance()
{
    static StateBase singleton;
    return singleton;
}
