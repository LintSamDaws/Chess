#include "board.h"
#include "move.h"
#include "piece.h"
#include "rook.h"
#include "king.h"
#include "main_state_machine.h"

#include <iostream>
#include <string>

// Use Forsyth-Edwards Notation (FEN)

// Starting position
#define starting_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

int Move::enPassant = 0;

int main(int argc, char *argv[])
{
    // Test cases
    std::string testStalemateFEN1 = "5k2/5P2/8/5K2/8/8/8/5Q2";
    int moveNumberStalemate1 = 0;
    std::string testStalemateFEN2 = "6k1/6R1/8/1p2p2p/1P2Pn1P/5Pq1/4r3/7K";
    int moveNumberStalemate2 = 99;
    std::string testStalemateFEN3 = "8/8/8/6K1/8/1Q6/p7/k7";
    int moveNumberStalemate3 = 0;
    std::string testStalemateFEN4 = "kb5R/8/1K6/8/8/8/8/8";
    int moveNumberStalemate4 = 0;

    std::string testCheckmateFEN1 = "1Q6/5pk1/2p3p1/1p2N2p/1b5P/1bn5/1r4P1/2K5";
    int moveNumberCheckmate1 = 1;
    std::string testCheckmateFEN2 = "8/q1n5/8/5K1k/8/8/8/6R1";
    int moveNumberCheckmate2 = 0;

    // Create board 8x8
    Board chess64(8,8,starting_position);
    chess64.printVecBoardChar();
    chess64.setMoveCount(0);
    std::cout << "Move number: " << chess64.GetMoveCount() << "\n";

    King blackKing('k', chess64.FindTheKing('k'));
    King whiteKing('K', chess64.FindTheKing('K'));

    std::string moveString = "";

    while (moveString != "quit") {
        std::cout << "Enter move\n";
        std::cin >> moveString;
        Move move(moveString);
        chess64.makeMove(move);
        chess64.printVecBoardChar();
        std::cout << "Move number: " << chess64.GetMoveCount() << "\n";

        // Check to the King examination
        blackKing.SetCoordinate(chess64.FindTheKing('k'));
        whiteKing.SetCoordinate(chess64.FindTheKing('K'));
        if(whiteKing.IsKingUnderCheck(chess64.getVecBoardChar())) std::cout << "White King is under Check\n";
        if(blackKing.IsKingUnderCheck(chess64.getVecBoardChar())) std::cout << "Black King is under Check\n";

        // Stalemate and Checkmate examination
        if (chess64.IsStaleMate()) {
            std::cout << "^Stalemate^\nThe Game is Over\nDraw\n";
            break;
        }
        if (chess64.IsCheckMate()) {
            std::cout << "^Checkmate^\nThe Game is Over\n";
            break;
        }

        std::cout << chess64.createFEN() << "\n";
    }



//    enum State {
//        Base,
//        MoveCheck,
//        MakeMove,
//        ResultCheck,
//        GameOver
//    };

    return 0;
}
































