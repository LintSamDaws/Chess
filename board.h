#ifndef BOARD_H
#define BOARD_H

#include "move.h"
#include "piece.h"
#include "board_state.h"
#include <vector>
#include <string>
#include <unordered_map>


// Use Forsyth-Edwards Notation (FEN)
// Starting position
#define starting_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"


// Forward declaration to resolve circular dependency/include
class BoardState;
class Move;

enum class GameResult { OnAction,
                        Draw,
                        WhiteWon,
                        BlackWon,
                        ForcedQuit};

class Board {

    std::string FEN;
    std::vector<char> vecBoardChar;
    int moveCount_;
    int enPassant_;
    std::unordered_map<std::string, bool> castlingStates_;
    Move move_;
    BoardState* currentState_;
    GameResult gameResult_;


public:

    Board ();
    Board (std::string fen);

    void GameOn();

    inline BoardState* getCurrentState() const { return currentState_; }
    void toggle();
    void setState(BoardState &newState);

    void SetEnPassant(int enPassant);
    int GetEnPassant() const;
    void SetGameResult(GameResult gameResult);
    GameResult GetGameResult() const;
    void setMoveCount(int moveCount);
    int GetMoveCount() const;
    void setMove(Move &move);
    Move GetMove() const;
    void setFEN(std::string fen);
    std::string getFEN() const;
    void setVecBoardChar(std::vector<char> vec);
    std::vector<char> getVecBoardChar() const;
    std::vector<char> FENtoVectorChar(std::string fen);
    void printVecBoardChar(const std::vector<char>& vecChar) const;
    void printVecBoardChar() const;
    void printFEN(std::string fen);
    void makeMove();
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
