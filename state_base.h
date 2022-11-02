#ifndef STATEBASE_H
#define STATEBASE_H

#include "board_state.h"
#include "board.h"
#include "move.h"

class StateBase : public BoardState
{
public:
    void enter(Board* board);
    void toggle(Board* board);
    void exit(Board* board);
    static BoardState& getInstance();

private:
    StateBase() {}
    StateBase(const StateBase& other);
    StateBase& operator=(const StateBase& other);
};

#endif // STATEBASE_H
