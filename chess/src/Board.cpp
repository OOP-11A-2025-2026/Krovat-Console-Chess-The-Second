#include "../include/Board.h"



Piece* Board::getPiece(Coordinates coords) {
    return squares[coords.first][coords.second];
}

void Board::resetAllEnPassantEligibility() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Pawn* p = dynamic_cast<Pawn*>(squares[i][j]);
            if (p) p->setEnPassantEligible(false);
        }
    }
}

void Board::checkPin(Coordinates from, Coordinates to) {
    Piece* movingPiece = getPiece(from);
    Piece* capturedPiece = getPiece(to);

    // Make the move (assigning pointers)
    squares[to.first][to.second] = movingPiece;
    squares[from.first][from.second] = nullptr;

    bool inCheck = checkCheck(movingPiece->getIsWhite());

    // Undo the move
    squares[from.first][from.second] = movingPiece;
    squares[to.first][to.second] = capturedPiece;

    if (inCheck) throw std::invalid_argument("Move leaves king in check");
}

void Board::enPassant(Coordinates from, Coordinates to) {
    Piece* p1 = getPiece(from);
    
    delete squares[from.first][to.second]; 
    squares[from.first][to.second] = nullptr; 

    squares[to.first][to.second] = p1;
    squares[from.first][from.second] = nullptr;
    
    static_cast<Pawn*>(p1)->setHasPawnMoved(true);
    resetAllEnPassantEligibility();
}

void Board::promotion(Coordinates coords, char choice) {
    Pawn* p = dynamic_cast<Pawn*>(getPiece(coords));
    if (!p) return;

    bool w = p->getIsWhite();
    Piece* n = nullptr;

    switch (toupper(choice)) {
        case 'R': n = new Rook(w); break;
        case 'B': n = new Bishop(w); break;
        case 'N': n = new Knight(w); break;
        default:  n = new Queen(w); break;
    }

    // Clean up the memory of the pawn before replacing the pointer
    delete squares[coords.first][coords.second]; 
    squares[coords.first][coords.second] = n;
}

bool Board::checkEnPassant(Coordinates from, Coordinates to) {
    Pawn* p1 = dynamic_cast<Pawn*>(getPiece(from));
    if (!p1) return false;

    int direction = p1->getIsWhite() ? -1 : 1;
    
    // 1. Must move diagonally one square
    if ((int)to.first - (int)from.first != direction || 
        std::abs((int)to.second - (int)from.second) != 1) {
        return false;
    }

    // 2. Target square must be empty
    if (getPiece(to) != nullptr) return false;

    // 3. Enemy pawn must be at the same row as 'from' and same column as 'to'
    Coordinates enemyCoords = { from.first, to.second };
    Pawn* p2 = dynamic_cast<Pawn*>(getPiece(enemyCoords));

    // 4. Enemy must be a Pawn, opposite color, and eligible
    if (p2 && p2->getIsWhite() != p1->getIsWhite() && p2->isEnPassantEligible()) {
        return true;
    }
    return false;
}