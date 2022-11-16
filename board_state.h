#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "board.h"

class Board;

class BoardState
{
public:
    virtual void SwitchState(Board& board) = 0;
    virtual ~BoardState() {}
};

#endif // BOARDSTATE_H
