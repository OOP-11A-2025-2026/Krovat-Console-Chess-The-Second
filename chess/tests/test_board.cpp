#include <cassert>
#include <iostream>
#include "../include/Board.h"

void testBoardConstructor() {
    Board board;

    // --- Pawns ---
    for (int col = 0; col < BOARD_SIZE; col++) 
    {
        Piece* blackPawn = board.getPiece({1, col});
        Piece* whitePawn = board.getPiece({6, col});

        assert(blackPawn && dynamic_cast<Pawn*>(blackPawn) && !blackPawn->getIsWhite());
        assert(whitePawn && dynamic_cast<Pawn*>(whitePawn) && whitePawn->getIsWhite());
    }

    // --- Knights ---
    Piece* wk1 = board.getPiece({7, 1});
    Piece* wk2 = board.getPiece({7, 6});
    assert(dynamic_cast<Knight*>(wk1) && wk1->getIsWhite());
    assert(dynamic_cast<Knight*>(wk2) && wk2->getIsWhite());
}

void testPawnMove() {
    Board board;

    Coordinates from{6, 4}; // e2
    Coordinates to{4, 4};   // e4

    assert(board.isLegalMove(from, to, true, ' '));
    int result = board.makeMove(from, to, true, ' ');
    assert(result == NORMAL);

    // Pawn moved
    Piece* moved = board.getPiece(to);
    assert(dynamic_cast<Pawn*>(moved) && moved->getIsWhite());
    assert(board.getPiece(from) == nullptr);
}

void testKnightMove() {
    Board board;

    Coordinates from{7, 6}; // g1
    Coordinates to{5, 5};   // f3

    assert(board.isLegalMove(from, to, true, ' '));
    int result = board.makeMove(from, to, true, ' ');
    assert(result == NORMAL);

    Piece* moved = board.getPiece(to);
    assert(dynamic_cast<Knight*>(moved) && moved->getIsWhite());
    assert(board.getPiece(from) == nullptr);
}

void testCapture() {
    Board board;

    // White pawn e2->e4
    board.makeMove({6, 4}, {4, 4}, true, ' ');

    // Black pawn d7->d5
    board.makeMove({1, 3}, {3, 3}, false, ' ');

    // e4xd5
    assert(board.isLegalMove({4, 4}, {3, 3}, true, ' '));
    board.makeMove({4, 4}, {3, 3}, true, ' ');
    assert(board.getPiece({3, 3}) && board.getPiece({3, 3})->getIsWhite());
}

void testBoardReset() {
    Board board;
    board.makeMove({6, 4}, {4, 4}, true, ' '); // e2->e4
    board.reset();
    assert(board.getPiece({6, 4}) && dynamic_cast<Pawn*>(board.getPiece({6,4})));
    assert(board.getPiece({4, 4}) == nullptr);
}

int main() {
    testBoardConstructor();
    testPawnMove();
    testKnightMove();
    testCapture();
    testBoardReset();

    std::cout << "All Board tests passed!\n";
    return 0;
}
