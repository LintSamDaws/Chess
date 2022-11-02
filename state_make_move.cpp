#include "state_make_move.h"
#include "state_result_check.h"


#include <iostream>
#include <string>
#include <conio.h>


void StateMakeMove::enter(Board* board) {

    std::cout << "Entering MakeMove\n";
    getch();
    board->toggle();

}

void StateMakeMove::toggle(Board* board) {

    std::cout << "Toggling MakeMove\n";
    Move* move = board->GetMove();
    board->makeMove(*move);
    board->setState(StateResultCheck::getInstance());
}

void StateMakeMove::exit(Board* board) {

    std::cout << "Exiting MakeMove\n";

}

BoardState& StateMakeMove::getInstance()
{
    static StateMakeMove singleton;
    return singleton;
}
