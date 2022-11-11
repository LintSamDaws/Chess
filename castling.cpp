#include "castling.h"


Castling::Castling() {}

Castling::Castling(std::string fen) {

    if (fen == starting_position) {
        castlingStates_.insert(std::pair<std::string, bool>("O-O", true));
        castlingStates_.insert(std::pair<std::string, bool>("O-O-O", true));
        castlingStates_.insert(std::pair<std::string, bool>("o-o", true));
        castlingStates_.insert(std::pair<std::string, bool>("o-o-o", true));
    }
}

std::unordered_map<std::string, bool> Castling::GetCastlingStates() {
    return castlingStates_;
}
void Castling::SetCastlingStates (std::unordered_map<std::string, bool> castlingStates) {
    castlingStates_ = castlingStates;
}

bool Castling::IsKingUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const {
    char name;
    int coordinate;
    if (isupper(move.getActivePiece())) name = 'K';
    else name = 'k';
    coordinate = move.getStartCoordinate();
    King king(name, coordinate);
    if (king.IsKingUnderCheck(vecBoardChar)) return true;
    else return false;
}

bool Castling::NoPieceBetweenCastling(const Move &move, const std::vector<char> &vecBoardChar) const {

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

bool Castling::IsCastlingSquaresUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const {
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

bool Castling::NOTMovedCastling(const Move &move) const {
    bool res = true;
    if (move.getFinishCoordinate() == 56) res = castlingStates_.at("O-O-O");
    if (move.getFinishCoordinate() == 63) res = castlingStates_.at("O-O");
    if (move.getFinishCoordinate() == 0) res = castlingStates_.at("o-o-o");
    if (move.getFinishCoordinate() == 7) res = castlingStates_.at("o-o");
    return res;
}

bool Castling::IsCastlingPossible(const Move &move, const std::vector<char> &vecBoardChar) const {

    if (NOTMovedCastling(move) && NoPieceBetweenCastling(move, vecBoardChar) && !IsKingUnderCheck(move, vecBoardChar) && !IsCastlingSquaresUnderCheck(move, vecBoardChar)) return true;
    else return false;
}

void Castling::SwitchState(const Move &move) {
    if (move.GetNotation() == "o-o" || move.GetNotation() == "o-o-o" || move.getActivePiece() == 'k') {
        castlingStates_.at("o-o") = false;
        castlingStates_.at("o-o-o") = false;
    }
    if (move.GetNotation() == "O-O" || move.GetNotation() == "O-O-O" || move.getActivePiece() == 'K') {
        castlingStates_.at("O-O") = false;
        castlingStates_.at("O-O-O") = false;
    }
    if (move.getActivePiece() == 'r' && move.getStartCoordinate() == 7) castlingStates_.at("o-o") = false;
    if (move.getActivePiece() == 'r' && move.getStartCoordinate() == 0) castlingStates_.at("o-o-o") = false;
    if (move.getActivePiece() == 'R' && move.getStartCoordinate() == 63) castlingStates_.at("O-O") = false;
    if (move.getActivePiece() == 'R' && move.getStartCoordinate() == 56) castlingStates_.at("O-O-O") = false;
}
