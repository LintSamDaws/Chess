#ifndef GAMELEGEND_H
#define GAMELEGEND_H

#include "move.h"

#include <string>
#include <vector>


class GameLegend
{
private:
    std::string fileAddress_;
    std::string notationLine_;
    std::vector<Move> moveVector_;
    int moveCount_;

public:
    GameLegend();

    void SetFileAddress (std::string fileAddress);
    std::string GetFileAddress() const;

    void SetNotationLine (std::string notationLine);
    std::string GetNotationLine() const;

    void SetMoveVector (const std::vector<Move> &moveVector);
    std::vector<Move> GetMoveVector() const;

    void SetMoveCount (int moveCount);
    int GetMoveCount() const;

    // Not used yet
    void MoveCountPlusPlus();

    void AddMove(Move move);

    void PrintGameLegendNotation();

};

#endif // GAMELEGEND_H
