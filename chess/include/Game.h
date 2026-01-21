#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>
#include <algorithm>
#include <fstream>

class Game {
private:
    vector<string> movesHistory;
    char promotionChoice = ' ';
    Board board;
    string gameResult = "*";
    
    Coordinates parseSquare(char file, char rank);
    bool matchesPiece(Piece* p, char c);

public:
    void start();
    void saveGame(string filename);
    void loadGame(string filename);
    pair<Coordinates, Coordinates> interpretMove(string notationRaw, bool whiteTurn);
};

#endif