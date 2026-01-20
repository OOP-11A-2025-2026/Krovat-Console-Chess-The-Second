#include "../include/Knight.h"

using namespace std;

Knight::Knight(bool isWhite) : Piece::Piece(isWhite, isWhite ? 'N' : 'n') {}

Knight::Knight(const Knight &other) : Piece::Piece(other) {}

bool Knight::regularMovement(Coordinates from, Coordinates to) {
    usint fromFst = from.first;
    usint fromSnd = from.second;
    usint toFst = to.first;
    usint toSnd = to.second;

    if(fromFst == toFst && fromSnd == toSnd)
        throw invalid_argument("Invalid coordinates. The coordinates must not be the same");

    if(isWithinBoard(to)) {
            usint dx = abs(toFst - fromFst);
            usint dy = abs(toSnd - fromSnd);
            return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
        }
    return false;
}

