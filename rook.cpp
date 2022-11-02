#include "rook.h"
#include "move.h"

#include <vector>
#include <set>
#include <iostream>

Rook::Rook() {}
Rook::Rook(char name, int coordinate) : Piece(name, coordinate) {}

Rook::~Rook() {}

std::set<int> Rook::Threats(const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfThreats;
    int temp;

    // White moves
    if (isupper(name_)) {

        // Checking possible moves to the LEFT
        temp = coordinate_;
        while (temp % 8 != 0) {

            temp--;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

        // Checking possible moves to the RIGHT
        temp = coordinate_;
        while (temp % 8 != 7) {

            temp++;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

        // Checking possible moves to the UPWARDS
        temp = coordinate_;
        while (temp > 7) {

            temp -= 8;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

        // Checking possible moves to the DOWNWARDS
        temp = coordinate_;
        while (temp < 56) {

            temp += 8;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }
    }
    // Black moves
    if (islower(name_)) {

        temp = coordinate_;
        while (temp % 8 != 0) {

            temp--;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = coordinate_;
        while (temp % 8 != 7) {

            temp++;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = coordinate_;
        while (temp > 7) {

            temp -= 8;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = coordinate_;
        while (temp < 56) {

            temp += 8;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (isupper(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

    }

//    for (int i : setOfThreats) {
//        std::cout << i << " ^ ";
//    }
//    std::cout << "Hello there!\n";

    return setOfThreats;
}

std::set<int> Rook::SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const {
    std::set<int> setOfPossibleMoves;
    setOfPossibleMoves = Threats(vecBoardChar);
    return setOfPossibleMoves;
}

bool Rook::IsProperMove(const Move &move, const std::vector<char> &vecBoardChar, int enPassant) const {

    std::set<int> setOfPossibleMoves = Threats(vecBoardChar);

    // If finishCoordinate is in the Threats set return true;
    if (setOfPossibleMoves.find(move.getFinishCoordinate()) != setOfPossibleMoves.end()) return true;
    else    return false;
}


