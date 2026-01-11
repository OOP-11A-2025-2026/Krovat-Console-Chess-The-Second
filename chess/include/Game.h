#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
private:
    // add equivalent to moves array
    char promotionChoice = ' ';
    Board board;
    std::string gameResult = "*";
    
    Coordinates parseSquare(char file, char rank);
    bool matchesPiece(Piece p, char c);

public:
    Game();
    void start();
    void saveGame(std::string filename);
    void loadGame(std::string filename);
    Coordinates interpretMove(std::string notation, bool whiteTurn);
};

#endif