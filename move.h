#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

class Board;

class Move {
    char activePiece;
    int startCoordinate;
    int finishCoordinate;

public:

    static int enPassant;

    Move();
    Move(std::string move);
    void setMove(const Move &move);
    void setActivePiece(char piece);
    void setStartCoordinate(int coordinate);
    void setFinishCoordinate(int coordinate);
    char getActivePiece() const;
    int getStartCoordinate() const;
    int getFinishCoordinate() const;
    std::set<int> linearThreat(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool isProperMoveRook(const Move &move, const std::vector<char> &vecBoardChar) const;
    std::set<int> diagonalThreat(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool isProperMoveBishop(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool isProperMoveQueen(const Move &move, const std::vector<char> &vecBoardChar) const;
    std::set<int> knightThreat(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool isProperMoveKnight(const Move &move, const std::vector<char> &vecBoardChar) const;
    std::set<int> pawnThreat(const Move &move, const std::vector<char> &vecBoardChar) const;
    std::set<int> setOfPossiblePawnMoves(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool isProperMovePawn(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool villainKingIsUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const;
    std::set<int> setOfPossibleKingMoves(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool isProperMoveKing(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool NOTMovedCastling(const Move &move, const std::unordered_map<std::string, bool> &castlingStates) const;
    bool NoPieceBetweenCastling(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool IsKingUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool IsCastlingSquaresUnderCheck(const Move &move, const std::vector<char> &vecBoardChar) const;
    bool IsCastlingPossible(const Move &move, const std::vector<char> &vecBoardChar, const std::unordered_map<std::string, bool> &castlingStates) const;


};

#endif // MOVE_H
