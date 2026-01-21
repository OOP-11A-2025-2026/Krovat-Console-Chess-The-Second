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

        assert(blackPawn != nullptr);
        assert(whitePawn != nullptr);

        assert(dynamic_cast<Pawn*>(blackPawn));
        assert(dynamic_cast<Pawn*>(whitePawn));

        assert(!blackPawn->getIsWhite());
        assert(whitePawn->getIsWhite());
    }

    // --- Rooks ---
    Piece* br1 = board.getPiece({0, 0});
    Piece* br2 = board.getPiece({0, 7});
    Piece* wr1 = board.getPiece({7, 0});
    Piece* wr2 = board.getPiece({7, 7});

    assert(dynamic_cast<Rook*>(br1));
    assert(dynamic_cast<Rook*>(br2));
    assert(dynamic_cast<Rook*>(wr1));
    assert(dynamic_cast<Rook*>(wr2));

    assert(!br1->getIsWhite());
    assert(!br2->getIsWhite());
    assert(wr1->getIsWhite());
    assert(wr2->getIsWhite());

    // --- Knights ---
    Piece* bk1 = board.getPiece({0, 1});
    Piece* bk2 = board.getPiece({0, 6});
    Piece* wk1 = board.getPiece({7, 1});
    Piece* wk2 = board.getPiece({7, 6});

    assert(dynamic_cast<Knight*>(bk1));
    assert(dynamic_cast<Knight*>(bk2));
    assert(dynamic_cast<Knight*>(wk1));
    assert(dynamic_cast<Knight*>(wk2));

    assert(!bk1->getIsWhite());
    assert(!bk2->getIsWhite());
    assert(wk1->getIsWhite());
    assert(wk2->getIsWhite());

    // --- Bishops ---
    Piece* bb1 = board.getPiece({0, 2});
    Piece* bb2 = board.getPiece({0, 5});
    Piece* wb1 = board.getPiece({7, 2});
    Piece* wb2 = board.getPiece({7, 5});

    assert(dynamic_cast<Bishop*>(bb1));
    assert(dynamic_cast<Bishop*>(bb2));
    assert(dynamic_cast<Bishop*>(wb1));
    assert(dynamic_cast<Bishop*>(wb2));

    assert(!bb1->getIsWhite());
    assert(!bb2->getIsWhite());
    assert(wb1->getIsWhite());
    assert(wb2->getIsWhite());

    // --- Queens ---
    Piece* bq = board.getPiece({0, 3});
    Piece* wq = board.getPiece({7, 3});

    assert(dynamic_cast<Queen*>(bq));
    assert(dynamic_cast<Queen*>(wq));

    assert(!bq->getIsWhite());
    assert(wq->getIsWhite());

    // --- Kings ---
    Piece* bk = board.getPiece({0, 4});
    Piece* wk = board.getPiece({7, 4});

    assert(dynamic_cast<King*>(bk));
    assert(dynamic_cast<King*>(wk));

    assert(!bk->getIsWhite());
    assert(wk->getIsWhite());

    // --- Empty squares ---
    for (int row = 2; row <= 5; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            assert(board.getPiece({row, col}) == nullptr);
        }
    }
}

void testBoardDestructor() {
    // Single destruction
    {
        Board board;
    }

    // Stress test: repeated construction/destruction
    for (int i = 0; i < 100; i++) {
        Board* board = new Board();
        delete board;
    }
}

int main() {
    //testBoardConstructor();
    testBoardDestructor();

    std::cout << "All Board constructor/destructor tests passed!\n";
    return 0;
}