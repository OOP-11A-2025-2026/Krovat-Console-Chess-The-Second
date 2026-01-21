#include <cassert>
#include <iostream>
#include <stdexcept>

#include "../include/Knight.h"

void test_initialization() {
    Knight whiteKnight(true);
    Knight blackKnight(false);

    assert(whiteKnight.getIsWhite() == true);
    assert(whiteKnight.getSymbol() == 'N');

    assert(blackKnight.getIsWhite() == false);
    assert(blackKnight.getSymbol() == 'n');
}

void test_copy() {
    Knight original(true);
    Knight* copy = static_cast<Knight*>(original.copy());

    assert(copy->getIsWhite() == original.getIsWhite());
    assert(copy->getSymbol() == original.getSymbol());

    delete copy;
}

void test_valid_knight_moves() {
    Knight k(true);

    Coordinates from{4, 4};

    assert(k.regularMovement(from, {6, 5}));
    assert(k.regularMovement(from, {6, 3}));
    assert(k.regularMovement(from, {2, 5}));
    assert(k.regularMovement(from, {2, 3}));

    assert(k.regularMovement(from, {5, 6}));
    assert(k.regularMovement(from, {3, 6}));
    assert(k.regularMovement(from, {5, 2}));
    assert(k.regularMovement(from, {3, 2}));
}

void test_invalid_knight_moves() {
    Knight k(true);
    Coordinates from{4, 4};

    // Horizontal
    assert(!k.regularMovement(from, {4, 5}));

    // Vertical
    assert(!k.regularMovement(from, {5, 4}));

    // Diagonal
    assert(!k.regularMovement(from, {5, 5}));

    // Random invalid
    assert(!k.regularMovement(from, {7, 5}));
}

void test_same_square_throws() {
    Knight k(true);

    try {
        k.regularMovement({3, 3}, {3, 3});
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }
}

void test_out_of_bounds() {
    Knight k(true);

    assert(!k.regularMovement({1, 0}, {3, -1}));
    assert(!k.regularMovement({1, 0}, {-1, 1}));

    assert(!k.regularMovement({6, 7}, {8, 6}));
    assert(!k.regularMovement({6, 7}, {4, 8}));
}

int main() {
    test_initialization();
    test_copy();
    test_valid_knight_moves();
    test_invalid_knight_moves();
    test_same_square_throws();
    test_out_of_bounds();

    std::cout << "Knight tests passed!\n";
}