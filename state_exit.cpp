#include "state_exit.h"

#include <iostream>
#include <string>

void StateExit::toggle(Board &board) {

    std::cout << "Exit\n";

    switch (board.GetGameResult()) {
    case GameResult::ForcedQuit: {
        std::cout << "Force Quitting\n";
        break;
    }
    case GameResult::Draw: {
        board.printVecBoardChar();
        std::cout << "Draw!\n";
        break;
    }
    case GameResult::WhiteWon: {
        board.printVecBoardChar();
        std::cout << "White has won!\n";
        break;
    }
    case GameResult::BlackWon: {
        board.printVecBoardChar();
        std::cout << "Black has won!\n";
        break;
    }
    }
}

BoardState& StateExit::getInstance() {
    static StateExit singleton;
    return singleton;
}
