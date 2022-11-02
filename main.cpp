#include "board.h"
#include "move.h"
#include "piece.h"
#include "rook.h"
#include "king.h"

#include <iostream>
#include <string>

// Use Forsyth-Edwards Notation (FEN)
// Starting position
#define starting_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

int Move::enPassant = 0;

int main(int argc, char *argv[])
{

    Board board(starting_position);
    board.GameOn();

    return 0;
}
































