#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(bool isWhite);

    Queen(const Queen &other);

    bool regularMovement(Coordinates from, Coordinates to) override;

    virtual ~Queen() = default;

    Piece* copy() const override;
};

#endif