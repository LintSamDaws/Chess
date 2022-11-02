#include "pawn.h"
#include <iostream>

Pawn::Pawn() {}
Pawn::Pawn(char name, int coordinate) : Piece(name, coordinate) {}

Pawn::~Pawn() {}

std::set<int> Pawn::Threats(const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfThreats;

    // White pawn
    if (isupper(name_)) {

        // LEFT UP threat
        if (coordinate_ % 8 > 0) {
            if (vecBoardChar[coordinate_ - 9] == '0') {
                setOfThreats.insert(coordinate_ - 9);
            }
            else if (islower(vecBoardChar[coordinate_ - 9])) {
                setOfThreats.insert(coordinate_ - 9);
            }
        }

        // RIGHT UP
        if (coordinate_ % 8 < 7) {
            if (vecBoardChar[coordinate_ - 7] == '0') {
                setOfThreats.insert(coordinate_ - 7);
            }
            else if (islower(vecBoardChar[coordinate_ - 7])) {
                setOfThreats.insert(coordinate_ - 7);
            }
        }
    }

    // Black pawn
    if (islower(name_)) {

        // LEFT DOWN
        if (coordinate_ % 8 > 0) {
            if (vecBoardChar[coordinate_ + 7] == '0') {
                setOfThreats.insert(coordinate_ + 7);
            }
            else if (isupper(vecBoardChar[coordinate_ + 7])) {
                setOfThreats.insert(coordinate_ + 7);
            }
        }
        // RIGHT DOWN
        if (coordinate_ % 8 < 7) {
            if (vecBoardChar[coordinate_ + 9] == '0') {
                setOfThreats.insert(coordinate_ + 9);
            }
            else if (isupper(vecBoardChar[coordinate_ + 9])) {
                setOfThreats.insert(coordinate_ + 9);
            }
        }
    }
    return setOfThreats;
}

std::set<int> Pawn::SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const {

    std::set<int> setOfPossibleMoves;

    if (isupper(name_)) {

        if (islower(vecBoardChar[coordinate_ - 9]) && coordinate_ % 8 > 0) {
            setOfPossibleMoves.insert(coordinate_ - 9);
        }

        if (islower(vecBoardChar[coordinate_ - 7]) && coordinate_ % 8 <= 6) {
            setOfPossibleMoves.insert(coordinate_ - 7);
        }

        if (coordinate_ - 9 == enPassant && coordinate_ % 8 > 0) {
            setOfPossibleMoves.insert(coordinate_ - 9);
        }

        if (coordinate_ - 7 == enPassant && coordinate_ % 8 <= 6) {
            setOfPossibleMoves.insert(coordinate_ - 7);
        }



        if (coordinate_ / 8 == 6) {
            if (vecBoardChar[coordinate_ - 8] == '0') {
                setOfPossibleMoves.insert(coordinate_ - 8);
            }
            if ((vecBoardChar[coordinate_ - 8] == '0') && (vecBoardChar[coordinate_ - 16] == '0')) {
                setOfPossibleMoves.insert(coordinate_ - 16);
            }
        }
        else {
            if (vecBoardChar[coordinate_ - 8] == '0') {
                setOfPossibleMoves.insert(coordinate_ - 8);
            }
        }
    }

    if (islower(name_)) {

        if (isupper(vecBoardChar[coordinate_ + 9]) && coordinate_ % 8 <= 6) {
            setOfPossibleMoves.insert(coordinate_ + 9);
        }

        if (isupper(vecBoardChar[coordinate_ + 7]) && coordinate_ % 8 > 0) {
            setOfPossibleMoves.insert(coordinate_ + 7);
        }

        if (coordinate_ + 9 == enPassant && coordinate_ % 8 <= 6) {
            setOfPossibleMoves.insert(coordinate_ + 9);
        }

        if (coordinate_ + 7 == enPassant && coordinate_ % 8 > 0) {
            setOfPossibleMoves.insert(coordinate_ + 7);
        }

        if (coordinate_ / 8 == 1) {
            if (vecBoardChar[coordinate_ + 8] == '0') {
                setOfPossibleMoves.insert(coordinate_ + 8);
            }
            if ((vecBoardChar[coordinate_ + 8] == '0') && (vecBoardChar[coordinate_ + 16] == '0')) {
                setOfPossibleMoves.insert(coordinate_ + 16);
            }
        }
        else {
            if (vecBoardChar[coordinate_ + 8] == '0') {
                setOfPossibleMoves.insert(coordinate_ + 8);
            }
        }
    }
    return setOfPossibleMoves;
}

bool Pawn::IsProperMove(const Move &move, const std::vector<char> &vecBoardChar, int enPassant) const {

    std::set<int> setOfPossibleMoves;
    setOfPossibleMoves = SetOfPossibleMoves(vecBoardChar, enPassant);

    // If finishCoordinate is in the setOfPossibleMove return true;
    if (setOfPossibleMoves.find(move.getFinishCoordinate()) != setOfPossibleMoves.end()) return true;
    else    return false;

}
