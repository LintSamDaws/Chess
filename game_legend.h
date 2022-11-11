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

public:
    GameLegend();

    void SetFileAddress (std::string fileAddress);
    std::string GetFileAddress();

    void SetNotationLine (std::string notationLine);
    std::string GetNotationLine();

    void SetMoveVector (const std::vector<Move> &moveVector);
    std::vector<Move> GetMoveVector();

    void AddMove(Move move, int moveCount);

    void PrintGameLegendNotation();
};

#endif // GAMELEGEND_H
