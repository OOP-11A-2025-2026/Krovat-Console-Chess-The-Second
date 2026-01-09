#include "../include/Piece.h"

using namespace std;

Piece::Piece(bool isWhite) : isWhite(isWhite) {}

Piece::Piece(const Piece &other) : isWhite(other.isWhite) {}

bool Piece::isWithinBoard(pair<usint, usint> pos ) {
    usint row = pos.first;
    usint col = pos.second;

    return (row > 0 && row < 8 && col > 0 && col < 8);
}