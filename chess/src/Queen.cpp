#include "../include/Queen.h"

Queen::Queen(bool isWhite)
    : Piece(isWhite, isWhite ? 'Q' : 'q') {}

Queen::Queen(const Queen& other)
    : Piece(other) {}

bool Queen::regularMovement(Coordinates from, Coordinates to) {
    if (from == to)
        throw std::invalid_argument("Invalid coordinates");

    int dx = std::abs((int)to.first - (int)from.first);
    int dy = std::abs((int)to.second - (int)from.second);

    return dx == 0 || dy == 0 || dx == dy;
}