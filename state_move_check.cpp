#include "state_move_check.h"
#include "state_base.h"
#include "state_make_move.h"
#include "state_exit.h"
#include "notation_reader.h"


#include <iostream>
#include <cctype>
#include <string>

void StateMoveCheck::SwitchState(Board &board) {

    std::cout << "MoveCheck\n";

    // Work with quitMove
    std::string quitMove = "quit";
    if (board.GetMove().GetNotation() == quitMove) {

        board.SetGameResult(GameResult::ForcedQuit);
        board.setState(StateExit::getInstance());
        return;
    }

    // New Stuff
    try {
        // Check Move Order
        if (!board.IsRightMoveOrder(board.GetMove()) && isupper(board.GetMove().getActivePiece()))
            throw std::range_error("Wrong Move Order.\nBlack to move!\n");
        if (!board.IsRightMoveOrder(board.GetMove()) && islower(board.GetMove().getActivePiece()))
            throw std::range_error("Wrong Move Order.\nWhite to move!\n");

        // Check Notation Correctness: input move is like "pe2-e4" or "Qa1:a8" or "o-o-o" or "O-O"
        std::vector<char> vecBoard = board.getVecBoardChar();
        if ((board.GetMove().getActivePiece() != vecBoard[board.GetMove().getStartCoordinate()])
                && board.GetMove().getActivePiece() != 'O'
                && board.GetMove().getActivePiece() != 'o')
            throw std::range_error("The Piece is Not There\n");






        // Checking GameLegend notation
        GameLegend gameLegend = board.GetGameLegend();
        // Adds even wrong moves FIX IT
        gameLegend.AddMove(board.GetMove());
        board.SetGameLegend(gameLegend);

//        // Checking reading from file
//        NotationReader reader;
//        gameLegend.SetFileAddress("1.txt");
//        reader.ReadGameNotationFromFile(gameLegend);
//        board.SetGameLegend(gameLegend);
//        board.GetGameLegend().PrintGameLegendNotation();

//        // Checking saving to file
//        NotationReader reader1;
//        reader1.SaveGameNotationToFile(gameLegend);

        board.setState(StateMakeMove::getInstance());
    }

    catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        board.setState(StateBase::getInstance());
    }
}

BoardState& StateMoveCheck::getInstance()
{
    static StateMoveCheck singleton;
    return singleton;
}
