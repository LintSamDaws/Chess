#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "board.h"

class Board;

class BoardState
{
public:
    virtual void enter(Board* board) = 0;
    virtual void toggle(Board* board) = 0;
    virtual void exit(Board* board) = 0;
    virtual ~BoardState() {}
};

#endif // BOARDSTATE_H
