#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "move.h"

#include <vector>
#include <set>

class Knight : public Piece
{
public:
    Knight();
    Knight(char name, int coordinate);

    ~Knight() override;

    std::set<int> Threats(const std::vector<char> &vecBoardChar) const override;
    std::set<int> SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const override;
    bool IsProperMove(const Move &move, const std::vector<char> &vecBoardChar) const override;
};

#endif // KNIGHT_H
