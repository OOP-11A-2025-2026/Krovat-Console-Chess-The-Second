#ifndef ROOK_H
#define ROOK_H

class Rook : public Piece {
    bool hasMoved;

public:
    Rook(bool isWhite);

    Rook(const Rook &other);

    bool regularMovement(Coordinates from, Coordinates to) override;

    bool hasMoved();

    void setHasMoved(bool moved);

    virtual ~Rook() = default;
};

#endif