#ifndef STATEMAKEMOVE_H
#define STATEMAKEMOVE_H

#include "board_state.h"
#include "board.h"
#include "move.h"

class StateMakeMove : public BoardState
{
public:
    void enter(Board* board);
    void toggle(Board* board);
    void exit(Board* board);
    static BoardState& getInstance();

private:
    StateMakeMove() {}
    StateMakeMove(const StateMakeMove& other);
    StateMakeMove& operator=(const StateMakeMove& other);
};

#endif // STATEMAKEMOVE_H
