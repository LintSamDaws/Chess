#include "state_move_check.h"
#include "state_base.h"
#include "state_make_move.h"
#include "state_exit.h"


#include <iostream>
#include <string>

void StateMoveCheck::toggle(Board &board) {

    std::cout << "MoveCheck\n";

    std::string quitMove = "quit";
    if (board.GetMove().GetNotation() == quitMove) {

        board.SetGameResult(GameResult::ForcedQuit);
        board.setState(StateExit::getInstance());
    }
    else {
        board.setState(StateMakeMove::getInstance());
    }
}

BoardState& StateMoveCheck::getInstance()
{
    static StateMoveCheck singleton;
    return singleton;
}
