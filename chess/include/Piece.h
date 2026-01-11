#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <utility>
#include <exception>

typedef unsigned short int usint;
typedef std::pair<usint, usint> Coordinates;

class Piece {
protected:
    const bool isWhite;
    const char symbol;

public:
    Piece(bool isWhite, char symbol);

    Piece(const Piece &other);

    virtual bool isWithinBoard(Coordinates pos);

    virtual bool regularMovement(Coordinates from, Coordinates to) = 0;

    virtual ~Piece() = default;
};

#endif