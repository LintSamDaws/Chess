#ifndef BOARD_H
#define BOARD_H

#include "move.h"
#include "piece.h"

#include <vector>
#include <string>
#include <unordered_map>


// Use Forsyth-Edwards Notation (FEN)
// Starting position
#define starting_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

class Move;

class Board {
    int file_;
    int rank_;
    std::string FEN;
    std::vector<char> vecBoardChar;
    int moveCount_;
    std::unordered_map<std::string, bool> castlingStates_;
    int enPassant_;

public:

    Board ();
    Board (int file, int rank);
    Board (int file, int rank, std::string fen);
    void setMoveCount(int moveCount);
    int GetMoveCount() const;
    void setFEN(std::string fen);
    std::string getFEN() const;
    void setVecBoardChar(std::vector<char> vec);
    std::vector<char> getVecBoardChar() const;
    std::vector<char> FENtoVectorChar(std::string fen);
    void printVecBoardChar(const std::vector<char>& vecChar) const;
    void printVecBoardChar() const;
    void printFEN(std::string fen);
    void makeMove(const Move &move);
    void makeMove2(const Move &move);
    void makeMoveRook(const Move &move);
    void makeMoveBishop(const Move &move);
    void makeMoveQueen(const Move &move);
    void makeMoveKnight(const Move &move);
    void makeMovePawn(const Move &move);
    char pawnPromotion(const Move &move);
    int FindTheKing(char name, const std::vector<char>& vecChar) const;
    int FindTheKing(char name) const;
    void makeMoveKing(const Move &move);
    void MakeMoveCastling(const Move &move);
    bool IsStaleMate() const;
    Piece& GetSameColorPiece(char kingName, int coordinate) const;
    bool IsCheckMate() const;
    std::string createFEN() const;
    std::string createFEN(const std::vector<char>& vecChar) const;
    bool IsRightMoveOrder(const Move &move) const;

};




#endif // BOARD_H