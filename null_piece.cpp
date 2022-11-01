#include "null_piece.h"

NullPiece::NullPiece() {}
NullPiece::NullPiece(char name, int coordinate) : Piece(name, coordinate) {}

NullPiece::~NullPiece() {}

std::set<int> NullPiece::Threats(const std::vector<char> &vecBoardChar) const {
    return {};
}

std::set<int> NullPiece::SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const {
    return {};
}

bool NullPiece::IsProperMove(const Move &move, const std::vector<char> &vecBoardChar) const {
    return false;
}
