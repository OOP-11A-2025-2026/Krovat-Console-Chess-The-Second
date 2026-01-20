#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    bool hasKingMoved;

public:
    King(bool isWhite);

    King(const King &other);

    bool regularMovement(Coordinates from, Coordinates to) override;

    virtual ~King() = default;

    bool getHasKingMoved();

    void setHasKingMoved(bool moved);
};

#endif