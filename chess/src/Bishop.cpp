#include "../include/Bishop.h"

using namespace std;

Bishop::Bishop(bool isWhite) : Piece::Piece(isWhite, isWhite ? 'B' : 'b') {}

Bishop::Bishop(const Bishop &other) : Piece::Piece(other) {}

Piece* Bishop::copy() const {
    return new Bishop(*this);
}

bool Bishop::regularMovement(Coordinates from, Coordinates to) {
    usint fromFst = from.first;
    usint fromSnd = from.second;
    usint toFst = to.first;
    usint toSnd = to.second;

    if(fromFst == toFst && fromSnd == toSnd)
        throw invalid_argument("Invalid coordinates. The coordinates must not be the same");

    if(isWithinBoard(to))
    {
        usint dx = abs(toFst - fromFst);
        usint dy = abs(toSnd - fromSnd);
        return dx == dy;
    }

    return false;
}
