#ifndef CASTLING_H
#define CASTLING_H


#include "king.h"

#include <string>
#include <unordered_map>
#include <vector>

#define starting_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

class Castling
{
private:
    std::unordered_map<std::string, bool> castlingStates_;

public:
    Castling();
    Castling(std::string fen);

    std::unordered_map<std::string, bool> GetCastlingStates();
    void SetCastlingStates(std::unordered_map<std::string, bool> castlingStates);

    bool IsKingUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool NoPieceBetweenCastling(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool IsCastlingSquaresUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool NOTMovedCastling(const Move &move) const;
    bool IsCastlingPossible(const Move &move, const std::vector<char> &vecBoardChar) const;
    void SwitchState(const Move &move);
    void MakeMoveCastling(const Move &move, std::vector<char> &vecBoardChar);
};

#endif // CASTLING_H
