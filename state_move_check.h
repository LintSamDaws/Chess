#ifndef STATEMOVECHECK_H
#define STATEMOVECHECK_H

#include "board_state.h"
#include "board.h"
#include "move.h"

class StateMoveCheck : public BoardState
{
public:
    void enter(Board* board);
    void toggle(Board* board);
    void exit(Board* board);
    static BoardState& getInstance();

private:
    StateMoveCheck() {}
    StateMoveCheck(const StateMoveCheck& other);
    StateMoveCheck& operator=(const StateMoveCheck& other);
};

#endif // STATEMOVECHECK_H
