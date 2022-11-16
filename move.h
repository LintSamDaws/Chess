#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>

class Board;

class Move {
    char activePiece;
    int startCoordinate;
    int finishCoordinate;
    std::string notation_;

public:

    friend std::ostream& operator<<(std::ostream& stream, const Move move);

    Move();
    Move(std::string move);
    void setMove(const Move &move);

    void setActivePiece(char piece);
    void setStartCoordinate(int coordinate);
    void SetNotation(std::string notation);
    void setFinishCoordinate(int coordinate);

    char getActivePiece() const;
    int getStartCoordinate() const;
    int getFinishCoordinate() const;
    std::string GetNotation() const;

    bool IsLegitNotation(std::string move) const;

};

#endif // MOVE_H
