#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "move.h"

#include <vector>
#include <set>

class Bishop : public Piece
{
public:
    Bishop();
    Bishop(char name, int coordinate);

    ~Bishop() override;

    std::set<int> Threats(const std::vector<char> &vecBoardChar) const override;
    std::set<int> SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const override;
    bool IsProperMove(const Move &move, const std::vector<char> &vecBoardChar) const override;
};

#endif // BISHOP_H
