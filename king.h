#ifndef KING_H
#define KING_H

#include "piece.h"
#include "move.h"

#include <set>
#include <vector>

class King : public Piece
{
public:
    King();
    King(char name, int coordinate);

    ~King() override;

    std::set<int> Threats(const std::vector<char> &vecBoardChar) const override;
    std::set<int> SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const override;
    bool IsProperMove(const Move &move, const std::vector<char> &vecBoardChar, int enPassant) const override;
    bool IsKingUnderCheck(const std::vector<char> &vecBoardChar) const;
    bool IsKingUnderCheck(King king, const std::vector<char> &vecBoardChar) const;


};

#endif // KING_H
