#include "move.h"
#include "king.h"


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>


Move::Move() {}
Move::Move(std::string move) {

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

void Move::setMove(const Move &move) {
    activePiece = move.activePiece;
    startCoordinate = move.startCoordinate;
    finishCoordinate = move.finishCoordinate;
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

char Move::getActivePiece() const {
    return activePiece;
}
int Move::getStartCoordinate() const {
    return startCoordinate;
}
int Move::getFinishCoordinate() const {
    return finishCoordinate;
}

// Creates the Set of Possible Rook-like Moves
std::set<int> Move::linearThreat(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves;

    if (isupper(move.activePiece)) {

        int temp;

        temp = startCoordinate;
        while (temp % 8 != 0) {

            temp--;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while (temp % 8 != 7) {

            temp++;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while (temp > 7) {

            temp -= 8;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while (temp < 56) {

            temp += 8;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }
    }
    if (islower(move.activePiece)) {

        int temp;

        temp = startCoordinate;
        while (temp % 8 != 0) {

            temp--;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while (temp % 8 != 7) {

            temp++;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while (temp > 7) {

            temp -= 8;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while (temp < 56) {

            temp += 8;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

    }

    return setOfPossibleMoves;
}
bool Move::isProperMoveRook(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves;
    setOfPossibleMoves = move.linearThreat(move, vecBoardChar);

// Prints setOfPossibleMoves
//    for (int iter : setOfPossibleMoves) {
//        std::cout << iter << "\n";
//    }

    // If finishCoordinate is in the setOfPossibleMove return true;
    if (setOfPossibleMoves.find(move.finishCoordinate) != setOfPossibleMoves.end()) return true;
    else    return false;
}

// Creates the Set of Possible Bishop-like Moves
std::set<int> Move::diagonalThreat(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves;

    if (isupper(move.activePiece)) {

        int temp;

        temp = startCoordinate;
        while ((temp % 8 != 0) && (temp >= 9)) {

            temp -= 9;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while ((temp % 8 != 7) && (temp >= 8)) {

            temp -= 7;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while ((temp % 8 != 0) && (temp <= 55)) {

            temp += 7;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while ((temp % 8 != 7) && (temp <= 54)) {

            temp += 9;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }
    }
    if (islower(move.activePiece)) {

        int temp;

        temp = startCoordinate;
        while ((temp % 8 != 0) && (temp >= 9)) {

            temp -= 9;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while ((temp % 8 != 7) && (temp >= 8)) {

            temp -= 7;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while ((temp % 8 != 0) && (temp <= 55)) {

            temp += 7;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = startCoordinate;
        while ((temp % 8 != 7) && (temp <= 54)) {

            temp += 9;
            if (vecBoardChar[temp] == '0') {
                setOfPossibleMoves.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfPossibleMoves.insert(temp);
                break;
            } else {
                break;
            }
        }

    }

    return setOfPossibleMoves;
}
bool Move::isProperMoveBishop(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves;
    setOfPossibleMoves = move.diagonalThreat(move, vecBoardChar);

// Prints setOfPossibleMoves
//    for (int iter : setOfPossibleMoves) {
//        std::cout << iter << "\n";
//    }

    // If finishCoordinate is in the setOfPossibleMove return true;
    if (setOfPossibleMoves.find(move.finishCoordinate) != setOfPossibleMoves.end()) return true;
    else    return false;
}

bool Move::isProperMoveQueen(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMovesLinear;
    std::set<int> setOfPossibleMovesDiagonal;

    setOfPossibleMovesLinear = move.linearThreat(move, vecBoardChar);
    setOfPossibleMovesDiagonal = move.diagonalThreat(move, vecBoardChar);
    setOfPossibleMovesLinear.insert(setOfPossibleMovesDiagonal.begin(), setOfPossibleMovesDiagonal.end());

// Prints setOfPossibleMoves
//    for (int iter : setOfPossibleMovesLinear) {
//        std::cout << iter << "\n";
//    }

    // If finishCoordinate is in the setOfPossibleMove return true;
    if (setOfPossibleMovesLinear.find(move.finishCoordinate) != setOfPossibleMovesLinear.end()) return true;
    else    return false;
}

// Creates the Set of Possible Knight-like Moves
std::set<int> Move::knightThreat(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves;

    if (isupper(move.activePiece)) {

        // Check direction RIGHT
        if (startCoordinate % 8 <= 5) {

            if ((startCoordinate / 8 >= 1) && (startCoordinate / 8 <= 6)) {

                if (vecBoardChar[startCoordinate - 6] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 6);
                }
                else if (islower(vecBoardChar[startCoordinate - 6])) {
                    setOfPossibleMoves.insert(startCoordinate - 6);
                }

                if (vecBoardChar[startCoordinate + 10] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 10);
                }
                else if (islower(vecBoardChar[startCoordinate + 10])) {
                    setOfPossibleMoves.insert(startCoordinate + 10);
                }
            }

            if (startCoordinate / 8 == 0) {

                if (vecBoardChar[startCoordinate + 10] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 10);
                }
                else if (islower(vecBoardChar[startCoordinate + 10])) {
                    setOfPossibleMoves.insert(startCoordinate + 10);
                }
            }

            if (startCoordinate / 8 == 7) {

                if (vecBoardChar[startCoordinate - 6] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 6);
                }
                else if (islower(vecBoardChar[startCoordinate - 6])) {
                    setOfPossibleMoves.insert(startCoordinate - 6);
                }
            }
        }

        // Check direction LEFT
        if (startCoordinate % 8 >= 2) {

            if ((startCoordinate / 8 >= 1) && (startCoordinate / 8 <= 6)) {

                if (vecBoardChar[startCoordinate + 6] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 6);
                }
                else if (islower(vecBoardChar[startCoordinate + 6])) {
                    setOfPossibleMoves.insert(startCoordinate + 6);
                }

                if (vecBoardChar[startCoordinate - 10] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 10);
                }
                else if (islower(vecBoardChar[startCoordinate - 10])) {
                    setOfPossibleMoves.insert(startCoordinate - 10);
                }
            }

            if (startCoordinate / 8 == 0) {

                if (vecBoardChar[startCoordinate + 6] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 6);
                }
                else if (islower(vecBoardChar[startCoordinate + 6])) {
                    setOfPossibleMoves.insert(startCoordinate + 6);
                }
            }

            if (startCoordinate / 8 == 7) {

                if (vecBoardChar[startCoordinate - 10] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 10);
                }
                else if (islower(vecBoardChar[startCoordinate - 10])) {
                    setOfPossibleMoves.insert(startCoordinate - 10);
                }
            }
        }

        // Check direction UP
        if (startCoordinate / 8 >= 2) {

            if ((startCoordinate % 8 >= 1) && (startCoordinate % 8 <= 6)) {

                if (vecBoardChar[startCoordinate - 17] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 17);
                }
                else if (islower(vecBoardChar[startCoordinate - 17])) {
                    setOfPossibleMoves.insert(startCoordinate - 17);
                }

                if (vecBoardChar[startCoordinate - 15] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 15);
                }
                else if (islower(vecBoardChar[startCoordinate - 15])) {
                    setOfPossibleMoves.insert(startCoordinate - 15);
                }
            }

            if (startCoordinate % 8 == 0) {

                if (vecBoardChar[startCoordinate - 15] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 15);
                }
                else if (islower(vecBoardChar[startCoordinate - 15])) {
                    setOfPossibleMoves.insert(startCoordinate - 15);
                }
            }

            if (startCoordinate % 8 == 7) {

                if (vecBoardChar[startCoordinate - 17] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 17);
                }
                else if (islower(vecBoardChar[startCoordinate - 17])) {
                    setOfPossibleMoves.insert(startCoordinate - 17);
                }
            }
        }

        // Check direction DOWN
        if (startCoordinate / 8 <= 5) {

            if ((startCoordinate % 8 >= 1) && (startCoordinate % 8 <= 6)) {

                if (vecBoardChar[startCoordinate + 17] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 17);
                }
                else if (islower(vecBoardChar[startCoordinate + 17])) {
                    setOfPossibleMoves.insert(startCoordinate + 17);
                }

                if (vecBoardChar[startCoordinate + 15] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 15);
                }
                else if (islower(vecBoardChar[startCoordinate + 15])) {
                    setOfPossibleMoves.insert(startCoordinate + 15);
                }
            }

            if (startCoordinate % 8 == 0) {

                if (vecBoardChar[startCoordinate + 17] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 17);
                }
                else if (islower(vecBoardChar[startCoordinate + 17])) {
                    setOfPossibleMoves.insert(startCoordinate + 17);
                }
            }

            if (startCoordinate % 8 == 7) {

                if (vecBoardChar[startCoordinate + 15] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 15);
                }
                else if (islower(vecBoardChar[startCoordinate + 15])) {
                    setOfPossibleMoves.insert(startCoordinate + 15);
                }
            }
        }


    }
    if (islower(move.activePiece)) {

        // Check direction RIGHT
        if (startCoordinate % 8 <= 5) {

            if ((startCoordinate / 8 >= 1) && (startCoordinate / 8 <= 6)) {

                if (vecBoardChar[startCoordinate - 6] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 6);
                }
                else if (isupper(vecBoardChar[startCoordinate - 6])) {
                    setOfPossibleMoves.insert(startCoordinate - 6);
                }

                if (vecBoardChar[startCoordinate + 10] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 10);
                }
                else if (isupper(vecBoardChar[startCoordinate + 10])) {
                    setOfPossibleMoves.insert(startCoordinate + 10);
                }
            }

            if (startCoordinate / 8 == 0) {

                if (vecBoardChar[startCoordinate + 10] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 10);
                }
                else if (isupper(vecBoardChar[startCoordinate + 10])) {
                    setOfPossibleMoves.insert(startCoordinate + 10);
                }
            }

            if (startCoordinate / 8 == 7) {

                if (vecBoardChar[startCoordinate - 6] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 6);
                }
                else if (isupper(vecBoardChar[startCoordinate - 6])) {
                    setOfPossibleMoves.insert(startCoordinate - 6);
                }
            }
        }

        // Check direction LEFT
        if (startCoordinate % 8 >= 2) {

            if ((startCoordinate / 8 >= 1) && (startCoordinate / 8 <= 6)) {

                if (vecBoardChar[startCoordinate + 6] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 6);
                }
                else if (isupper(vecBoardChar[startCoordinate + 6])) {
                    setOfPossibleMoves.insert(startCoordinate + 6);
                }

                if (vecBoardChar[startCoordinate - 10] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 10);
                }
                else if (isupper(vecBoardChar[startCoordinate - 10])) {
                    setOfPossibleMoves.insert(startCoordinate - 10);
                }
            }

            if (startCoordinate / 8 == 0) {

                if (vecBoardChar[startCoordinate + 6] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 6);
                }
                else if (isupper(vecBoardChar[startCoordinate + 6])) {
                    setOfPossibleMoves.insert(startCoordinate + 6);
                }
            }

            if (startCoordinate / 8 == 7) {

                if (vecBoardChar[startCoordinate - 10] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 10);
                }
                else if (isupper(vecBoardChar[startCoordinate - 10])) {
                    setOfPossibleMoves.insert(startCoordinate - 10);
                }
            }
        }

        // Check direction UP
        if (startCoordinate / 8 >= 2) {

            if ((startCoordinate % 8 >= 1) && (startCoordinate % 8 <= 6)) {

                if (vecBoardChar[startCoordinate - 17] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 17);
                }
                else if (isupper(vecBoardChar[startCoordinate - 17])) {
                    setOfPossibleMoves.insert(startCoordinate - 17);
                }

                if (vecBoardChar[startCoordinate - 15] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 15);
                }
                else if (isupper(vecBoardChar[startCoordinate - 15])) {
                    setOfPossibleMoves.insert(startCoordinate - 15);
                }
            }

            if (startCoordinate % 8 == 0) {

                if (vecBoardChar[startCoordinate - 15] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 15);
                }
                else if (isupper(vecBoardChar[startCoordinate - 15])) {
                    setOfPossibleMoves.insert(startCoordinate - 15);
                }
            }

            if (startCoordinate % 8 == 7) {

                if (vecBoardChar[startCoordinate - 17] == '0') {
                    setOfPossibleMoves.insert(startCoordinate - 17);
                }
                else if (isupper(vecBoardChar[startCoordinate - 17])) {
                    setOfPossibleMoves.insert(startCoordinate - 17);
                }
            }
        }

        // Check direction DOWN
        if (startCoordinate / 8 <= 5) {

            if ((startCoordinate % 8 >= 1) && (startCoordinate % 8 <= 6)) {

                if (vecBoardChar[startCoordinate + 17] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 17);
                }
                else if (isupper(vecBoardChar[startCoordinate + 17])) {
                    setOfPossibleMoves.insert(startCoordinate + 17);
                }

                if (vecBoardChar[startCoordinate + 15] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 15);
                }
                else if (isupper(vecBoardChar[startCoordinate + 15])) {
                    setOfPossibleMoves.insert(startCoordinate + 15);
                }
            }

            if (startCoordinate % 8 == 0) {

                if (vecBoardChar[startCoordinate + 17] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 17);
                }
                else if (isupper(vecBoardChar[startCoordinate + 17])) {
                    setOfPossibleMoves.insert(startCoordinate + 17);
                }
            }

            if (startCoordinate % 8 == 7) {

                if (vecBoardChar[startCoordinate + 15] == '0') {
                    setOfPossibleMoves.insert(startCoordinate + 15);
                }
                else if (isupper(vecBoardChar[startCoordinate + 15])) {
                    setOfPossibleMoves.insert(startCoordinate + 15);
                }
            }
        }
    }

    return setOfPossibleMoves;
}
bool Move::isProperMoveKnight(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves;
    setOfPossibleMoves = move.knightThreat(move, vecBoardChar);

// Prints setOfPossibleMoves
//    for (int iter : setOfPossibleMoves) {
//        std::cout << iter << "\n";
//    }

    // If finishCoordinate is in the setOfPossibleMove return true;
    if (setOfPossibleMoves.find(move.finishCoordinate) != setOfPossibleMoves.end()) return true;
    else    return false;
}

std::set<int> Move::pawnThreat(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleThreats;

    if (isupper(move.activePiece)) {

        if (move.startCoordinate % 8 > 0) {
            if (vecBoardChar[startCoordinate - 9] == '0') {
                setOfPossibleThreats.insert(startCoordinate - 9);
            }
            else if (islower(vecBoardChar[startCoordinate - 9])) {
                setOfPossibleThreats.insert(startCoordinate - 9);
            }
        }

        if (move.startCoordinate % 8 < 7) {
            if (vecBoardChar[startCoordinate - 7] == '0') {
                setOfPossibleThreats.insert(startCoordinate - 7);
            }
            else if (islower(vecBoardChar[startCoordinate - 7])) {
                setOfPossibleThreats.insert(startCoordinate - 7);
            }
        }
    }

    if (islower(move.activePiece)) {

        if (move.startCoordinate % 8 > 0) {
            if (vecBoardChar[startCoordinate + 7] == '0') {
                setOfPossibleThreats.insert(startCoordinate + 7);
            }
            else if (isupper(vecBoardChar[startCoordinate + 7])) {
                setOfPossibleThreats.insert(startCoordinate + 7);
            }
        }
        if (move.startCoordinate % 8 < 7) {
            if (vecBoardChar[startCoordinate + 9] == '0') {
                setOfPossibleThreats.insert(startCoordinate + 9);
            }
            else if (isupper(vecBoardChar[startCoordinate + 9])) {
                setOfPossibleThreats.insert(startCoordinate + 9);
            }
        }
    }
    return setOfPossibleThreats;
}

std::set<int> Move::setOfPossiblePawnMoves(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves;

    if (isupper(move.activePiece)) {

        if (islower(vecBoardChar[startCoordinate - 9])) {
            setOfPossibleMoves.insert(startCoordinate - 9);
        }

        if (islower(vecBoardChar[startCoordinate - 7])) {
            setOfPossibleMoves.insert(startCoordinate - 7);
        }

        if (startCoordinate - 9 == enPassant) {
            setOfPossibleMoves.insert(startCoordinate - 9);
        }

        if (startCoordinate - 7 == enPassant) {
            setOfPossibleMoves.insert(startCoordinate - 7);
        }



        if (startCoordinate / 8 == 6) {
            if (vecBoardChar[startCoordinate - 8] == '0') {
                setOfPossibleMoves.insert(startCoordinate - 8);
            }
            if ((vecBoardChar[startCoordinate - 8] == '0') && (vecBoardChar[startCoordinate - 16] == '0')) {
                setOfPossibleMoves.insert(startCoordinate - 16);
            }
        }
        else {
            if (vecBoardChar[startCoordinate - 8] == '0') {
                setOfPossibleMoves.insert(startCoordinate - 8);
            }
        }
    }

    if (islower(move.activePiece)) {

        if (isupper(vecBoardChar[startCoordinate + 9])) {
            setOfPossibleMoves.insert(startCoordinate + 9);
        }

        if (isupper(vecBoardChar[startCoordinate + 7])) {
            setOfPossibleMoves.insert(startCoordinate + 7);
        }

        if (startCoordinate + 9 == enPassant) {
            setOfPossibleMoves.insert(startCoordinate + 9);
        }

        if (startCoordinate + 7 == enPassant) {
            setOfPossibleMoves.insert(startCoordinate + 7);
        }

        if (startCoordinate / 8 == 1) {
            if (vecBoardChar[startCoordinate + 8] == '0') {
                setOfPossibleMoves.insert(startCoordinate + 8);
            }
            if ((vecBoardChar[startCoordinate + 8] == '0') && (vecBoardChar[startCoordinate + 16] == '0')) {
                setOfPossibleMoves.insert(startCoordinate + 16);
            }
        }
        else {
            if (vecBoardChar[startCoordinate + 8] == '0') {
                setOfPossibleMoves.insert(startCoordinate + 8);
            }
        }
    }

    return setOfPossibleMoves;
}

bool Move::isProperMovePawn(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves;
    setOfPossibleMoves = move.setOfPossiblePawnMoves(move, vecBoardChar);

// Prints setOfPossibleMoves
//    for (int iter : setOfPossibleMoves) {
//        std::cout << iter << "\n";
//    }

    // If finishCoordinate is in the setOfPossibleMove return true;
    if (setOfPossibleMoves.find(move.finishCoordinate) != setOfPossibleMoves.end()) return true;
    else    return false;
}

bool Move::villainKingIsUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfThreats;
    std::set<int> additionalThreats;
    int villainKingCoordinate;

    // Define is Villain's King White 'K' or Black 'k'
    char targetKing;
    if (islower(move.getActivePiece())) {

        for (int i=0; i<63; i++) {

            Move tempMove;
            tempMove.setActivePiece(vecBoardChar[i]);
            tempMove.setStartCoordinate(i);
            tempMove.setFinishCoordinate(i);

            if (vecBoardChar[i] == 'q') {
                additionalThreats = tempMove.linearThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
                additionalThreats = tempMove.diagonalThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'r') {
                additionalThreats = tempMove.linearThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'b') {
                additionalThreats = tempMove.diagonalThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'n') {
                additionalThreats = tempMove.knightThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'p') {
                additionalThreats = tempMove.pawnThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'K') {
                villainKingCoordinate = i;
            }

            //FIX for HeroKing
        }
    }
    else {

        for (int i=0; i<63; i++) {

            Move tempMove;
            tempMove.setActivePiece(vecBoardChar[i]);
            tempMove.setStartCoordinate(i);
            tempMove.setFinishCoordinate(i);

            if (vecBoardChar[i] == 'Q') {
                additionalThreats = tempMove.linearThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
                additionalThreats = tempMove.diagonalThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'R') {
                additionalThreats = tempMove.linearThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'B') {
                additionalThreats = tempMove.diagonalThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'N') {
                additionalThreats = tempMove.knightThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'P') {
                additionalThreats = tempMove.pawnThreat(tempMove, vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'k') {
                villainKingCoordinate = i;
            }

            //FIX for HeroKing
        }
    }
    for (auto iter : setOfThreats) {
        std::cout << iter << " ";
    }
    std::cout << "\n^" << villainKingCoordinate << "^\n";

    if (setOfThreats.find(villainKingCoordinate) != setOfThreats.end()) {
        return true;
    }
    else return false;
}

std::set<int> Move::setOfPossibleKingMoves(const Move &move, const std::vector<char> &vecBoardChar) const {


    std::set<int> setOfThreats;

    if (isupper(move.getActivePiece())) {

        // Check direction DOWN
        if (startCoordinate / 8 <= 6) {

            if (vecBoardChar[startCoordinate + 8] == '0') {
                setOfThreats.insert(startCoordinate + 8);
            }
            else if (islower(vecBoardChar[startCoordinate + 8])) {
                setOfThreats.insert(startCoordinate + 8);
            }
        }

        // Check direction R-D DIAG
        if (startCoordinate % 8 <= 6 && startCoordinate / 8 <= 6) {

            if (vecBoardChar[startCoordinate + 9] == '0') {
                setOfThreats.insert(startCoordinate + 9);
            }
            else if (islower(vecBoardChar[startCoordinate + 9])) {
                setOfThreats.insert(startCoordinate + 9);
            }
        }

        // Check direction RIGHT
        if (startCoordinate % 8 <= 6) {

            if (vecBoardChar[startCoordinate + 1] == '0') {
                setOfThreats.insert(startCoordinate + 1);
            }
            else if (islower(vecBoardChar[startCoordinate + 1])) {
                setOfThreats.insert(startCoordinate + 1);
            }
        }

        // Check direction R-U DIAG
        if (startCoordinate % 8 <= 6 && startCoordinate / 8 >= 1) {

            if (vecBoardChar[startCoordinate - 7] == '0') {
                setOfThreats.insert(startCoordinate - 7);
            }
            else if (islower(vecBoardChar[startCoordinate - 7])) {
                setOfThreats.insert(startCoordinate - 7);
            }
        }

        // Check direction UP
        if (startCoordinate / 8 >= 1) {

            if (vecBoardChar[startCoordinate - 8] == '0') {
                setOfThreats.insert(startCoordinate - 8);
            }
            else if (islower(vecBoardChar[startCoordinate - 8])) {
                setOfThreats.insert(startCoordinate - 8);
            }
        }

        // Check direction L-U DIAG
        if (startCoordinate % 8 >= 1 && startCoordinate / 8 >= 1) {

            if (vecBoardChar[startCoordinate - 9] == '0') {
                setOfThreats.insert(startCoordinate - 9);
            }
            else if (islower(vecBoardChar[startCoordinate - 9])) {
                setOfThreats.insert(startCoordinate - 9);
            }
        }

        // Check direction LEFT
        if (startCoordinate % 8 >= 1) {

            if (vecBoardChar[startCoordinate - 1] == '0') {
                setOfThreats.insert(startCoordinate - 1);
            }
            else if (islower(vecBoardChar[startCoordinate - 1])) {
                setOfThreats.insert(startCoordinate - 1);
            }
        }

        // Check direction L-D DIAG
        if (startCoordinate % 8 >= 1 && startCoordinate / 8 <= 6) {

            if (vecBoardChar[startCoordinate + 7] == '0') {
                setOfThreats.insert(startCoordinate + 7);
            }
            else if (islower(vecBoardChar[startCoordinate + 7])) {
                setOfThreats.insert(startCoordinate + 7);
            }
        }
    }

    if (islower(move.getActivePiece())) {

        // Check direction DOWN
        if (startCoordinate / 8 <= 6) {

            if (vecBoardChar[startCoordinate + 8] == '0') {
                setOfThreats.insert(startCoordinate + 8);
            }
            else if (isupper(vecBoardChar[startCoordinate + 8])) {
                setOfThreats.insert(startCoordinate + 8);
            }
        }

        // Check direction R-D DIAG
        if (startCoordinate % 8 <= 6 && startCoordinate / 8 <= 6) {

            if (vecBoardChar[startCoordinate + 9] == '0') {
                setOfThreats.insert(startCoordinate + 9);
            }
            else if (isupper(vecBoardChar[startCoordinate + 9])) {
                setOfThreats.insert(startCoordinate + 9);
            }
        }

        // Check direction RIGHT
        if (startCoordinate % 8 <= 6) {

            if (vecBoardChar[startCoordinate + 1] == '0') {
                setOfThreats.insert(startCoordinate + 1);
            }
            else if (isupper(vecBoardChar[startCoordinate + 1])) {
                setOfThreats.insert(startCoordinate + 1);
            }
        }

        // Check direction R-U DIAG
        if (startCoordinate % 8 <= 6 && startCoordinate / 8 >= 1) {

            if (vecBoardChar[startCoordinate - 7] == '0') {
                setOfThreats.insert(startCoordinate - 7);
            }
            else if (isupper(vecBoardChar[startCoordinate - 7])) {
                setOfThreats.insert(startCoordinate - 7);
            }
        }

        // Check direction UP
        if (startCoordinate / 8 >= 1) {

            if (vecBoardChar[startCoordinate - 8] == '0') {
                setOfThreats.insert(startCoordinate - 8);
            }
            else if (isupper(vecBoardChar[startCoordinate - 8])) {
                setOfThreats.insert(startCoordinate - 8);
            }
        }

        // Check direction L-U DIAG
        if (startCoordinate % 8 >= 1 && startCoordinate / 8 >= 1) {

            if (vecBoardChar[startCoordinate - 9] == '0') {
                setOfThreats.insert(startCoordinate - 9);
            }
            else if (isupper(vecBoardChar[startCoordinate - 9])) {
                setOfThreats.insert(startCoordinate - 9);
            }
        }

        // Check direction LEFT
        if (startCoordinate % 8 >= 1) {

            if (vecBoardChar[startCoordinate - 1] == '0') {
                setOfThreats.insert(startCoordinate - 1);
            }
            else if (isupper(vecBoardChar[startCoordinate - 1])) {
                setOfThreats.insert(startCoordinate - 1);
            }
        }

        // Check direction L-D DIAG
        if (startCoordinate % 8 >= 1 && startCoordinate / 8 <= 6) {

            if (vecBoardChar[startCoordinate + 7] == '0') {
                setOfThreats.insert(startCoordinate + 7);
            }
            else if (isupper(vecBoardChar[startCoordinate + 7])) {
                setOfThreats.insert(startCoordinate + 7);
            }
        }
    }

    return setOfThreats;
}

bool Move::isProperMoveKing(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves = setOfPossibleKingMoves(move, vecBoardChar);

    // If finishCoordinate is in the Threats set return true;
    if (setOfPossibleMoves.find(move.getFinishCoordinate()) != setOfPossibleMoves.end()) return true;
    else    return false;
}

bool Move::NOTMovedCastling(const Move &move, const std::unordered_map<std::string, bool> &castlingStates) const {
    bool res = true;
    if (move.getFinishCoordinate() == 56) res = castlingStates.at("O-O-O");
    if (move.getFinishCoordinate() == 63) res = castlingStates.at("O-O");
    if (move.getFinishCoordinate() == 0) res = castlingStates.at("o-o-o");
    if (move.getFinishCoordinate() == 7) res = castlingStates.at("o-o");
    return res;
}

bool Move::NoPieceBetweenCastling(const Move &move, const std::vector<char> &vecBoardChar) const {

    if (move.getFinishCoordinate() == 56) {
        if (vecBoardChar[57] == '0' && vecBoardChar[58] == '0' && vecBoardChar[59] == '0') return true;
        else return false;
    }
    if (move.getFinishCoordinate() == 63) {
        if (vecBoardChar[61] == '0' && vecBoardChar[62] == '0') return true;
        else return false;
    }
    if (move.getFinishCoordinate() == 0) {
        if (vecBoardChar[1] == '0' && vecBoardChar[2] == '0' && vecBoardChar[3] == '0') return true;
        else return false;
    }
    if (move.getFinishCoordinate() == 7) {
        if (vecBoardChar[5] == '0' && vecBoardChar[6] == '0') return true;
        else return false;
    }
    return false;
}

bool Move::IsKingUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const {
    char name;
    int coordinate;
    if (isupper(move.getActivePiece())) name = 'K';
    else name = 'k';
    coordinate = move.getStartCoordinate();
    King king(name, coordinate);
    if (king.IsKingUnderCheck(vecBoardChar)) return true;
    else return false;
}

bool Move::IsCastlingSquaresUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const {
    King additionalKing1;
    King additionalKing2;
    if (isupper(move.getActivePiece())) {
        if (move.getFinishCoordinate() == 56) {
            additionalKing1.SetName('K');
            additionalKing1.SetCoordinate(58);

            additionalKing2.SetName('K');
            additionalKing2.SetCoordinate(59);

            if(additionalKing1.IsKingUnderCheck(vecBoardChar) || additionalKing2.IsKingUnderCheck(vecBoardChar)) return true;
            else return false;
        }
        else {
            additionalKing1.SetName('K');
            additionalKing1.SetCoordinate(61);

            additionalKing2.SetName('K');
            additionalKing2.SetCoordinate(62);

            if(additionalKing1.IsKingUnderCheck(vecBoardChar) || additionalKing2.IsKingUnderCheck(vecBoardChar)) return true;
            else return false;
        }
    }
    else {
        if (move.getFinishCoordinate() == 0) {
            additionalKing1.SetName('k');
            additionalKing1.SetCoordinate(2);

            additionalKing2.SetName('k');
            additionalKing2.SetCoordinate(3);

            if(additionalKing1.IsKingUnderCheck(vecBoardChar) || additionalKing2.IsKingUnderCheck(vecBoardChar)) return true;
            else return false;
        }
        else {
            additionalKing1.SetName('k');
            additionalKing1.SetCoordinate(5);

            additionalKing2.SetName('k');
            additionalKing2.SetCoordinate(6);

            if(additionalKing1.IsKingUnderCheck(vecBoardChar) || additionalKing2.IsKingUnderCheck(vecBoardChar)) return true;
            else return false;
        }
    }
}

bool Move::IsCastlingPossible(const Move &move, const std::vector<char> &vecBoardChar, const std::unordered_map<std::string, bool> &castlingStates) const {

    if (move.NOTMovedCastling(move, castlingStates) && move.NoPieceBetweenCastling(move, vecBoardChar) && !move.IsKingUnderCheck(move, vecBoardChar) && !move.IsCastlingSquaresUnderCheck(move, vecBoardChar)) return true;
    else return false;
}















