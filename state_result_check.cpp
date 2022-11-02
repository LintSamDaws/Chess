#include "state_result_check.h"
#include "state_base.h"
#include "state_exit.h"

#include <iostream>
#include <string>

void StateResultCheck::enter(Board *board) {

    board->toggle();
}

void StateResultCheck::toggle(Board *board) {

    if (board->IsCheckMate()) {
        board->printVecBoardChar();
        std::string winner;
        if (board->GetMoveCount() % 2 == 1) winner = "White";
        else winner = "Black";
        std::cout << "CheckMate! " << winner << " has won.\n";
        board->setState(StateExit::getInstance());
        return;
    }
    if (board->IsStaleMate()) {
        board->printVecBoardChar();
        std::cout << "StaleMate!\nDraw.\n";
        board->setState(StateExit::getInstance());
        return;
    }
    board->setState(StateBase::getInstance());
}

void StateResultCheck::exit(Board *board) {

}

BoardState& StateResultCheck::getInstance() {
    static StateResultCheck singleton;
    return singleton;
}
