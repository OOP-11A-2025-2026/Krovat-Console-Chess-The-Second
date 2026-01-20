#include "../include/King.h"

using namespace std;

King::King(bool isWhite) : Piece::Piece(isWhite, isWhite ? 'K' : 'k') {}

King::King(const King &other) : Piece::Piece(other), hasKingMoved(other.hasKingMoved) {}

Piece* King::copy() const {
    return new King(*this);
}

bool King::regularMovement(Coordinates from, Coordinates to) {
    usint fromFst = from.first;
    usint fromSnd = from.second;
    usint toFst = to.first;
    usint toSnd = to.second;

    if(fromFst == toFst && fromSnd == toSnd)
        throw invalid_argument("Invalid coordinates. The coordinates must not be the same");

    if(isWithinBoard(to)) {
            usint dx = abs(toFst - fromFst);
            usint dy = abs(toSnd - fromSnd);
            return (dx <= 1 && dy <= 1 || dx * dy == 1);
        }
    return false;
}

bool King::getHasKingMoved() {
    return hasKingMoved;
}

void King::setHasKingMoved(bool moved) {
    hasKingMoved = moved;
}