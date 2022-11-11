#include "state_base.h"
#include "state_exit.h"
#include "state_move_check.h"
#include "notation_reader.h"

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

    // Checking GameLegend notation
    GameLegend gameLegend = board.GetGameLegend();
    // Adds even wrong moves FIX IT
    gameLegend.AddMove(newMove, board.GetMoveCount());
    board.SetGameLegend(gameLegend);

//    // Checking reading from file
//    NotationReader reader;
//    gameLegend.SetFileAddress("1.txt");
//    reader.ReadGameNotationFromFile(gameLegend);
//    board.SetGameLegend(gameLegend);
//    board.GetGameLegend().PrintGameLegendNotation();

//    // Checking saving to file
//    reader.SaveGameNotationToFile(gameLegend);


    board.setState(StateMoveCheck::getInstance());
}

BoardState& StateBase::getInstance()
{
    static StateBase singleton;
    return singleton;
}
