#ifndef STATEEXIT_H
#define STATEEXIT_H

#include "board_state.h"
#include "board.h"
#include "move.h"

class StateExit : public BoardState
{
public:
    void SwitchState(Board& board);
    static BoardState& getInstance();

private:
    StateExit() {}
    StateExit(const StateExit& other);
    StateExit& operator=(const StateExit& other);
};

#endif // STATEEXIT_H
