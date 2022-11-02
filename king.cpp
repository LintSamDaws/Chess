#include "king.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "pawn.h"
#include "move.h"

#include <vector>
#include <set>

King::King() {}
King::King(char name, int coordinate) : Piece(name, coordinate) {}

King::~King() {}

std::set<int> King::Threats(const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfThreats;

    if (isupper(name_)) {

        // Check direction DOWN
        if (coordinate_ / 8 <= 6) {

            if (vecBoardChar[coordinate_ + 8] == '0') {
                setOfThreats.insert(coordinate_ + 8);
            }
            else if (islower(vecBoardChar[coordinate_ + 8])) {
                setOfThreats.insert(coordinate_ + 8);
            }
        }

        // Check direction R-D DIAG
        if (coordinate_ % 8 <= 6 && coordinate_ / 8 <= 6) {

            if (vecBoardChar[coordinate_ + 9] == '0') {
                setOfThreats.insert(coordinate_ + 9);
            }
            else if (islower(vecBoardChar[coordinate_ + 9])) {
                setOfThreats.insert(coordinate_ + 9);
            }
        }

        // Check direction RIGHT
        if (coordinate_ % 8 <= 6) {

            if (vecBoardChar[coordinate_ + 1] == '0') {
                setOfThreats.insert(coordinate_ + 1);
            }
            else if (islower(vecBoardChar[coordinate_ + 1])) {
                setOfThreats.insert(coordinate_ + 1);
            }
        }

        // Check direction R-U DIAG
        if (coordinate_ % 8 <= 6 && coordinate_ / 8 >= 1) {

            if (vecBoardChar[coordinate_ - 7] == '0') {
                setOfThreats.insert(coordinate_ - 7);
            }
            else if (islower(vecBoardChar[coordinate_ - 7])) {
                setOfThreats.insert(coordinate_ - 7);
            }
        }

        // Check direction UP
        if (coordinate_ / 8 >= 1) {

            if (vecBoardChar[coordinate_ - 8] == '0') {
                setOfThreats.insert(coordinate_ - 8);
            }
            else if (islower(vecBoardChar[coordinate_ - 8])) {
                setOfThreats.insert(coordinate_ - 8);
            }
        }

        // Check direction L-U DIAG
        if (coordinate_ % 8 >= 1 && coordinate_ / 8 >= 1) {

            if (vecBoardChar[coordinate_ - 9] == '0') {
                setOfThreats.insert(coordinate_ - 9);
            }
            else if (islower(vecBoardChar[coordinate_ - 9])) {
                setOfThreats.insert(coordinate_ - 9);
            }
        }

        // Check direction LEFT
        if (coordinate_ % 8 >= 1) {

            if (vecBoardChar[coordinate_ - 1] == '0') {
                setOfThreats.insert(coordinate_ - 1);
            }
            else if (islower(vecBoardChar[coordinate_ - 1])) {
                setOfThreats.insert(coordinate_ - 1);
            }
        }

        // Check direction L-D DIAG
        if (coordinate_ % 8 >= 1 && coordinate_ / 8 <= 6) {

            if (vecBoardChar[coordinate_ + 7] == '0') {
                setOfThreats.insert(coordinate_ + 7);
            }
            else if (islower(vecBoardChar[coordinate_ + 7])) {
                setOfThreats.insert(coordinate_ + 7);
            }
        }
    }

    if (islower(name_)) {

        // Check direction DOWN
        if (coordinate_ / 8 <= 6) {

            if (vecBoardChar[coordinate_ + 8] == '0') {
                setOfThreats.insert(coordinate_ + 8);
            }
            else if (isupper(vecBoardChar[coordinate_ + 8])) {
                setOfThreats.insert(coordinate_ + 8);
            }
        }

        // Check direction R-D DIAG
        if (coordinate_ % 8 <= 6 && coordinate_ / 8 <= 6) {

            if (vecBoardChar[coordinate_ + 9] == '0') {
                setOfThreats.insert(coordinate_ + 9);
            }
            else if (isupper(vecBoardChar[coordinate_ + 9])) {
                setOfThreats.insert(coordinate_ + 9);
            }
        }

        // Check direction RIGHT
        if (coordinate_ % 8 <= 6) {

            if (vecBoardChar[coordinate_ + 1] == '0') {
                setOfThreats.insert(coordinate_ + 1);
            }
            else if (isupper(vecBoardChar[coordinate_ + 1])) {
                setOfThreats.insert(coordinate_ + 1);
            }
        }

        // Check direction R-U DIAG
        if (coordinate_ % 8 <= 6 && coordinate_ / 8 >= 1) {

            if (vecBoardChar[coordinate_ - 7] == '0') {
                setOfThreats.insert(coordinate_ - 7);
            }
            else if (isupper(vecBoardChar[coordinate_ - 7])) {
                setOfThreats.insert(coordinate_ - 7);
            }
        }

        // Check direction UP
        if (coordinate_ / 8 >= 1) {

            if (vecBoardChar[coordinate_ - 8] == '0') {
                setOfThreats.insert(coordinate_ - 8);
            }
            else if (isupper(vecBoardChar[coordinate_ - 8])) {
                setOfThreats.insert(coordinate_ - 8);
            }
        }

        // Check direction L-U DIAG
        if (coordinate_ % 8 >= 1 && coordinate_ / 8 >= 1) {

            if (vecBoardChar[coordinate_ - 9] == '0') {
                setOfThreats.insert(coordinate_ - 9);
            }
            else if (isupper(vecBoardChar[coordinate_ - 9])) {
                setOfThreats.insert(coordinate_ - 9);
            }
        }

        // Check direction LEFT
        if (coordinate_ % 8 >= 1) {

            if (vecBoardChar[coordinate_ - 1] == '0') {
                setOfThreats.insert(coordinate_ - 1);
            }
            else if (isupper(vecBoardChar[coordinate_ - 1])) {
                setOfThreats.insert(coordinate_ - 1);
            }
        }

        // Check direction L-D DIAG
        if (coordinate_ % 8 >= 1 && coordinate_ / 8 <= 6) {

            if (vecBoardChar[coordinate_ + 7] == '0') {
                setOfThreats.insert(coordinate_ + 7);
            }
            else if (isupper(vecBoardChar[coordinate_ + 7])) {
                setOfThreats.insert(coordinate_ + 7);
            }
        }
    }

    return setOfThreats;
}

std::set<int> King::SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const {
    std::set<int> setOfPossibleMoves;
    setOfPossibleMoves = Threats(vecBoardChar);
    return setOfPossibleMoves;
}

bool King::IsProperMove(const Move &move, const std::vector<char> &vecBoardChar, int enPassant) const {

    std::set<int> setOfPossibleMoves = Threats(vecBoardChar);

    // If finishCoordinate is in the Threats set return true;
    if (setOfPossibleMoves.find(move.getFinishCoordinate()) != setOfPossibleMoves.end()) return true;
    else    return false;
}

bool King::IsKingUnderCheck(const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfThreats;
    std::set<int> additionalThreats;

    // Define is King White 'K' (uppercase) or Black 'k' (lowercase)
    if (isupper(name_)) {

        for (int i=0; i<64; i++) {

            Piece *pieceVillain;

            if (vecBoardChar[i] == 'q') {
                Queen queenVillain('q', i);
                pieceVillain = &queenVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'r') {
                Rook rookVillain('r', i);
                pieceVillain = &rookVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'b') {
                Bishop bishopVilalin('b', i);
                pieceVillain = &bishopVilalin;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'n') {
                Knight knightVillain('n', i);
                pieceVillain = &knightVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'p') {
                Pawn pawnVillain('p', i);
                pieceVillain = &pawnVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'k') {
                King kingVillain('k', i);
                pieceVillain = &kingVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
        }
    }
    else {

        for (int i=0; i<64; i++) {

            Piece *pieceVillain;

            if (vecBoardChar[i] == 'Q') {
                Queen queenVillain('Q', i);
                pieceVillain = &queenVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'R') {
                Rook rookVillain('R', i);
                pieceVillain = &rookVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'B') {
                Bishop bishopVilalin('B', i);
                pieceVillain = &bishopVilalin;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'N') {
                Knight knightVillain('N', i);
                pieceVillain = &knightVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'P') {
                Pawn pawnVillain('P', i);
                pieceVillain = &pawnVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'K') {
                King kingVillain('K', i);
                pieceVillain = &kingVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
        }
    }

    // Looking for Coordinate in the setOfThreats
    if (setOfThreats.find(coordinate_) != setOfThreats.end()) {
        return true;
    }
    else return false;
}

bool King::IsKingUnderCheck(King king, const std::vector<char> &vecBoardChar) const {

    std::set<int> setOfThreats;
    std::set<int> additionalThreats;

    // Define is King White 'K' (uppercase) or Black 'k' (lowercase)
    if (isupper(king.GetName())) {

        for (int i=0; i<64; i++) {

            Piece *pieceVillain;

            if (vecBoardChar[i] == 'q') {
                Queen queenVillain('q', i);
                pieceVillain = &queenVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'r') {
                Rook rookVillain('r', i);
                pieceVillain = &rookVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'b') {
                Bishop bishopVilalin('b', i);
                pieceVillain = &bishopVilalin;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'n') {
                Knight knightVillain('n', i);
                pieceVillain = &knightVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'p') {
                Pawn pawnVillain('p', i);
                pieceVillain = &pawnVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'k') {
                King kingVillain('k', i);
                pieceVillain = &kingVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
        }
    }
    else {

        for (int i=0; i<64; i++) {

            Piece *pieceVillain;

            if (vecBoardChar[i] == 'Q') {
                Queen queenVillain('Q', i);
                pieceVillain = &queenVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'R') {
                Rook rookVillain('R', i);
                pieceVillain = &rookVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'B') {
                Bishop bishopVilalin('B', i);
                pieceVillain = &bishopVilalin;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'N') {
                Knight knightVillain('N', i);
                pieceVillain = &knightVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'P') {
                Pawn pawnVillain('P', i);
                pieceVillain = &pawnVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
            if (vecBoardChar[i] == 'K') {
                King kingVillain('K', i);
                pieceVillain = &kingVillain;
                additionalThreats = pieceVillain->Threats(vecBoardChar);
                setOfThreats.insert(additionalThreats.begin(), additionalThreats.end());
            }
        }
    }

    // Looking for Coordinate in the setOfThreats
    if (setOfThreats.find(king.GetCoordinate()) != setOfThreats.end()) {
        return true;
    }
    else return false;
}
