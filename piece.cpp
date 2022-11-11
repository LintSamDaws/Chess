#include "piece.h"

#include <set>


Piece::Piece() {}
Piece::Piece(char name, int coordinate) {
    name_ = name;
    coordinate_ = coordinate;
}

void Piece::SetName(char name) {
    name_ = name;
}
void Piece::SetCoordinate(int coordinate) {
    coordinate_ = coordinate;
}

char Piece::GetName() const {
    return name_;
}
int Piece::GetCoordinate() const {
    return coordinate_;
}

// The Piece changes its coordinate_
void Piece::MakeMove(const Move &move)
{
    coordinate_ = move.getFinishCoordinate();
}

