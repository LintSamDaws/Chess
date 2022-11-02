#ifndef STATEEXIT_H
#define STATEEXIT_H

#include "board_state.h"
#include "board.h"
#include "move.h"

class StateExit : public BoardState
{
public:
    void enter(Board* board);
    void toggle(Board* board);
    void exit(Board* board);
    static BoardState& getInstance();

private:
    StateExit() {}
    StateExit(const StateExit& other);
    StateExit& operator=(const StateExit& other);
};

#endif // STATEEXIT_H
