#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "move.h"

#include <vector>
#include <set>

class Rook : public Piece
{
public:
    Rook();
    Rook(char name, int coordinate);

    ~Rook() override;

    std::set<int> Threats(const std::vector<char> &vecBoardChar) const override;
    std::set<int> SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const override;
    bool IsProperMove(const Move &move, const std::vector<char> &vecBoardChar, int enPassant) const override;
};

#endif // ROOK_H
