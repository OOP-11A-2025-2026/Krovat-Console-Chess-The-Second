#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {

public:
    Knight(bool isWhite);

    Knight(const Knight &other);

    bool regularMovement(pair<usint, usint> from, pair<usint, usint> to) override;

    virtual ~Knight() = default;
};

#endif