#ifndef BOARD_H
#define BOARD_H

// Exceptions
#include "InvalidMove.h"

// Pieces
#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

// Other
#include <string>
#include <sstream>

class Board {
private:
    Piece* squares[8][8] = {nullptr};
    Piece* undoSquares[8][8] = {nullptr};

    bool undoAvailable = false;

    int knightMoves[8][2] = {
        { 2, 1}, { 2,-1}, {-2, 1}, {-2,-1},
        { 1, 2}, { 1,-2}, {-1, 2}, {-1,-2}
    };
    
    void saveUndoState(); // done, untested
    Coordinates getKingCoordinates(bool isKingWhite); // done, untested
    bool checkCastle(Coordinates from, Coordinates to);
    void castle(Coordinates from, Coordinates to);
    bool checkCollision(Coordinates from, Coordinates to); // done, untested
    Piece* getPiece(Coordinates coords); // done, untested
    void resetAllEnPassantEligibility(); // done, untested
    bool checkEnPassant(Coordinates from, Coordinates to); // done, untested
    void enPassant(Coordinates from, Coordinates to); // done, untested
    void promotion(Coordinates coords, char promotionChoice); // done, untested
    void checkPin(Coordinates from, Coordinates to); // done, untested

public:
    // To stop accsidental shadow copying
    Board(const Board &other) = delete;
    Board& operator=(const Board &other) = delete;

    Board(); // done, untested
    ~Board(); // done, untested
    
    void undoMove(); // done, untested
    bool checkCheck(bool isKingWhite); // done, untested
    bool hasValidMoves(bool isKingWhite);
    bool checkMate(bool isKingWhite);
    bool checkStalemate(bool isKingWhite);
    int makeMove(Coordinates from, Coordinates to, bool isWhiteTurn, char promotionChoice);
    std::string toString(); // done, untested
    bool isLegalMove(Coordinates from, Coordinates to, bool isWhiteTurn, char promotionChoice);    
};

#endif