#ifndef NULL_PIECE_H
#define NULL_PIECE_H

#include "piece.h"

class NullPiece : public Piece
{
public:
    NullPiece();
    NullPiece(char name, int coordinate);

    ~NullPiece() override;

    std::set<int> Threats(const std::vector<char> &vecBoardChar) const override;
    std::set<int> SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const override;
    bool IsProperMove(const Move &move, const std::vector<char> &vecBoardChar) const override;
};

#endif // NULL_PIECE_H
