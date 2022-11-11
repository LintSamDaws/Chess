#include "game_legend.h"

GameLegend::GameLegend() {}

void GameLegend::SetFileAddress(std::string fileAddress)
{
    fileAddress_ = fileAddress;
}
std::string GameLegend::GetFileAddress()
{
    return fileAddress_;
}

void GameLegend::SetNotationLine(std::string notationLine)
{
    notationLine_ = notationLine;
}
std::string GameLegend::GetNotationLine()
{
    return notationLine_;
}

void GameLegend::SetMoveVector(const std::vector<Move> &moveVector)
{
    moveVector_ = moveVector;
}
std::vector<Move> GameLegend::GetMoveVector()
{
    return moveVector_;
}

void GameLegend::AddMove(Move move, int moveCount)
{
    notationLine_ += std::to_string(moveCount + 1) + ". " + move.GetNotation() + "\n";
    moveVector_.push_back(move);
}

void GameLegend::PrintGameLegendNotation() {
    std::cout << notationLine_;
}

