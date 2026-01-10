#include "../include/King.h"

using namespace std;

King::King(bool isWhite, char symbol) : Piece::Piece(isWhite, isWhite ? 'K' : 'k') {}

King::King(const King &other) : Piece::Piece(other) {}

bool King::regularMovement(pair<usint, usint> from, pair<usint, usint> to) {
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

bool King::hasMoved() {
    return hasKingMoved;
}

void King::setHasMoved(bool moved) {
    hasKingMoved = moved;
}