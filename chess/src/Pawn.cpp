#include "../include/Pawn.h"
#include <cmath>

Pawn::Pawn(bool isWhite) 
    : Piece(isWhite, isWhite ? 'P' : 'p'), hasPawnMoved(false), enPassantEligible(false) {}

Pawn::Pawn(const Pawn &other) 
    : Piece(other), hasPawnMoved(other.hasPawnMoved), enPassantEligible(other.enPassantEligible) {}

bool Pawn::regularMovement(Coordinates from, Coordinates to) {
    int direction = isWhite ? -1 : 1;
    int rowDiff = (int)to.first - (int)from.first;
    int colDiff = (int)to.second - (int)from.second;

    if (colDiff == 0 && rowDiff == direction) return true;

    if (!hasPawnMoved && colDiff == 0 && rowDiff == 2 * direction) return true;

    if (std::abs(colDiff) == 1 && rowDiff == direction) return true;

    return false;
}