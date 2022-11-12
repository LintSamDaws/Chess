#include "state_result_check.h"
#include "state_base.h"
#include "state_exit.h"

#include <iostream>
#include <string>

void StateResultCheck::toggle(Board &board) {

    std::cout << "ResultCheck\n";

    if (board.IsCheckMate()) {

        if (board.GetGameLegend().GetMoveCount() % 2 == 1) {
            board.SetGameResult(GameResult::WhiteWon);
        }
        else {
            board.SetGameResult(GameResult::BlackWon);
        }
        board.setState(StateExit::getInstance());
        return;
    }
    if (board.IsStaleMate()) {
        board.SetGameResult(GameResult::Draw);
        board.setState(StateExit::getInstance());
        return;
    }
    board.setState(StateBase::getInstance());
}

BoardState& StateResultCheck::getInstance() {
    static StateResultCheck singleton;
    return singleton;
}
