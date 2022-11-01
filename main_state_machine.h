#ifndef MAINSTATEMACHINE_H
#define MAINSTATEMACHINE_H

#include "board.h"
#include "move.h"

#include <QStateMachine>




class MainStateMachine
{
private:


public:
    MainStateMachine();

    void Reset();
    void State_Base(Board board, Move move);
    void State_MoveCheckings();
    void State_MakeMove();
    void State_ResultCheckings();
    void State_GameOver();
};

#endif // MAINSTATEMACHINE_H
