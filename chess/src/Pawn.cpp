#include "../include/Pawn.h"
#include <cmath>

Pawn::Pawn(bool isWhite) 
    : Piece(isWhite, isWhite ? 'P' : 'p'), hasPawnMoved(false), enPassantEligible(false) {}

Pawn::Pawn(const Pawn &other) 
    : Piece(other), hasPawnMoved(other.hasPawnMoved), enPassantEligible(other.enPassantEligible) {}

Piece* Pawn::copy() const {
    return new Pawn(*this);
}

bool Pawn::regularMovement(Coordinates from, Coordinates to) {
    int direction = isWhite ? -1 : 1; // White moves up (lower index), Black moves down (higher index)
    int rowDiff = (int)to.first - (int)from.first;
    int colDiff = (int)to.second - (int)from.second;

    if(from.first == to.first && from.second == to.second)
        throw std::invalid_argument("Invalid coordinates. The coordinates must not be the same");

    if(!isWithinBoard(to)) return false;

    if (colDiff == 0 && rowDiff == direction) return true;

    if (!hasPawnMoved && colDiff == 0 && rowDiff == 2 * direction) return true;

    if (std::abs(colDiff) == 1 && rowDiff == direction) return true;

    return false;
}

bool Pawn::getHasPawnMoved() const {
    return hasPawnMoved;
}

void Pawn::setHasPawnMoved(bool moved) {
    hasPawnMoved = moved;
}

bool Pawn::isEnPassantEligible() const {
    return enPassantEligible;
}

void Pawn::setEnPassantEligible(bool eligible) {
    enPassantEligible = eligible;
}