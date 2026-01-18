#ifndef BOARD_H
#define BOARD_H

// Exceptions
#include "InvalidMove.h"

// Piece classes
#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

// Other libaries
#include <string>

class Board {
private:
    // 
    Piece* squares[8][8];
    // Piece undoSquares[8][8];
    bool undoAvailable = false;

    int knightMoves[8][2] = {
            { 2, 1}, { 2,-1}, {-2, 1}, {-2,-1},
            { 1, 2}, { 1,-2}, {-1, 2}, {-1,-2}
    };

    void saveUndoState();
    Coordinates getKingCoordinates(bool isKingWhite);
    bool checkCastle(Coordinates from, Coordinates to);
    void castle(Coordinates from, Coordinates to);
    bool checkCollision(Coordinates from, Coordinates to);
    Piece* getPiece(Coordinates coords);
    void resetAllEnPassantEligibility();
    bool checkEnPassant(Coordinates from, Coordinates to);
    void enPassant(Coordinates from, Coordinates to);
    void promotion(Coordinates coords, char promotionChoice);
    void checkPin(Coordinates from, Coordinates to);

public:
    Board();
    void undoMove();
    bool checkCheck(bool isKingWhite);
    bool hasValidMoves(bool isKingWhite);
    bool checkMate(bool isKingWhite);
    bool checkStalemate(bool isKingWhite);
    int makeMove(Coordinates from, Coordinates to, bool isWhiteTurn, char promotionChoice);
    std::string toString();
    bool isLegalMove(Coordinates from, Coordinates to, bool isWhiteTurn, char promotionChoice);

};

#endif