#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "move.h"

#include <vector>
#include <set>

class Queen : public Piece
{
public:
    Queen();
    Queen(char name, int coordinate);

    ~Queen() override;

    std::set<int> Threats(const std::vector<char> &vecBoardChar) const override;
    std::set<int> SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const override;
    bool IsProperMove(const Move &move, const std::vector<char> &vecBoardChar, int enPassant) const override;
};

#endif // QUEEN_H
