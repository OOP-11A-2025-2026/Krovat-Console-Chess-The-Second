#include "../include/Rook.h"

Rook::Rook(bool isWhite)
    : Piece(isWhite, isWhite ? 'R' : 'r'), hasRookMoved(false) {}

Rook::Rook(const Rook& other)
    : Piece(other), hasRookMoved(other.hasRookMoved) {}

bool Rook::regularMovement(Coordinates from, Coordinates to) {
    if (from == to)
        throw std::invalid_argument("Invalid coordinates");

    return from.first == to.first || from.second == to.second;
}

bool Rook::getHasRookMoved() {
    return hasRookMoved;
}

void Rook::setHasRookMoved(bool moved) {
    hasRookMoved = moved;
}