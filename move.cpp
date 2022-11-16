#include "move.h"

#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& stream, const Move move) {
    stream << move.activePiece << move.startCoordinate << '-' << move.finishCoordinate;
    return stream;
}

Move::Move() {}
Move::Move(std::string move) {

    notation_ = move;
    // The Move is Castling
    // move="O-O" or move="O-O-O" for White // move="o-o" or move="o-o-o" for Black
    // activePiece = 'O' for White or 'o' for Black
    // startCoordinate is the coordinate of the King
    // finishCoordinate is the coordinate of the Rook
    if (move[0] == 'O' || move[0] == 'o') {
        if (move == "O-O") {
            activePiece = 'O';
            startCoordinate = 60;
            finishCoordinate = 63;
        } else
        if (move == "O-O-O") {
            activePiece = 'O';
            startCoordinate = 60;
            finishCoordinate = 56;
        } else
        if (move == "o-o") {
            activePiece = 'o';
            startCoordinate = 4;
            finishCoordinate = 7;
        } else
        if (move == "o-o-o") {
            activePiece = 'o';
            startCoordinate = 4;
            finishCoordinate = 0;
        } else std::cout << "Such Castling is Invalid\n";
    }
    // The Move is NOT the Castling
    else {
            // Gets move[5] type of Qe8-e5

        activePiece = move[0];

            // Converts "a1", "e4" type of coord to integer in range 0 to 63
        switch (move[1]) {
        case 'a':
            startCoordinate = (8 - move[2] + '0')*8 + 0;
            break;
        case 'b':
            startCoordinate = (8 - move[2] + '0')*8 + 1;
            break;
        case 'c':
            startCoordinate = (8 - move[2] + '0')*8 + 2;
            break;
        case 'd':
            startCoordinate = (8 - move[2] + '0')*8 + 3;
            break;
        case 'e':
            startCoordinate = (8 - move[2] + '0')*8 + 4;
            break;
        case 'f':
            startCoordinate = (8 - move[2] + '0')*8 + 5;
            break;
        case 'g':
            startCoordinate = (8 - move[2] + '0')*8 + 6;
            break;
        case 'h':
            startCoordinate = (8 - move[2] + '0')*8 + 7;
            break;
        default:
            startCoordinate = 0;
            break;
        }

        switch (move[4]) {
        case 'a':
            finishCoordinate = (8 - move[5] + '0')*8 + 0;
            break;
        case 'b':
            finishCoordinate = (8 - move[5] + '0')*8 + 1;
            break;
        case 'c':
            finishCoordinate = (8 - move[5] + '0')*8 + 2;
            break;
        case 'd':
            finishCoordinate = (8 - move[5] + '0')*8 + 3;
            break;
        case 'e':
            finishCoordinate = (8 - move[5] + '0')*8 + 4;
            break;
        case 'f':
            finishCoordinate = (8 - move[5] + '0')*8 + 5;
            break;
        case 'g':
            finishCoordinate = (8 - move[5] + '0')*8 + 6;
            break;
        case 'h':
            finishCoordinate = (8 - move[5] + '0')*8 + 7;
            break;
        default:
            finishCoordinate = 0;
            break;
        }
    }
}

void Move::setActivePiece(char piece) {
    activePiece = piece;
}
void Move::setStartCoordinate(int coordinate) {
    startCoordinate = coordinate;
}
void Move::setFinishCoordinate(int coordinate) {
    finishCoordinate = coordinate;
}
void Move::SetNotation(std::string notation) {
    notation_ = notation;
}

char Move::getActivePiece() const {
    return activePiece;
}
int Move::getStartCoordinate() const {
    return startCoordinate;
}
int Move::getFinishCoordinate() const {
    return finishCoordinate;
}
std::string Move::GetNotation() const {
    return notation_;
}

bool Move::IsLegitNotation(std::string move) const {
    int size = move.size();
    if (move[0] == 'O' || move[0] == 'o' || size == 5) return true;
    else return false;
}










