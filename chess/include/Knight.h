#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {

public:
    Knight(bool isWhite);

    Knight(const Knight &other);

    bool regularMovement(Coordinates from, Coordinates to) override;

    virtual ~Knight() = default;

    Piece* copy() const override;
};

#endif