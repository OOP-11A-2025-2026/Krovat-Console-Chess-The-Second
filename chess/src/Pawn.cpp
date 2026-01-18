#include "../include/Pawn.h"
#include <cmath>

Pawn::Pawn(bool isWhite) 
    : Piece(isWhite, isWhite ? 'P' : 'p'), hasPawnMoved(false), enPassantEligible(false) {}

Pawn::Pawn(const Pawn &other) 
    : Piece(other), hasPawnMoved(other.hasPawnMoved), enPassantEligible(other.enPassantEligible) {}

bool Pawn::regularMovement(Coordinates from, Coordinates to) {
    int direction = isWhite ? -1 : 1; // White moves up (lower index), Black moves down
    int rowDiff = (int)to.first - (int)from.first;
    int colDiff = (int)to.second - (int)from.second;

    // One square forward
    if (colDiff == 0 && rowDiff == direction) return true;

    // Two squares forward (initial move)
    if (!hasPawnMoved && colDiff == 0 && rowDiff == 2 * direction) return true;

    //Diagonal capture geometry
    if (std::abs(colDiff) == 1 && rowDiff == direction) return true;

    return false;
}