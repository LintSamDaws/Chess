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
        fen_ = fen;
        vecBoardChar_ = FENtoVectorChar(fen);
        vecBoardPiece_ = SetStartingPositionVecBoardPiece();
        gameLegend_.SetMoveCount(0);
        enPassant_ = 0;
        currentState_ = &StateBase::getInstance();
        gameResult_ = GameResult::OnAction;
    }
    else {
        fen_ = fen;
        vecBoardChar_ = FENtoVectorChar(fen);
        // Can be a problem if we are using FEN with next move enPassant_
    }
}

// Start of the Game. State Machine
void Board::GameOn() {
    std::cout << "Game on!\n";
    while(true) {
        this->SwitchState();
        if (currentState_ == &StateExit::getInstance()) {
            this->SwitchState();
            break;
        }
    }
}

void Board::setState(BoardState& newState)
{
    currentState_ = &newState;  // actually change states now
}
void Board::SwitchState()
{
    // Delegate the task of determining the next state to the current state
    currentState_->SwitchState(*this);
}

void Board::SetGameLegend(GameLegend gameLegend)
{
    gameLegend_ = gameLegend;
}
GameLegend Board::GetGameLegend() const
{
    return gameLegend_;
}

void Board::setMove(Move &move) {
    move_ = move;
}
Move Board::GetMove() const {
    return move_;
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
    fen_ = fen;
    vecBoardChar_ = FENtoVectorChar(fen);
}
std::string Board::getFEN() const {
    return fen_;
}

void Board::setVecBoardChar(std::vector<char> vec){
    vecBoardChar_ = vec;
}
std::vector<char> Board::getVecBoardChar() const {
    return vecBoardChar_;
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

        std::cout << vecBoardChar_[i] << " ";
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

bool Board::IsHeroKingUnderCheckTest(const Move &move) {
    // Create testVec just to check the Hero's king is not under the check
    std::vector<char> testVec = vecBoardChar_;
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

        // Castling
        if (move_.getActivePiece() == 'O' || move_.getActivePiece() == 'o') {
            if (this->castling_.IsCastlingPossible(this->move_, vecBoardChar_)) {
                MakeMoveCastling(this->move_);
                this->moveCountPlusPlus();
                castling_.SwitchState(move_);
            }
            else throw std::range_error("Such Castling is Invalid\n");
        }
        // every other move
        else {
            Piece& activePiece = this->GetPieceObject(move_);
            if (activePiece.IsProperMove(this->move_, vecBoardChar_, enPassant_)) {
                // Final Check
                // If the target square is safe the move is being made
                if (!IsHeroKingUnderCheckTest(this->move_)) {
                    makeMovePiece(this->move_);
                    this->moveCountPlusPlus();
                    castling_.SwitchState(move_);
                }
                else throw std::range_error("The Move is Invalid\nThe King is under check\n");
            }
            else throw std::range_error("The Move is Invalid\n");
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}

// temp
void Board::moveCountPlusPlus() {
    GameLegend legend = this->GetGameLegend();
    legend.MoveCountPlusPlus();
    this->SetGameLegend(legend);
}

void Board::makeMovePiece(const Move &move) {

    // Pawn Move:
    if (move.getActivePiece() == 'P' || move.getActivePiece() == 'p') {

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
            vecBoardChar_[move.getStartCoordinate()] = '0';
            vecBoardChar_[move.getFinishCoordinate()] = promotion;
        }
        else {
            vecBoardChar_[move.getStartCoordinate()] = '0';

            // Manage en-Passand case for White
            if (vecBoardChar_[move.getFinishCoordinate()] == '0' && move.getActivePiece() == 'P') {
                vecBoardChar_[move.getFinishCoordinate() + 8] = '0';
            }
            // for Black
            if (vecBoardChar_[move.getFinishCoordinate()] =='0' && move.getActivePiece() == 'p') {
                vecBoardChar_[move.getFinishCoordinate() - 8] = '0';
            }
            vecBoardChar_[move.getFinishCoordinate()] = move.getActivePiece();
        }
    }
    // Another Piece Move:
    else {
        vecBoardChar_[move.getStartCoordinate()] = '0';
        vecBoardChar_[move.getFinishCoordinate()] = move.getActivePiece();

        this->SetEnPassant(0);
    }

}
void Board::MakeMoveCastling(const Move &move) {

    // Castling for White
    if (isupper(move.getActivePiece())) {
        // Long Castling
        if (move.getFinishCoordinate() == 56) {
            vecBoardChar_[56] = '0';
            vecBoardChar_[60] = '0';
            vecBoardChar_[58] = 'K';
            vecBoardChar_[59] = 'R';
        }
        // Short
        else {
            vecBoardChar_[60] = '0';
            vecBoardChar_[63] = '0';
            vecBoardChar_[62] = 'K';
            vecBoardChar_[61] = 'R';
        }
    }
    // Castling for Black
    else {
        // Long Castling
        if (move.getFinishCoordinate() == 0) {
            vecBoardChar_[0] = '0';
            vecBoardChar_[4] = '0';
            vecBoardChar_[2] = 'K';
            vecBoardChar_[3] = 'R';
        }
        // Short
        else {
            vecBoardChar_[4] = '0';
            vecBoardChar_[7] = '0';
            vecBoardChar_[6] = 'k';
            vecBoardChar_[5] = 'r';
        }
    }

    this->SetEnPassant(0);
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

int Board::FindTheKing(char name, const std::vector<char> &vecChar) const {
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
        if (vecBoardChar_[i] == name) {
            res = i;
        }
    }
    return res;
}

Piece& Board::GetPieceObject(const Move &move) const {

    static NullPiece nullPiece;
    Piece* activePiece = &nullPiece;

    static Rook rook;
    static Bishop bishop;
    static Queen queen;
    static Knight knight;
    static Pawn pawn;
    static King king;

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
            activePiece = &king;
            break;
        }

        default:
        {
            break;
        }
    }
    activePiece->SetName(move.getActivePiece());
    activePiece->SetCoordinate(move.getStartCoordinate());
    return *activePiece;
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

    switch (vecBoardChar_[coordinate]) {
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
    activePiece->SetName(vecBoardChar_[coordinate]);
    activePiece->SetCoordinate(coordinate);
    return *activePiece;
}

bool Board::IsStaleMate() const {

    // Spot the King. White or Black
    int kingCoordinate;
    char kingName;
    if (this->GetGameLegend().GetMoveCount() % 2 == 0) {
        kingCoordinate = FindTheKing('K');
        kingName = 'K';
    }
    else {
        kingCoordinate = FindTheKing('k');
        kingName = 'k';
    }

    // If the King is under check there is no Stalemate
    King king(kingName, kingCoordinate);
    if (king.IsKingUnderCheck(vecBoardChar_)) {
        return false;
    }
    // Check if one of all other pieces has the Possible Move
    else {
        for (int i=0; i<64; i++) {

            Piece& activePiece = GetSameColorPiece(kingName, i);

            if (vecBoardChar_[i] != '0' && ((islower(kingName) && islower(vecBoardChar_[i])) || (isupper(kingName) && isupper(vecBoardChar_[i])))) {

                std::set<int> setOfPossibleMoves;
                setOfPossibleMoves = activePiece.SetOfPossibleMoves(vecBoardChar_, this->GetEnPassant());

                for (int moveFromSet : setOfPossibleMoves) {
                    // Create testVec just to check the Hero's king is not under the check
                    std::vector<char> testVec = vecBoardChar_;
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
bool Board::IsCheckMate() const {

    // Spot the King. White or Black. Initialize it.
    int kingCoordinate;
    char kingName;
    if (this->GetGameLegend().GetMoveCount() % 2 == 0) {
        kingCoordinate = FindTheKing('K');
        kingName = 'K';
    }
    else {
        kingCoordinate = FindTheKing('k');
        kingName = 'k';
    }

    // If the King is not under check there is no Checkmate
    King king(kingName, kingCoordinate);


    if (!king.IsKingUnderCheck(vecBoardChar_)) {
        return false;
    }
    // Check if the King or one of other pieces has the Possible Move
    else {
        for (int i=0; i<64; i++) {

            Piece& activePiece = GetSameColorPiece(kingName, i);

            if (vecBoardChar_[i] != '0' && ((islower(kingName) && islower(vecBoardChar_[i])) || (isupper(kingName) && isupper(vecBoardChar_[i])))) {

                std::set<int> setOfPossibleMoves;
                setOfPossibleMoves = activePiece.SetOfPossibleMoves(vecBoardChar_, this->GetEnPassant());

                for (int moveFromSet : setOfPossibleMoves) {

                    // Create testVec just to check the Hero's king is not under the check
                    std::vector<char> testVec = vecBoardChar_;
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
        if (vecBoardChar_[i] != '0') {
            fen += vecBoardChar_[i];
        }
        else {
            count++;
            if ((i != 63 && vecBoardChar_[i+1] != '0') || (i % 8 == 7 && count != 0)) {
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
    if ((this->GetGameLegend().GetMoveCount() % 2 == 0 && isupper(move.getActivePiece()))
            || (this->GetGameLegend().GetMoveCount() % 2 == 1 && islower(move.getActivePiece()))) {
        return true;
    }
    else return false;
}






































