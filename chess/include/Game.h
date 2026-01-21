#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>

class Game {
private:
    std::vector<std::string> movesHistory;
    char promotionChoice = ' ';
    Board board;
    std::string gameResult = "*";
    
    Coordinates parseSquare(char file, char rank);
    bool matchesPiece(Piece& p, char c);

public:
    void start();
    void saveGame(std::string filename);
    void loadGame(std::string filename);
    std::pair<Coordinates, Coordinates> interpretMove(std::string notationRaw, bool whiteTurn);
};

#endif