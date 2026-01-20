#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
private:
    // add equivalent to moves array - please do not remove this comment if you don't replese it with the needed code, so we don't forget about it
    char promotionChoice = ' ';
    Board board;
    std::string gameResult = "*";
    
    Coordinates parseSquare(char file, char rank);
    bool matchesPiece(Piece& p, char c);

public:
    Game();
    void start();
    void saveGame(std::string filename);
    void loadGame(std::string filename);
    Coordinates interpretMove(std::string notation, bool whiteTurn);
};

#endif