#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "move.h"

#include <vector>
#include <set>

class Pawn : public Piece
{
public:
    Pawn();
    Pawn(char name, int coordinate);

    ~Pawn() override;

    std::set<int> Threats(const std::vector<char> &vecBoardChar) const override;
    std::set<int> SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const override;
    bool IsProperMove(const Move &move, const std::vector<char> &vecBoardChar, int enPassant) const override;
};

#endif // PAWN_H
