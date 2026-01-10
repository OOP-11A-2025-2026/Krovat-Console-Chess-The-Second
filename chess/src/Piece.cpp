#include "../include/Piece.h"

using namespace std;

Piece::Piece(bool isWhite, char symbol) : isWhite(isWhite), symbol(symbol) {}

Piece::Piece(const Piece &other) : isWhite(other.isWhite), symbol(other.symbol) {}

bool Piece::isWithinBoard(std::pair<usint, usint> pos) {
    usint row = pos.first;
    usint col = pos.second;

    return (row > 0 && row < 8 && col > 0 && col < 8);
}