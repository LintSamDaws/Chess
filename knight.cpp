#include "knight.h"

Knight::Knight() {}
Knight::Knight(char name, int coordinate) : Piece(name, coordinate) {}

Knight::~Knight() {}

std::set<int> Knight::Threats(const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves;

    if (isupper(name_)) {

        // Check direction RIGHT
        if (coordinate_ % 8 <= 5) {

            if ((coordinate_ / 8 >= 1) && (coordinate_ / 8 <= 6)) {

                if (vecBoardChar[coordinate_ - 6] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 6);
                }
                else if (islower(vecBoardChar[coordinate_ - 6])) {
                    setOfPossibleMoves.insert(coordinate_ - 6);
                }

                if (vecBoardChar[coordinate_ + 10] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 10);
                }
                else if (islower(vecBoardChar[coordinate_ + 10])) {
                    setOfPossibleMoves.insert(coordinate_ + 10);
                }
            }

            if (coordinate_ / 8 == 0) {

                if (vecBoardChar[coordinate_ + 10] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 10);
                }
                else if (islower(vecBoardChar[coordinate_ + 10])) {
                    setOfPossibleMoves.insert(coordinate_ + 10);
                }
            }

            if (coordinate_ / 8 == 7) {

                if (vecBoardChar[coordinate_ - 6] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 6);
                }
                else if (islower(vecBoardChar[coordinate_ - 6])) {
                    setOfPossibleMoves.insert(coordinate_ - 6);
                }
            }
        }

        // Check direction LEFT
        if (coordinate_ % 8 >= 2) {

            if ((coordinate_ / 8 >= 1) && (coordinate_ / 8 <= 6)) {

                if (vecBoardChar[coordinate_ + 6] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 6);
                }
                else if (islower(vecBoardChar[coordinate_ + 6])) {
                    setOfPossibleMoves.insert(coordinate_ + 6);
                }

                if (vecBoardChar[coordinate_ - 10] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 10);
                }
                else if (islower(vecBoardChar[coordinate_ - 10])) {
                    setOfPossibleMoves.insert(coordinate_ - 10);
                }
            }

            if (coordinate_ / 8 == 0) {

                if (vecBoardChar[coordinate_ + 6] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 6);
                }
                else if (islower(vecBoardChar[coordinate_ + 6])) {
                    setOfPossibleMoves.insert(coordinate_ + 6);
                }
            }

            if (coordinate_ / 8 == 7) {

                if (vecBoardChar[coordinate_ - 10] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 10);
                }
                else if (islower(vecBoardChar[coordinate_ - 10])) {
                    setOfPossibleMoves.insert(coordinate_ - 10);
                }
            }
        }

        // Check direction UP
        if (coordinate_ / 8 >= 2) {

            if ((coordinate_ % 8 >= 1) && (coordinate_ % 8 <= 6)) {

                if (vecBoardChar[coordinate_ - 17] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 17);
                }
                else if (islower(vecBoardChar[coordinate_ - 17])) {
                    setOfPossibleMoves.insert(coordinate_ - 17);
                }

                if (vecBoardChar[coordinate_ - 15] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 15);
                }
                else if (islower(vecBoardChar[coordinate_ - 15])) {
                    setOfPossibleMoves.insert(coordinate_ - 15);
                }
            }

            if (coordinate_ % 8 == 0) {

                if (vecBoardChar[coordinate_ - 15] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 15);
                }
                else if (islower(vecBoardChar[coordinate_ - 15])) {
                    setOfPossibleMoves.insert(coordinate_ - 15);
                }
            }

            if (coordinate_ % 8 == 7) {

                if (vecBoardChar[coordinate_ - 17] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 17);
                }
                else if (islower(vecBoardChar[coordinate_ - 17])) {
                    setOfPossibleMoves.insert(coordinate_ - 17);
                }
            }
        }

        // Check direction DOWN
        if (coordinate_ / 8 <= 5) {

            if ((coordinate_ % 8 >= 1) && (coordinate_ % 8 <= 6)) {

                if (vecBoardChar[coordinate_ + 17] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 17);
                }
                else if (islower(vecBoardChar[coordinate_ + 17])) {
                    setOfPossibleMoves.insert(coordinate_ + 17);
                }

                if (vecBoardChar[coordinate_ + 15] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 15);
                }
                else if (islower(vecBoardChar[coordinate_ + 15])) {
                    setOfPossibleMoves.insert(coordinate_ + 15);
                }
            }

            if (coordinate_ % 8 == 0) {

                if (vecBoardChar[coordinate_ + 17] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 17);
                }
                else if (islower(vecBoardChar[coordinate_ + 17])) {
                    setOfPossibleMoves.insert(coordinate_ + 17);
                }
            }

            if (coordinate_ % 8 == 7) {

                if (vecBoardChar[coordinate_ + 15] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 15);
                }
                else if (islower(vecBoardChar[coordinate_ + 15])) {
                    setOfPossibleMoves.insert(coordinate_ + 15);
                }
            }
        }


    }
    if (islower(name_)) {

        // Check direction RIGHT
        if (coordinate_ % 8 <= 5) {

            if ((coordinate_ / 8 >= 1) && (coordinate_ / 8 <= 6)) {

                if (vecBoardChar[coordinate_ - 6] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 6);
                }
                else if (isupper(vecBoardChar[coordinate_ - 6])) {
                    setOfPossibleMoves.insert(coordinate_ - 6);
                }

                if (vecBoardChar[coordinate_ + 10] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 10);
                }
                else if (isupper(vecBoardChar[coordinate_ + 10])) {
                    setOfPossibleMoves.insert(coordinate_ + 10);
                }
            }

            if (coordinate_ / 8 == 0) {

                if (vecBoardChar[coordinate_ + 10] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 10);
                }
                else if (isupper(vecBoardChar[coordinate_ + 10])) {
                    setOfPossibleMoves.insert(coordinate_ + 10);
                }
            }

            if (coordinate_ / 8 == 7) {

                if (vecBoardChar[coordinate_ - 6] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 6);
                }
                else if (isupper(vecBoardChar[coordinate_ - 6])) {
                    setOfPossibleMoves.insert(coordinate_ - 6);
                }
            }
        }

        // Check direction LEFT
        if (coordinate_ % 8 >= 2) {

            if ((coordinate_ / 8 >= 1) && (coordinate_ / 8 <= 6)) {

                if (vecBoardChar[coordinate_ + 6] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 6);
                }
                else if (isupper(vecBoardChar[coordinate_ + 6])) {
                    setOfPossibleMoves.insert(coordinate_ + 6);
                }

                if (vecBoardChar[coordinate_ - 10] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 10);
                }
                else if (isupper(vecBoardChar[coordinate_ - 10])) {
                    setOfPossibleMoves.insert(coordinate_ - 10);
                }
            }

            if (coordinate_ / 8 == 0) {

                if (vecBoardChar[coordinate_ + 6] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 6);
                }
                else if (isupper(vecBoardChar[coordinate_ + 6])) {
                    setOfPossibleMoves.insert(coordinate_ + 6);
                }
            }

            if (coordinate_ / 8 == 7) {

                if (vecBoardChar[coordinate_ - 10] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 10);
                }
                else if (isupper(vecBoardChar[coordinate_ - 10])) {
                    setOfPossibleMoves.insert(coordinate_ - 10);
                }
            }
        }

        // Check direction UP
        if (coordinate_ / 8 >= 2) {

            if ((coordinate_ % 8 >= 1) && (coordinate_ % 8 <= 6)) {

                if (vecBoardChar[coordinate_ - 17] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 17);
                }
                else if (isupper(vecBoardChar[coordinate_ - 17])) {
                    setOfPossibleMoves.insert(coordinate_ - 17);
                }

                if (vecBoardChar[coordinate_ - 15] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 15);
                }
                else if (isupper(vecBoardChar[coordinate_ - 15])) {
                    setOfPossibleMoves.insert(coordinate_ - 15);
                }
            }

            if (coordinate_ % 8 == 0) {

                if (vecBoardChar[coordinate_ - 15] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 15);
                }
                else if (isupper(vecBoardChar[coordinate_ - 15])) {
                    setOfPossibleMoves.insert(coordinate_ - 15);
                }
            }

            if (coordinate_ % 8 == 7) {

                if (vecBoardChar[coordinate_ - 17] == '0') {
                    setOfPossibleMoves.insert(coordinate_ - 17);
                }
                else if (isupper(vecBoardChar[coordinate_ - 17])) {
                    setOfPossibleMoves.insert(coordinate_ - 17);
                }
            }
        }

        // Check direction DOWN
        if (coordinate_ / 8 <= 5) {

            if ((coordinate_ % 8 >= 1) && (coordinate_ % 8 <= 6)) {

                if (vecBoardChar[coordinate_ + 17] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 17);
                }
                else if (isupper(vecBoardChar[coordinate_ + 17])) {
                    setOfPossibleMoves.insert(coordinate_ + 17);
                }

                if (vecBoardChar[coordinate_ + 15] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 15);
                }
                else if (isupper(vecBoardChar[coordinate_ + 15])) {
                    setOfPossibleMoves.insert(coordinate_ + 15);
                }
            }

            if (coordinate_ % 8 == 0) {

                if (vecBoardChar[coordinate_ + 17] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 17);
                }
                else if (isupper(vecBoardChar[coordinate_ + 17])) {
                    setOfPossibleMoves.insert(coordinate_ + 17);
                }
            }

            if (coordinate_ % 8 == 7) {

                if (vecBoardChar[coordinate_ + 15] == '0') {
                    setOfPossibleMoves.insert(coordinate_ + 15);
                }
                else if (isupper(vecBoardChar[coordinate_ + 15])) {
                    setOfPossibleMoves.insert(coordinate_ + 15);
                }
            }
        }
    }

    return setOfPossibleMoves;
}

std::set<int> Knight::SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const {
    std::set<int> setOfPossibleMoves;
    setOfPossibleMoves = Threats(vecBoardChar);
    return setOfPossibleMoves;
}

bool Knight::IsProperMove(const Move &move, const std::vector<char> &vecBoardChar, int enPassant) const {

    std::set<int> setOfPossibleMoves = Threats(vecBoardChar);

    // If finishCoordinate is in the Threats set return true;
    if (setOfPossibleMoves.find(move.getFinishCoordinate()) != setOfPossibleMoves.end()) return true;
    else    return false;
}
