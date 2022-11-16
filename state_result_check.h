#ifndef STATERESULTCHECK_H
#define STATERESULTCHECK_H

#include "board_state.h"
#include "board.h"
#include "move.h"

class StateResultCheck : public BoardState
{
public:

    void SwitchState(Board &board);
    static BoardState& getInstance();

private:
    StateResultCheck() {}
    StateResultCheck(const StateResultCheck& other);
    StateResultCheck& operator=(const StateResultCheck& other);
};

#endif // STATERESULTCHECK_H
