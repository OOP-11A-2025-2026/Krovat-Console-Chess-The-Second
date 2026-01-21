#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
    bool hasRookMoved;

public:
    Rook(bool isWhite);

    Rook(const Rook &other);

    bool regularMovement(Coordinates from, Coordinates to) override;

    bool getHasRookMoved() const;

    void setHasRookMoved(bool moved);

    virtual ~Rook() = default;

    Piece* copy() const override;
};

#endif