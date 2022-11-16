#include "game_legend.h"

GameLegend::GameLegend() {}

void GameLegend::SetFileAddress(std::string fileAddress)
{
    fileAddress_ = fileAddress;
}
std::string GameLegend::GetFileAddress() const
{
    return fileAddress_;
}

void GameLegend::SetNotationLine(std::string notationLine)
{
    notationLine_ = notationLine;
}
std::string GameLegend::GetNotationLine() const
{
    return notationLine_;
}

void GameLegend::SetMoveVector(const std::vector<Move> &moveVector)
{
    moveVector_ = moveVector;
}
std::vector<Move> GameLegend::GetMoveVector() const
{
    return moveVector_;
}

void GameLegend::SetMoveCount(int moveCount)
{
    moveCount_ = moveCount;
}
int GameLegend::GetMoveCount() const
{
    return moveCount_;
}

// Not used yet
void GameLegend::MoveCountPlusPlus() {
    moveCount_++;
}

void GameLegend::AddMove(Move move)
{
    notationLine_ += std::to_string(moveCount_ + 1) + ". " + move.GetNotation() + "\n";
    moveVector_.push_back(move);
}

void GameLegend::PrintGameLegendNotation() {
    std::cout << notationLine_;
}

