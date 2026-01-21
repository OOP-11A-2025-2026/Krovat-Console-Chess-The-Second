#include <cassert>
#include <iostream>

#include "../include/Rook.h"

void test_initialization() {
    Rook whiteRook(true);
    Rook blackRook(false);

    assert(whiteRook.getIsWhite() == true);
    assert(whiteRook.getSymbol() == 'R');
    assert(whiteRook.getHasRookMoved() == false);

    assert(blackRook.getIsWhite() == false);
    assert(blackRook.getSymbol() == 'r');
    assert(blackRook.getHasRookMoved() == false);
}

void test_copy() {
    Rook original(true);
    original.setHasRookMoved(true);
    Rook* copy = static_cast<Rook*>(original.copy());

    assert(copy->getIsWhite() == original.getIsWhite());
    assert(copy->getSymbol() == original.getSymbol());
    assert(copy->getHasRookMoved() == original.getHasRookMoved());

    delete copy;
}

void test_basic_rook_moves() {
    Rook r(true);
    Coordinates from{4, 4};

    // Horizontal
    assert(r.regularMovement(from, {4, 7}));
    assert(r.regularMovement(from, {4, 0}));

    // Vertical
    assert(r.regularMovement(from, {7, 4}));
    assert(r.regularMovement(from, {0, 4}));
}

void test_invalid_rook_moves() {
    Rook r(true);
    Coordinates from{4, 4};

    // Diagonal
    assert(!r.regularMovement(from, {5, 5}));

    // Knight-like
    assert(!r.regularMovement(from, {5, 6}));
}

void test_out_of_bounds_rook_move() {
    Rook r(true);
    Coordinates from{4, 4};

    assert(!r.regularMovement(from, {8, 4}));
    assert(!r.regularMovement(from, {-1, 4}));
}

void test_same_square_throws() {
    Rook r(true);
    Coordinates pos{4, 4};

    try {
        r.regularMovement(pos, pos);
        assert(false); // should not reach here
    } catch (const std::invalid_argument&) {
        assert(true);
    }
}

void test_rook_moved_flag() {
    Rook r(true);

    assert(!r.getHasRookMoved());
    r.setHasRookMoved(true);
    assert(r.getHasRookMoved());
}

int main() {
    test_basic_rook_moves();
    test_invalid_rook_moves();
    test_out_of_bounds_rook_move();
    test_same_square_throws();
    test_rook_moved_flag();

    std::cout << "Rook tests passed!\n";
}