#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <utility>

typedef unsigned short int usint;

class Piece {
protected:
    const bool isWhite;

public:
    Piece(bool isWhite);

    Piece(const Piece &other);

    virtual bool isWithinBoard(pair<usint, usint>);
};

#endif