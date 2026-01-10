#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <utility>
#include <exception>

typedef unsigned short int usint;

class Piece {
protected:
    const bool isWhite;
    const char symbol;

public:
    Piece(bool isWhite, char symbol);

    Piece(const Piece &other);

    virtual bool isWithinBoard(pair<usint, usint> pos);

    virtual bool regularMovement(pair<usint, usint> from, pair<usint, usint> to) = 0;

    virtual ~Piece() = default;
};

#endif