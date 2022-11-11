#ifndef PIECE_H
#define PIECE_H
#include "move.h"

#include <set>
#include <vector>

class Piece
{
protected:
    char name_;
    int coordinate_;

public:
    Piece();
    Piece(char name, int coordinate);

    virtual ~Piece() {}

    void SetName(char name);
    void SetCoordinate(int coordinate);

    char GetName() const;
    int GetCoordinate() const;

    virtual std::set<int> Threats(const std::vector<char> &vecBoardChar) const = 0;
    virtual std::set<int> SetOfPossibleMoves(const std::vector<char> &vecBoardChar, int enPassant) const = 0;
    virtual bool IsProperMove(const Move &move, const std::vector<char> &vecBoardChar, int enPassant) const = 0;
    void MakeMove(const Move &move);

};

#endif // PIECE_H

