#include <cassert>
#include <iostream>
#include <stdexcept>

#include "../include/King.h"

void test_valid_king_moves() {
    King k(true);
    Coordinates from{4, 4};

    // Horizontal
    assert(k.regularMovement(from, {4, 5}));
    assert(k.regularMovement(from, {4, 3}));

    // Vertical
    assert(k.regularMovement(from, {5, 4}));
    assert(k.regularMovement(from, {3, 4}));

    // Diagonal
    assert(k.regularMovement(from, {5, 5}));
    assert(k.regularMovement(from, {5, 3}));
    assert(k.regularMovement(from, {3, 5}));
    assert(k.regularMovement(from, {3, 3}));
}

void test_invalid_king_moves() {
    King k(true);
    Coordinates from{4, 4};

    // Too far
    assert(!k.regularMovement(from, {6, 4}));
    assert(!k.regularMovement(from, {4, 6}));
    assert(!k.regularMovement(from, {6, 6}));

    // Knight-like
    assert(!k.regularMovement(from, {6, 5}));
}

void test_same_square_throws() {
    King k(true);

    try {
        k.regularMovement({3, 3}, {3, 3});
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }
}

void test_out_of_bounds() {
    King k(true);

    assert(!k.regularMovement({0, 0}, {-1, 0}));
    assert(!k.regularMovement({7, 7}, {8, 7}));
}

void test_has_moved_flag() {
    King k(true);

    // Default should be false
    assert(!k.getHasKingMoved());

    k.setHasKingMoved(true);
    assert(k.getHasKingMoved());

    k.setHasKingMoved(false);
    assert(!k.getHasKingMoved());
}

int main() {
    test_valid_king_moves();
    test_invalid_king_moves();
    test_same_square_throws();
    test_out_of_bounds();
    test_has_moved_flag();

    std::cout << "King tests passed!\n";
}