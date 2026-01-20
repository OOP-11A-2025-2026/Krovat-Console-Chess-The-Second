#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    bool hasMoved;

public:
    // King(bool isWhite, char symbol);
    King(bool isWhite); // The symbol is assigned by default

    King(const King &other);

    bool regularMovement(Coordinates from, Coordinates to) override;

    virtual ~King() = default;

    bool hasMoved();

    void setHasMoved(bool moved);
};

#endif