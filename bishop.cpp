#include "bishop.h"
#include "move.h"

#include <vector>
#include <set>

Bishop::Bishop() {}
Bishop::Bishop(char name, int coordinate) : Piece(name, coordinate) {}

Bishop::~Bishop() {}

std::set<int> Bishop::Threats(const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfThreats;
    int temp;

    if (isupper(name_)) {

        temp = coordinate_;
        while ((temp % 8 != 0) && (temp >= 9)) {

            temp -= 9;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = coordinate_;
        while ((temp % 8 != 7) && (temp >= 8)) {

            temp -= 7;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = coordinate_;
        while ((temp % 8 != 0) && (temp <= 55)) {

            temp += 7;
            if (vecBoardChar[temp] == '0') {
                setOfThreats.insert(temp);
            } else if (islower(vecBoardChar[temp])) {
                setOfThreats.insert(temp);
                break;
            } else {
                break;
            }
        }

        temp = coordinate_;
        while ((temp % 8 != 7) && (temp <= 54)) {

            temp += 9;
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

    if (islower(name_)) {

        temp = coordinate_;
        while ((temp % 8 != 0) && (temp >= 9)) {

            temp -= 9;
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
        while ((temp % 8 != 7) && (temp >= 8)) {

            temp -= 7;
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
        while ((temp % 8 != 0) && (temp <= 55)) {

            temp += 7;
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
        while ((temp % 8 != 7) && (temp <= 54)) {

            temp += 9;
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
    return setOfThreats;
}

std::set<int> Bishop::SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const {
    std::set<int> setOfPossibleMoves;
    setOfPossibleMoves = Threats(vecBoardChar);
    return setOfPossibleMoves;
}

bool Bishop::IsProperMove(const Move &move, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfPossibleMoves = Threats(vecBoardChar);

    // If finishCoordinate is in the Threats set return true;
    if (setOfPossibleMoves.find(move.getFinishCoordinate()) != setOfPossibleMoves.end()) return true;
    else    return false;
}
