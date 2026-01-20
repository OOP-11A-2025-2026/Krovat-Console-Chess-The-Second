#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
private:
    bool hasMoved;
    bool enPassantEligible;

public:
    Pawn(bool isWhite);
    Pawn(const Pawn &other);

    bool regularMovement(Coordinates from, Coordinates to) override;
    
    // Accessors
    bool hasMoved() const { return hasMoved; }
    void setHasMoved(bool moved) { hasMoved = moved; }
    bool isEnPassantEligible() const { return enPassantEligible; }
    void setEnPassantEligible(bool eligible) { enPassantEligible = eligible; }

    virtual ~Pawn() = default;
};

#endif