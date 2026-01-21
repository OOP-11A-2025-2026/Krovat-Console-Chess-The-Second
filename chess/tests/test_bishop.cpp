#include <cassert>
#include <iostream>
#include <stdexcept>

#include "../include/Bishop.h"

void test_initialization() {
    Bishop whiteBishop(true);
    Bishop blackBishop(false);

    assert(whiteBishop.getIsWhite() == true);
    assert(whiteBishop.getSymbol() == 'B');

    assert(blackBishop.getIsWhite() == false);
    assert(blackBishop.getSymbol() == 'b');
}

void test_copy() {
    Bishop original(true);
    Piece* copyPiece = original.copy();
    Bishop* copiedBishop = dynamic_cast<Bishop*>(copyPiece);

    assert(copiedBishop != nullptr);
    assert(copiedBishop->getIsWhite() == original.getIsWhite());
    assert(copiedBishop->getSymbol() == original.getSymbol());

    delete copyPiece;
}

void test_diagonal_moves() {
    Bishop b(true);

    assert(b.regularMovement({4, 4}, {7, 7}));
    assert(b.regularMovement({4, 4}, {0, 0}));

    assert(b.regularMovement({4, 4}, {1, 7}));
    assert(b.regularMovement({4, 4}, {7, 1}));

    assert(b.regularMovement({4, 3}, {0, 7}));
    assert(b.regularMovement({4, 3}, {7, 0}));
}

void test_non_diagonal_moves() {
    Bishop b(true);

    // Horizontal
    assert(!b.regularMovement({4, 4}, {4, 5}));

    // Vertical
    assert(!b.regularMovement({4, 4}, {5, 4}));

    // Knight-like
    assert(!b.regularMovement({4, 4}, {5, 6}));
}

void test_same_square_throws() {
    Bishop b(true);

    try {
        b.regularMovement({3, 3}, {3, 3});
        assert(false); // Should never reach here
    } catch (const std::invalid_argument&) {
        assert(true);
    }
}

void test_out_of_bounds() {
    Bishop b(true);

    // Negative
    assert(!b.regularMovement({4, 4}, {-1, -1}));

    // Too large
    assert(!b.regularMovement({4, 4}, {8, 8}));
}

int main() {
    test_initialization();
    test_copy();
    test_diagonal_moves();
    test_non_diagonal_moves();
    test_same_square_throws();
    test_out_of_bounds();

    std::cout << "Bishop tests passed!\n";
}