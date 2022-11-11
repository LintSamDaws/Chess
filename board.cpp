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

#include "state_base.h"
#include "state_exit.h"


Board::Board () {}
Board::Board (std::string fen) : gameLegend_(), castling_(fen) {

    if (fen == starting_position) {
        FEN = fen;
        vecBoardChar = FENtoVectorChar(fen);
        vecBoardPiece_ = SetStartingPositionVecBoardPiece();
        moveCount_ = 0;
        enPassant_ = 0;
        currentState_ = &StateBase::getInstance();
        gameResult_ = GameResult::OnAction;
    }
    else {
        FEN = fen;
        vecBoardChar = FENtoVectorChar(fen);
        // Can be a problem if we are using FEN with next move enPassant_
    }
}

// Start of the Game. State Machine
void Board::GameOn() {
    while(true) {
        this->toggle();
        if (currentState_ == &StateExit::getInstance()) {
            this->toggle();
            break;
        }
    }
}

void Board::setState(BoardState& newState)
{
    currentState_ = &newState;  // actually change states now
}
void Board::toggle()
{
    // Delegate the task of determining the next state to the current state
    currentState_->toggle(*this);
}

void Board::SetGameLegend(GameLegend gameLegend)
{
    gameLegend_ = gameLegend;
}
GameLegend Board::GetGameLegend()
{
    return gameLegend_;
}

void Board::setMove(Move &move) {
    move_ = move;
}
Move Board::GetMove() const {
    return move_;
}

void Board::setMoveCount(int moveCount) {
    moveCount_ = moveCount;
}
int Board::GetMoveCount() const {
    return moveCount_;
}

void Board::SetEnPassant(int enPassant) {
    enPassant_ = enPassant;
}
int Board::GetEnPassant() const {
    return enPassant_;
}

void Board::SetGameResult(GameResult gameResult) {
    gameResult_ = gameResult;
}
GameResult Board::GetGameResult() const {
    return gameResult_;
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

std::vector<Piece*> Board::SetStartingPositionVecBoardPiece() {

    // start fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    std::vector<Piece*> vec;

    vec.push_back(new Rook('r', 0));
    vec.push_back(new Knight('n', 1));
    vec.push_back(new Bishop('b', 2));
    vec.push_back(new Queen('q', 3));
    vec.push_back(new King('k', 4));
    vec.push_back(new Bishop('b', 5));
    vec.push_back(new Knight('n', 6));
    vec.push_back(new Rook('r', 7));

    for (int i=8; i<=15; i++) vec.push_back(new Pawn('p', i));
    // Init. vector<Piece*> in the range [16; 47] with NullPieces (name_ is '0', coordinate_ is i)
    for (int i=16; i<=47; i++) vec.push_back(new NullPiece('0', i));
    for (int i=48; i<=55; i++) vec.push_back(new Pawn('P', i));

    vec.push_back(new Rook('R', 56));
    vec.push_back(new Knight('N', 57));
    vec.push_back(new Bishop('B', 58));
    vec.push_back(new Queen('Q', 59));
    vec.push_back(new King('K', 60));
    vec.push_back(new Bishop('B', 61));
    vec.push_back(new Knight('N', 62));
    vec.push_back(new Rook('R', 63));

    return vec;
}
//only for test. Can be deleted
void Board::PrintVecBoardPiece() {
    for (auto itr : vecBoardPiece_) {
        std::cout << itr->GetName() << itr->GetCoordinate() << " ";
    }
    std::cout << "\n";
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

bool Board::IsHeroKingUnderCheckTestForRNBQP(const Move &move) {
    // Create testVec just to check the Hero's king is not under the check
    std::vector<char> testVec = vecBoardChar;
    testVec[move.getStartCoordinate()] = '0';
    testVec[move.getFinishCoordinate()] = move.getActivePiece();

    // Create the heroKing object
    King heroKing;
    if (islower(move.getActivePiece())) {
        heroKing.SetName('k');
        heroKing.SetCoordinate(FindTheKing('k', testVec));
    }
    else {
        heroKing.SetName('K');
        heroKing.SetCoordinate(FindTheKing('K', testVec));
    }

    // Check if heroKing is under check
    if (heroKing.IsKingUnderCheck(testVec)) return true;
    else return false;
}

void Board::makeMove() {

    try {
        if (!IsRightMoveOrder(this->move_) && isupper(this->move_.getActivePiece()))
            throw std::range_error("Wrong Move Order.\nBlack to move!\n");
        if (!IsRightMoveOrder(this->move_) && islower(this->move_.getActivePiece()))
            throw std::range_error("Wrong Move Order.\nWhite to move!\n");

        // input move is like "pe2-e4" or "Qa1:a8" or "o-o-o" or "O-O"
        if ((this->move_.getActivePiece() != vecBoardChar[this->move_.getStartCoordinate()])
                && this->move_.getActivePiece() != 'O' && this->move_.getActivePiece() != 'o')
            throw std::range_error("The Piece is Not There\n");

        switch (this->move_.getActivePiece()) {

            case 'R':
            case 'r':
            {
            if (this->move_.isProperMoveRook(this->move_, vecBoardChar)) {

                // If the target square is safe the move is being made
                if (!IsHeroKingUnderCheckTestForRNBQP(this->move_)) {
                    makeMoveRook(this->move_);
                }
                else throw std::range_error("The Move is Invalid\nThe King is under check\n");
            }
            else throw std::range_error("The Move is Invalid\n");
            break;
            }

            case 'B':
            case 'b':
            {
            if (this->move_.isProperMoveBishop(this->move_, vecBoardChar)) {

                // If the target square is safe the move is being made
                if (!IsHeroKingUnderCheckTestForRNBQP(this->move_)) {
                    makeMoveBishop(this->move_);
                }
                else throw std::range_error("The Move is Invalid\nThe King is under check\n");
            }
            else throw std::range_error("The Move is Invalid\n");
            break;
            }

            case 'Q':
            case 'q':
            {
            if (this->move_.isProperMoveQueen(this->move_, vecBoardChar)) {

                // If the target square is safe the move is being made
                if (!IsHeroKingUnderCheckTestForRNBQP(this->move_)) {
                    makeMoveQueen(this->move_);
                }
                else throw std::range_error("The Move is Invalid\nThe King is under check\n");
            }
            else throw std::range_error("The Move is Invalid\n");
            break;
            }

            case 'N':
            case 'n':
            {
            if (this->move_.isProperMoveKnight(this->move_, vecBoardChar)) {

                // If the target square is safe the move is being made
                if (!IsHeroKingUnderCheckTestForRNBQP(this->move_)) {
                    makeMoveKnight(this->move_);
                }
                else throw std::range_error("The Move is Invalid\nThe King is under check\n");
            }
            else throw std::range_error("The Move is Invalid\n");
            break;
            }

            case 'P':
            case 'p':
            {
            if (this->move_.isProperMovePawn(this->move_, vecBoardChar, this->GetEnPassant())) {

                // If the target square is safe the move is being made
                if (!IsHeroKingUnderCheckTestForRNBQP(this->move_)) {
                    makeMovePawn(this->move_);
                }
                else throw std::range_error("The Move is Invalid\nThe King is under check\n");
            }
            else throw std::range_error("The Move is Invalid\n");
            break;
            }

            case 'K':
            case 'k':
            {
            if (this->move_.isProperMoveKing(this->move_, vecBoardChar)) {

                // Create testVec just to check the Hero's king is not under the check
                std::vector<char> testVec = vecBoardChar;
                testVec[this->move_.getStartCoordinate()] = '0';
                testVec[this->move_.getFinishCoordinate()] = this->move_.getActivePiece();

                King king;
                if (islower(this->move_.getActivePiece())) {
                    king.SetName('k');
                    king.SetCoordinate(FindTheKing('k', testVec));
                }
                else {
                    king.SetName('K');
                    king.SetCoordinate(FindTheKing('K', testVec));
                }

                if (!king.IsKingUnderCheck(testVec)) {
                    // The move is being made
                    makeMoveKing(this->move_);
                }
                else std::cout << "The Move is Invalid\nThe King is under check\n";
            }
            else std::cout << "The Move is Invalid\n";
            break;
            }

            case 'O':
            case 'o':
            {
            if (this->castling_.IsCastlingPossible(this->move_, vecBoardChar)) {
                    MakeMoveCastling(this->move_);
            }
            else throw std::range_error("Such Castling is Invalid\n");
            break;
            }

            default:
            {
                throw std::range_error("No such Piece\n");
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
            if (castling_.IsCastlingPossible(move, vecBoardChar)) {
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

        if (activePiece->IsProperMove(move, vecBoardChar, this->GetEnPassant())) {

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
                this->SetEnPassant(0);
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

    this->SetEnPassant(0);

    moveCount_++;
    castling_.SwitchState(move);
}
void Board::makeMoveBishop(const Move &move) {
    vecBoardChar[move.getStartCoordinate()] = '0';
    vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();

    this->SetEnPassant(0);

    moveCount_++;
}
void Board::makeMoveQueen(const Move &move) {
    vecBoardChar[move.getStartCoordinate()] = '0';
    vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();

    this->SetEnPassant(0);

    moveCount_++;
}
void Board::makeMoveKnight(const Move &move) {
    vecBoardChar[move.getStartCoordinate()] = '0';
    vecBoardChar[move.getFinishCoordinate()] = move.getActivePiece();

    this->SetEnPassant(0);

    moveCount_++;
}

void Board::makeMovePawn(const Move &move) {

    // Check for en-Passant Opportunity on the next move.
    // If en-Passant is possible, set enPassant_ value = field on the 3rd rank for White, 6th rank for Black
    if (move.getActivePiece() == 'P' && move.getStartCoordinate() / 8 == 6 && move.getFinishCoordinate() / 8 == 4) {

        this->SetEnPassant(move.getStartCoordinate() - 8);
    }
    else {
        if (move.getActivePiece() == 'p' && move.getStartCoordinate() / 8 == 1 && move.getFinishCoordinate() / 8 == 3) {

            this->SetEnPassant(move.getStartCoordinate() + 8);
        }
        else {
            this->SetEnPassant(0);
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

    this->SetEnPassant(0);

    moveCount_++;
    castling_.SwitchState(move);
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

    this->SetEnPassant(0);
    castling_.SwitchState(move);

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
                setOfPossibleMoves = activePiece.SetOfPossibleMoves(vecBoardChar, this->GetEnPassant());

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
                setOfPossibleMoves = activePiece.SetOfPossibleMoves(vecBoardChar, this->GetEnPassant());

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






































