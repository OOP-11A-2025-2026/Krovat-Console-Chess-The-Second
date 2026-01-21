#include "../include/Queen.h"

#include <cassert>
#include <iostream>

void test_initialization() {
    Queen whiteQueen(true);
    Queen blackQueen(false);

    assert(whiteQueen.getIsWhite() == true);
    assert(whiteQueen.getSymbol() == 'Q');

    assert(blackQueen.getIsWhite() == false);
    assert(blackQueen.getSymbol() == 'q');
}

void test_copy() {
    Queen original(true);
    Piece* copyPiece = original.copy();
    Queen* copiedQueen = dynamic_cast<Queen*>(copyPiece);

    assert(copiedQueen != nullptr);
    assert(copiedQueen->getIsWhite() == original.getIsWhite());
    assert(copiedQueen->getSymbol() == original.getSymbol());

    delete copyPiece;
}

void test_basic_queen_moves() {
    Queen q(true);
    Coordinates from{4, 4};

    // Rook-like moves
    assert(q.regularMovement(from, {4, 7}));
    assert(q.regularMovement(from, {4, 0}));
    assert(q.regularMovement(from, {7, 4}));
    assert(q.regularMovement(from, {0, 4}));

    // Bishop-like moves
    assert(q.regularMovement(from, {7, 7}));
    assert(q.regularMovement(from, {0, 0}));
    assert(q.regularMovement(from, {6, 2}));
    assert(q.regularMovement(from, {2, 6}));
}

void test_invalid_queen_moves() {
    Queen q(true);
    Coordinates from{4, 4};

    // Knight-like
    assert(!q.regularMovement(from, {5, 6}));

    // Random invalid
    assert(!q.regularMovement(from, {6, 7}));
}

void test_out_of_bounds_queen_move() {
    Queen q(true);

    assert(!q.regularMovement({4, 4}, {8, 4}));
    assert(!q.regularMovement({4, 4}, {-1, 4}));
}

void test_same_square_throws() {
    Queen q(true);
    Coordinates pos{4, 4};

    try {
        q.regularMovement(pos, pos);
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }
}

int main() {
    test_initialization();
    test_copy();
    test_basic_queen_moves();
    test_invalid_queen_moves();
    test_out_of_bounds_queen_move();
    test_same_square_throws();

    std::cout << "Queen tests passed!\n";
}