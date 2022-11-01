#include "main_state_machine.h"
#include "board.h"
#include "move.h"

#include <iostream>
#include <string>

MainStateMachine::MainStateMachine() {}

void MainStateMachine::Reset() {
//    SetState(&MainStateMachine::STATE_A);
}

void MainStateMachine::State_Base(Board board, Move move) {

    board.printVecBoardChar();
    std::cout << "Enter move\n";
    std::string moveString;
    std::cin >> moveString;
    Move move(moveString);

}

void MainStateMachine::State_MoveCheckings() {

}

void MainStateMachine::State_MakeMove() {

}

void MainStateMachine::State_ResultCheckings() {

}

void MainStateMachine::State_GameOver() {

}

//MainStateMachine s;
//while (true) {

//}
