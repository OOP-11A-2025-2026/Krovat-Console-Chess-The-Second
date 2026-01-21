#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
private:
    bool hasPawnMoved;
    bool enPassantEligible;

public:
    Pawn(bool isWhite);
    Pawn(const Pawn &other);

    bool regularMovement(Coordinates from, Coordinates to) override;
    
    // Accessors
    bool getHasPawnMoved() const;
    void setHasPawnMoved(bool moved);
    bool isEnPassantEligible()  const;
    void setEnPassantEligible(bool eligible);

    virtual ~Pawn() = default;

    Piece* copy() const override;
};

#endif