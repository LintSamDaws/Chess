#include "board.h"
#include "piece.h"
#include "king.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "pawn.h"
#include "null_piece.h"

#include <iostream>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <string>
//#include <stdexcept>


namespace {
int sum(int a, int b) { return a+b; }

}


Board::Board () {}
Board::Board (int file, int rank) {
    file_ = file;
    rank_ = rank;
    moveCount_ = 0;
    enPassant_ = 0;
    castlingStates_.insert(std::pair<std::string, bool>("O-O", true));
    castlingStates_.insert(std::pair<std::string, bool>("O-O-O", true));
    castlingStates_.insert(std::pair<std::string, bool>("o-o", true));
    castlingStates_.insert(std::pair<std::string, bool>("o-o-o", true));
}
Board::Board (int file, int rank, std::string fen) {
    file_ = file;
    rank_ = rank;
    FEN = fen;
    vecBoardChar = FENtoVectorChar(fen);
    // Can be a problem if we are using FEN with next move enPassant
    enPassant_ = 0;
    if (fen == starting_position) {
        moveCount_ = 0;
        castlingStates_.insert(std::pair<std::string, bool>("O-O", true));
        castlingStates_.insert(std::pair<std::string, bool>("O-O-O", true));
        castlingStates_.insert(std::pair<std::string, bool>("o-o", true));
        castlingStates_.insert(std::pair<std::string, bool>("o-o-o", true));
    }
}

void Board::setMoveCount(int moveCount) {
    moveCount_ = moveCount;
}
int Board::GetMoveCount() const {
    return moveCount_;
}

void Board::setFEN(std::string fen) {
    FEN = fen;
    vecBoardChar = FENtoVectorChar(fen);
}
std::string Board::getFEN() const {
    return FEN;
}

void Board::setVecBoardChar(std::vector<char> vec){
    vecBoardChar = vec;
}
std::vector<char> Board::getVecBoardChar() const {
    return vecBoardChar;
}

std::vector<char> Board::FENtoVectorChar(std::string fen) {

    std::vector<char> vec(64);
    for (int i=0; i<64; i++) {
        vec[i] = '0';
    }

    // start fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

    int add = 0;
    for (int i=0; i<fen.size(); i++) {
        switch (fen[i]) {
        case '/':
            add -= 1;
            break;
        case 'p':
            vec[i+add] = 'p';
            break;
        case 'k':
            vec[i+add] = 'k';
            break;
        case 'n':
            vec[i+add] = 'n';
            break;
        case 'b':
            vec[i+add] = 'b';
            break;
        case 'r':
            vec[i+add] = 'r';
            break;
        case 'q':
            vec[i+add] = 'q';
            break;
        case 'P':
            vec[i+add] = 'P';
            break;
        case 'K':
            vec[i+add] = 'K';
            break;
        case 'N':
            vec[i+add] = 'N';
            break;
        case 'B':
            vec[i+add] = 'B';
            break;
        case 'R':
            vec[i+add] = 'R';
            break;
        case 'Q':
            vec[i+add] = 'Q';
            break;
        default:
            add += fen[i] - '0' - 1;
            break;
        }
    }
    return vec;
}

void Board::printVecBoardChar(const std::vector<char>& vecChar) const {
    int count = 0;
    for (int i=0; i<64; i++) {

        if (count % 8 == 0) std::cout << "\n";
        count++;

        std::cout << vecChar[i] << " ";
    }
    std::cout << "\n\n";
}
void Board::printVecBoardChar() const {
    int count = 0;
    for (int i=0; i<64; i++) {

        if (count % 8 == 0) std::cout << "\n";
        count++;

        std::cout << vecBoardChar[i] << " ";
    }
    std::cout << "\n\n";
}
void Board::printFEN(std::string fen) {

    int count=0;
    for (int i=0; i<fen.length(); i++) {

            if (isdigit(fen[i])) {
                int emptySquare = fen[i]-'0';
                for(int k = 0; k < emptySquare; k++) {
                    std::cout << 0 << "  ";
                }
            }
            else {
                switch (fen[i]) {
                case '/':
                    std::cout << "\n";
                    break;
                case 'p':
                    std::cout << 1 + 16 << " ";
                    break;
                case 'k':
                    std::cout << 2 + 16 << " ";
                    break;
                case 'n':
                    std::cout << 3 + 16 << " ";
                    break;
                case 'b':
                    std::cout << 4 + 16 << " ";
                    break;
                case 'r':
                    std::cout << 5 + 16 << " ";
                    break;
                case 'q':
                    std::cout << 6 + 16 << " ";
                    break;
                case 'P':
                    std::cout << 1 + 8 << "  ";
                    break;
                case 'K':
                    std::cout << 2 + 8 << " ";
                    break;
                case 'N':
                    std::cout << 3 + 8 << " ";
                    break;
                case 'B':
                    std::cout << 4 + 8 << " ";
                    break;
                case 'R':
                    std::cout << 5 + 8 << " ";
                    break;
                case 'Q':
                    std::cout << 6 + 8 << " ";
                    break;
                default:
                    break;
                }
            }
     }
    std::cout << "\n";
}

void Board::makeMove(const Move &move) {

    try {
        if (!IsRightMoveOrder(move) && isupper(move.getActivePiece())) throw std::range_error("Wrong Move Order.\nBlack to move!\n");
        if (!IsRightMoveOrder(move) && islower(move.getActivePiece())) throw std::range_error("Wrong Move Order.\nWhite to move!\n");

        // input move is like "pe2-e4" or "Qa1:a8" or "o-o-o" or "O-O"
        if ((move.getActivePiece() != vecBoardChar[move.getStartCoordinate()])
                && move.getActivePiece() != 'O' && move.getActivePiece() != 'o') throw std::range_error("The Piece is Not There\n");

        switch (move.getActivePiece()) {
            case 'R':
            case 'r':
            {
            if (move.isProperMoveRook(move, vecBoardChar)) {

                // Create testVec just to check the Hero's king is not under the check
                std::vector<char> testVec = vecBoardChar;
                testVec[move.getStartCoordinate()] = '0';
                testVec[move.getFinishCoordinate()] = move.getActivePiece();

                King king;
                if (islower(move.getActivePiece())) {
                    king.SetName('k');
                    king.SetCoordinate(FindTheKing('k', testVec));
                }
                else {
                    king.SetName('K');
                    king.SetCoordinate(FindTheKing('K', testVec));
                }

                if (!king.IsKingUnderCheck(testVec)) {
                    // The move is being made
                    makeMoveRook(move);
                }
                else std::cout << "The Move is Invalid\nThe King is under check\n";
            }
            else std::cout << "The Move is Invalid\n";
            break;
            }
            case 'B':
            case 'b':
            {
            if (move.isProperMoveBishop(move, vecBoardChar)) {

                // Create testVec just to check the Hero's king is not under the check
                std::vector<char> testVec = vecBoardChar;
                testVec[move.getStartCoordinate()] = '0';
                testVec[move.getFinishCoordinate()] = move.getActivePiece();

                King king;
                if (islower(move.getActivePiece())) {
                    king.SetName('k');
                    king.SetCoordinate(FindTheKing('k', testVec));
                }
                else {
                    king.SetName('K');
                    king.SetCoordinate(FindTheKing('K', testVec));
                }

                if (!king.IsKingUnderCheck(testVec)) {
                    // The move is being made
                    makeMoveBishop(move);
                }
                else std::cout << "The Move is Invalid\nThe King is under check\n";
            }
            else std::cout << "The Move is Invalid\n";
            break;
            }
            case 'Q':
            case 'q':
            {
            if (move.isProperMoveQueen(move, vecBoardChar)) {

                // Create testVec just to check the Hero's king is not under the check
                std::vector<char> testVec = vecBoardChar;
                testVec[move.getStartCoordinate()] = '0';
                testVec[move.getFinishCoordinate()] = move.getActivePiece();

                King king;
                if (islower(move.getActivePiece())) {
                    king.SetName('k');
                    king.SetCoordinate(FindTheKing('k', testVec));
                }
                else {
                    king.SetName('K');
                    king.SetCoordinate(FindTheKing('K', testVec));
                }

                if (!king.IsKingUnderCheck(testVec)) {
                    // The move is being made
                    makeMoveQueen(move);
                }
                else std::cout << "The Move is Invalid\nThe King is under check\n";
            }
            else std::cout << "The Move is Invalid\n";
            break;
            }
            case 'N':
            case 'n':
            {
            if (move.isProperMoveKnight(move, vecBoardChar)) {

                // Create testVec just to check the Hero's king is not under the check
                std::vector<char> testVec = vecBoardChar;
                testVec[move.getStartCoordinate()] = '0';
                testVec[move.getFinishCoordinate()] = move.getActivePiece();

                King king;
                if (islower(move.getActivePiece())) {
                    king.SetName('k');
                    king.SetCoordinate(FindTheKing('k', testVec));
                }
                else {
                    king.SetName('K');
                    king.SetCoordinate(FindTheKing('K', testVec));
                }

                if (!king.IsKingUnderCheck(testVec)) {
                    // The move is being made
                    makeMoveKnight(move);
                }
                else std::cout << "The Move is Invalid\nThe King is under check\n";
            }
            else std::cout << "The Move is Invalid\n";
            break;
            }
            case 'P':
            case 'p':
            {
                if (move.isProperMovePawn(move, vecBoardChar)) {

                    // Create testVec just to check the Hero's king is not under the check
                    std::vector<char> testVec = vecBoardChar;
                    testVec[move.getStartCoordinate()] = '0';
                    testVec[move.getFinishCoordinate()] = move.getActivePiece();

                    King king;
                    if (islower(move.getActivePiece())) {
                        king.SetName('k');
                        king.SetCoordinate(FindTheKing('k', testVec));
                    }
                    else {
                        king.SetName('K');
                        king.SetCoordinate(FindTheKing('K', testVec));
                    }

                    if (!king.IsKingUnderCheck(testVec)) {
                        // The move is being made
                        makeMovePawn(move);
                    }
                    else std::cout << "The Move is Invalid\nThe King is under check\n";
                }
                else std::cout << "The Move is Invalid\n";
                break;
            }
            case 'K':
            case 'k':
            {
            if (move.isProperMoveKing(move, vecBoardChar)) {

                // Create testVec just to check the Hero's king is not under the check
                std::vector<char> testVec = vecBoardChar;
                testVec[move.getStartCoordinate()] = '0';
                testVec[move.getFinishCoordinate()] = move.getActivePiece();

                King king;
                if (islower(move.getActivePiece())) {
                    king.SetName('k');
                    king.SetCoordinate(FindTheKing('k', testVec));
                }
                else {
                    king.SetName('K');
                    king.SetCoordinate(FindTheKing('K', testVec));
                }

                if (!king.IsKingUnderCheck(testVec)) {
                    // The move is being made
                    makeMoveKing(move);
                }
                else std::cout << "The Move is Invalid\nThe King is under check\n";
            }
            else std::cout << "The Move is Invalid\n";
            break;
            }
            case 'O':
            case 'o':
            {
            if (move.IsCastlingPossible(move, vecBoardChar, castlingStates_)) {
                    MakeMoveCastling(move);
            }
            else std::cout << "Such Castling is Invalid\n";

            break;
            }
            default:
            {
                std::cout << "No such Piece\n";
                break;
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}
void Board::makeMove2(const Move &move) {

    try {
        if (!IsRightMoveOrder(move) && isupper(move.getActivePiece())) throw std::range_error("Wrong Move Order.\nBlack to move!\n");
        if (!IsRightMoveOrder(move) && islower(move.getActivePiece())) throw std::range_error("Wrong Move Order.\nWhite to move!\n");

        // input move is like "pe2-e4" or "Qa1:a8" or "o-o-o" or "O-O"
        if ((move.getActivePiece() != vecBoardChar[move.getStartCoordinate()])
                && move.getActivePiece() != 'O' && move.getActivePiece() != 'o') throw std::range_error("The Piece is Not There\n");

        static NullPiece nullPiece;
        Piece* activePiece = &nullPiece;

        static Rook rook;
        static Bishop bishop;
        static Queen queen;
        static Knight knight;
        static Pawn pawn;
        static King kingToMove;

        switch (move.getActivePiece()) {
            case 'R':
            case 'r':
            {
                activePiece = &rook;
                break;
            }
            case 'B':
            case 'b':
            {
                activePiece = &bishop;
                break;
            }
            case 'Q':
            case 'q':
            {
                activePiece = &queen;
                break;
            }
            case 'N':
            case 'n':
            {
                activePiece = &knight;
                break;
            }
            case 'P':
            case 'p':
            {
                activePiece = &pawn;
                break;
            }
            case 'K':
            case 'k':
            {
                activePiece = &kingToMove;
                break;
            }
            case 'O':
            case 'o':
            {
            if (move.IsCastlingPossible(move, vecBoardChar, castlingStates_)) {
                    MakeMoveCastling(move);
            }
            else throw std::range_error("Such Castling is Invalid\n");

            break;
            }
            default:
            {
                throw std::range_error("There is no such Piece\n");
                break;
            }
        }
        activePiece->SetName(move.getActivePiece());
        activePiece->SetCoordinate(move.getStartCoordinate());

        if (activePiece->IsProperMove(move, vecBoardChar)) {

            // Create testVec just to check the Hero's king is not under the check
            std::vector<char> testVec = vecBoardChar;
            testVec[move.getStartCoordinate()] = '0';
            testVec[move.getFinishCoordinate()] = move.getActivePiece();

            King king;
            if (islower(move.getActivePiece())) {
                king.SetName('k');
                king.SetCoordinate(FindTheKing('k', testVec));
            }
            else {
                king.SetName('K');
                king.SetCoordinate(FindTheKing('K', testVec));
            }

            if (!king.IsKingUnderCheck(testVec)) {
                // The move is being made
                vecBoardChar[move.getStartCoordinate()] = '0';
                vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();
                Move::enPassant = 0;
            }
            else throw std::range_error("The Move is Invalid\nThe King is under check\n");
        }
        else throw std::range_error("The Move is Invalid\n");
    }
    // Exception Handling
    catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}

void Board::makeMoveRook(const Move &move) {
    vecBoardChar[move.getStartCoordinate()] = '0';
    vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();
    Move::enPassant = 0;
    enPassant_ = 0;
    moveCount_++;
    if (move.getStartCoordinate() == 56) castlingStates_["O-O-O"] = false;
    if (move.getStartCoordinate() == 63) castlingStates_["O-O"] = false;
    if (move.getStartCoordinate() == 0) castlingStates_["o-o-o"] = false;
    if (move.getStartCoordinate() == 7) castlingStates_["o-o"] = false;
}
void Board::makeMoveBishop(const Move &move) {
    vecBoardChar[move.getStartCoordinate()] = '0';
    vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();
    Move::enPassant = 0;
    enPassant_ = 0;
    moveCount_++;
}
void Board::makeMoveQueen(const Move &move) {
    vecBoardChar[move.getStartCoordinate()] = '0';
    vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();
    Move::enPassant = 0;
    enPassant_ = 0;
    moveCount_++;
}
void Board::makeMoveKnight(const Move &move) {
    vecBoardChar[move.getStartCoordinate()] = '0';
    vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();
    Move::enPassant = 0;
    enPassant_ = 0;
    moveCount_++;
}

void Board::makeMovePawn(const Move &move) {

    // Check for en-Passant Opportunity on the next move.
    // If en-Passant is possible, set enPassant value = field on the 3rd rank for White, 6th rank for Black
    if (move.getActivePiece() == 'P' && move.getStartCoordinate() / 8 == 6 && move.getFinishCoordinate() / 8 == 4) {
         Move::enPassant = move.getStartCoordinate() - 8;
         enPassant_ = move.getStartCoordinate() - 8;
    }
    else {
        if (move.getActivePiece() == 'p' && move.getStartCoordinate() / 8 == 1 && move.getFinishCoordinate() / 8 == 3) {
            Move::enPassant = move.getStartCoordinate() + 8;
            enPassant_ = move.getStartCoordinate() + 8;
        }
        else {
            Move::enPassant = 0;
            enPassant_ = 0;
        }
    }

    // Check if the Pawn can be Promoted
    if ((move.getActivePiece() == 'P' && move.getFinishCoordinate() / 8 == 0) || (move.getActivePiece() == 'p' && move.getFinishCoordinate() / 8 == 7)) {
        char promotion;
        promotion = pawnPromotion(move);
        vecBoardChar[move.getStartCoordinate()] = '0';
        vecBoardChar[move.getFinishCoordinate()] = promotion;
    }
    else {
        vecBoardChar[move.getStartCoordinate()] = '0';

        // Manage en-Passand case for White
        if (vecBoardChar[move.getFinishCoordinate()] == '0' && move.getActivePiece() == 'P') {
            vecBoardChar[move.getFinishCoordinate() + 8] = '0';
        }
        // for Black
        if (vecBoardChar[move.getFinishCoordinate()] =='0' && move.getActivePiece() == 'p') {
            vecBoardChar[move.getFinishCoordinate() - 8] = '0';
        }
        vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();
    }
    moveCount_++;
}

char Board::pawnPromotion(const Move &move) {
    char promotion;
    std::cout << "To what piece do you want to promote your pawn?\n";
    std::cout << "Q or q: queen\n";
    std::cout << "R or r: rook\n";
    std::cout << "B or b: bishop\n";
    std::cout << "N or n: knight\n";
    std::cin >> promotion;
    if (islower(move.getActivePiece())) promotion = tolower(promotion);
    else promotion = toupper(promotion);
    return promotion;
}

int Board::FindTheKing(char name, const std::vector<char>& vecChar) const {
    int res;
    for (int i=0; i<64; i++) {
        if (vecChar[i] == name) {
            res = i;
        }
    }
    return res;
}
int Board::FindTheKing(char name) const {
    int res;
    for (int i=0; i<64; i++) {
        if (vecBoardChar[i] == name) {
            res = i;
        }
    }
    return res;
}
void Board::makeMoveKing(const Move &move) {
    vecBoardChar[move.getStartCoordinate()] = '0';
    vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();
    Move::enPassant = 0;
    enPassant_ = 0;
    moveCount_++;
    if (isupper(move.getActivePiece())) {
        castlingStates_["O-O-O"] = false;
        castlingStates_["O-O"] = false;
    }
    if (islower(move.getActivePiece())) {
        castlingStates_["o-o-o"] = false;
        castlingStates_["o-o"] = false;
    }
}

void Board::MakeMoveCastling(const Move &move) {

    // Castling for White
    if (isupper(move.getActivePiece())) {
        // Long Castling
        if (move.getFinishCoordinate() == 56) {
            vecBoardChar[56] = '0';
            vecBoardChar[60] = '0';
            vecBoardChar[58] = 'K';
            vecBoardChar[59] = 'R';
        }
        // Short
        else {
            vecBoardChar[60] = '0';
            vecBoardChar[63] = '0';
            vecBoardChar[62] = 'K';
            vecBoardChar[61] = 'R';
        }
    }
    // Castling for Black
    else {
        // Long Castling
        if (move.getFinishCoordinate() == 0) {
            vecBoardChar[0] = '0';
            vecBoardChar[4] = '0';
            vecBoardChar[2] = 'K';
            vecBoardChar[3] = 'R';
        }
        // Short
        else {
            vecBoardChar[4] = '0';
            vecBoardChar[7] = '0';
            vecBoardChar[6] = 'k';
            vecBoardChar[5] = 'r';
        }
    }
    Move::enPassant = 0;
    enPassant_ = 0;
    moveCount_++;
}

bool Board::IsStaleMate() const {

    // Spot the King. White or Black
    int kingCoordinate;
    char kingName;
    if (moveCount_ % 2 == 0) {
        kingCoordinate = FindTheKing('K');
        kingName = 'K';
    }
    else {
        kingCoordinate = FindTheKing('k');
        kingName = 'k';
    }

    // If the King is under check there is no Stalemate
    King king(kingName, kingCoordinate);
    if (king.IsKingUnderCheck(vecBoardChar)) {
        return false;
    }
    // Check if one of all other pieces has the Possible Move
    else {
        for (int i=0; i<64; i++) {

            Piece& activePiece = GetSameColorPiece(kingName, i);

            if (vecBoardChar[i] != '0' && ((islower(kingName) && islower(vecBoardChar[i])) || (isupper(kingName) && isupper(vecBoardChar[i])))) {

                std::set<int> setOfPossibleMoves;
                setOfPossibleMoves = activePiece.SetOfPossibleMoves(vecBoardChar, enPassant_);

                for (int moveFromSet : setOfPossibleMoves) {
                    // Create testVec just to check the Hero's king is not under the check
                    std::vector<char> testVec = vecBoardChar;
                    testVec[activePiece.GetCoordinate()] = '0';
                    testVec[moveFromSet] = activePiece.GetName();

                    // In case of King Move
                    if (activePiece.GetName() == 'K' || activePiece.GetName() == 'k') {
                        King newKing(activePiece.GetName(), activePiece.GetCoordinate());
                        newKing.SetCoordinate(moveFromSet);
                        if (!newKing.IsKingUnderCheck(testVec)) return false;
                    }
                    else {
                        if (!king.IsKingUnderCheck(testVec)) return false;
                    }
                }
            }
        }
    }
    return true;
}

Piece& Board::GetSameColorPiece(char kingName, int coordinate) const {

    static NullPiece nullPiece;
    Piece* activePiece = &nullPiece;

    static Rook rook;
    static Bishop bishop;
    static Queen queen;
    static Knight knight;
    static Pawn pawn;
    static King kingToMove;

    switch (vecBoardChar[coordinate]) {
        case 'R':
        {
            if (isupper(kingName)) {
                activePiece = &rook;
            }
            break;
        }
        case 'r':
        {
            if (islower(kingName)) {
                activePiece = &rook;
            }
            break;
        }
        case 'B':
        {
            if (isupper(kingName)) {
                activePiece = &bishop;
            }
            break;
        }
        case 'b':
        {
            if (islower(kingName)) {
                activePiece = &bishop;
            }
            break;
        }
        case 'Q':
        {
            if (isupper(kingName)) {
                activePiece = &queen;
            }
            break;
        }
        case 'q':
        {
            if (islower(kingName)) {
                activePiece = &queen;
            }
            break;
        }
        case 'N':
        {
            if (isupper(kingName)) {
                activePiece = &knight;
            }
            break;
        }
        case 'n':
        {
            if (islower(kingName)) {
                activePiece = &knight;
            }
            break;
        }
        case 'P':
        {
            if (isupper(kingName)) {
                activePiece = &pawn;
            }
            break;
        }
        case 'p':
        {
            if (islower(kingName)) {
                activePiece = &pawn;
            }
            break;
        }
        case 'K':
        {
            if (isupper(kingName)) {
                activePiece = &kingToMove;
            }
            break;
        }
        case 'k':
        {
            if (islower(kingName)) {
                activePiece = &kingToMove;
            }
            break;
        }
        default:
        {
            break;
        }
    }
    activePiece->SetName(vecBoardChar[coordinate]);
    activePiece->SetCoordinate(coordinate);
    return *activePiece;
}

bool Board::IsCheckMate() const {

    // Spot the King. White or Black. Initialize it.
    int kingCoordinate;
    char kingName;
    if (moveCount_ % 2 == 0) {
        kingCoordinate = FindTheKing('K');
        kingName = 'K';
    }
    else {
        kingCoordinate = FindTheKing('k');
        kingName = 'k';
    }

    // If the King is not under check there is no Checkmate
    King king(kingName, kingCoordinate);


    if (!king.IsKingUnderCheck(vecBoardChar)) {
        return false;
    }
    // Check if the King or one of other pieces has the Possible Move
    else {
        for (int i=0; i<64; i++) {

            Piece& activePiece = GetSameColorPiece(kingName, i);

            if (vecBoardChar[i] != '0' && ((islower(kingName) && islower(vecBoardChar[i])) || (isupper(kingName) && isupper(vecBoardChar[i])))) {

                std::set<int> setOfPossibleMoves;
                setOfPossibleMoves = activePiece.SetOfPossibleMoves(vecBoardChar, enPassant_);

                for (int moveFromSet : setOfPossibleMoves) {

                    // Create testVec just to check the Hero's king is not under the check
                    std::vector<char> testVec = vecBoardChar;
                    testVec[activePiece.GetCoordinate()] = '0';
                    testVec[moveFromSet] = activePiece.GetName();

                    // In case of King Move
                    if (activePiece.GetName() == 'K' || activePiece.GetName() == 'k') {
                        King newKing(activePiece.GetName(), activePiece.GetCoordinate());
                        newKing.SetCoordinate(moveFromSet);

//                        printVecBoardChar(testVec);
//                        std::cout << activePiece.GetCoordinate() << "^^^" << activePiece.GetName() << "\n";
//                        std::cout << king.GetCoordinate() << "^^^" << king.GetName() << "\n";
                    if (!newKing.IsKingUnderCheck(testVec)) {
//                        std::cout << "Here we go. No check\n" << activePiece.GetName() << " ^ " << activePiece.GetCoordinate() << "\n";
                        return false;
                    }

                    }
                    else {

//                        printVecBoardChar(testVec);
//                        std::cout << activePiece.GetCoordinate() << "^^^" << activePiece.GetName() << "\n";
//                        std::cout << king.GetCoordinate() << "^^^" << king.GetName() << "\n";

                        if (!king.IsKingUnderCheck(testVec)) {

//                            std::cout << "Here we go. No check\n" << activePiece.GetName() << " ^ " << activePiece.GetCoordinate() << "\n";
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

std::string Board::createFEN() const {

    std::string fen = "";
    int count = 0;
    for (int i=0; i<64; i++) {
        if (vecBoardChar[i] != '0') {
            fen += vecBoardChar[i];
        }
        else {
            count++;
            if ((i != 63 && vecBoardChar[i+1] != '0') || (i % 8 == 7 && count != 0)) {
                std::string temp = std::to_string(count);
                fen += temp;
                count = 0;
            }
        }
        if (i % 8 == 7 && i != 63) fen += "/";
    }
    return fen;
}
std::string Board::createFEN(const std::vector<char>& vecChar) const {

    std::string fen = "";
    int count = 0;
    for (int i=0; i<64; i++) {
        if (vecChar[i] != '0') {
            fen += vecChar[i];
        }
        else {
            count++;
            if ((i != 63 && vecChar[i+1] != '0') || (i % 8 == 7 && count != 0)) {
                std::string temp = std::to_string(count);
                fen += temp;
                count = 0;
            }
        }
        if (i % 8 == 7 && i != 63) fen += "/";
    }
    return fen;
}

bool Board::IsRightMoveOrder(const Move &move) const {
    if ((moveCount_ % 2 == 0 && isupper(move.getActivePiece())) || (moveCount_ % 2 == 1 && islower(move.getActivePiece()))) {
        return true;
    }
    else return false;
}






































