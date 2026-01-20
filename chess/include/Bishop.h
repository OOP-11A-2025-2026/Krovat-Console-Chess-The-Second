#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(bool isWhite);

    Bishop(const Bishop &other);

    bool regularMovement(Coordinates from, Coordinates to) override;

    virtual ~Bishop() = default;
};

#endif