#include <cassert>
#include <iostream>
#include "../include/Game.h"

void testInterpretMove() {
    Game game;

    char promo;
    auto [from, to] = game.interpretMove("e4", true, promo);
    assert(from.first == 6 && from.second == 4); // e2
    assert(to.first == 4 && to.second == 4);     // e4
    assert(promo == ' ');

    auto [kFrom, kTo] = game.interpretMove("Nf3", true, promo);
    assert(kFrom.first == 7 && kFrom.second == 6); // g1
    assert(kTo.first == 5 && kTo.second == 5);     // f3
}

void testLoadGame() {
    Game game;

    // We'll create a temporary PGN in memory
    std::string filename = "test.pgn";
    std::ofstream out(filename);
    out << "1. e4 e5 2. Nf3 Nc6\n";
    out.close();

    game.loadGame(filename);

    // Moves history size
    assert(game.getMovesHistory().size() == 4);
    assert(game.getMovesHistory()[0] == "e4");
    assert(game.getMovesHistory()[1] == "e5");
    assert(game.getMovesHistory()[2] == "Nf3");
    assert(game.getMovesHistory()[3] == "Nc6");
}

int main() {
    testInterpretMove();
    testLoadGame();

    std::cout << "All Game tests passed!\n";
    return 0;
}
