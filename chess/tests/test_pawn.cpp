#include <cassert>
#include <iostream>

#include "../include/Pawn.h"

void test_white_pawn_basic_moves() {
    Pawn p(true);
    Coordinates from{6, 4};

    // One square forward
    assert(p.regularMovement(from, {5, 4}));

    // Two squares forward on first move
    assert(p.regularMovement(from, {4, 4}));
}

void test_white_pawn_invalid_moves() {
    Pawn p(true);
    Coordinates from{6, 4};

    // Backwards
    assert(!p.regularMovement(from, {7, 4}));

    // Sideways
    assert(!p.regularMovement(from, {6, 5}));

    // Too far
    assert(!p.regularMovement(from, {3, 4}));
}

void test_black_pawn_basic_moves() {
    Pawn p(false);
    Coordinates from{1, 3};

    // One square forward
    assert(p.regularMovement(from, {2, 3}));

    // Two squares forward on first move
    assert(p.regularMovement(from, {3, 3}));
}

void test_black_pawn_invalid_moves() {
    Pawn p(false);
    Coordinates from{1, 3};

    // Backwards
    assert(!p.regularMovement(from, {0, 3}));

    // Sideways
    assert(!p.regularMovement(from, {1, 4}));

    // Too far
    assert(!p.regularMovement(from, {4, 3}));
}

void test_diagonal_pawn_moves() {
    Pawn p(true);
    Coordinates from{6, 4};

    // Diagonal movement allowed (capture handled by Board)
    assert(p.regularMovement(from, {5, 5}));
    assert(p.regularMovement(from, {5, 3}));
}

void test_double_move_after_moved_fails() {
    Pawn p(true);
    Coordinates from{6, 4};

    p.setHasPawnMoved(true);

    assert(!p.regularMovement(from, {4, 4}));
}

void test_out_of_bounds_moves() {
    Pawn p(true);

    assert(!p.regularMovement({0, 4}, {-1, 4}));
    
    Pawn p2(false);

    assert(!p2.regularMovement({7, 4}, {8, 4}));
}

void test_pawn_state_flags() {
    Pawn p(true);

    // hasPawnMoved
    assert(!p.getHasPawnMoved());
    p.setHasPawnMoved(true);
    assert(p.getHasPawnMoved());

    // enPassantEligible
    assert(!p.isEnPassantEligible());
    p.setEnPassantEligible(true);
    assert(p.isEnPassantEligible());
}

int main() {
    test_white_pawn_basic_moves();
    test_white_pawn_invalid_moves();
    test_black_pawn_basic_moves();
    test_diagonal_pawn_moves();
    test_double_move_after_moved_fails();
    test_out_of_bounds_moves();
    test_pawn_state_flags();

    std::cout << "Pawn tests passed!\n";
}