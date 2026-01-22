#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>

class Game {
private:
    std::vector<std::string> movesHistory;
    char promotionChoice = ' ';
    Board board;
    std::string gameResult = "*";
    
    Coordinates parseSquare(char file, char rank);
    bool matchesPiece(Piece* p, char c);

public:
    void start();
    void saveGame(std::string filename);
    void loadGame(const std::string& filename);
    std::pair<Coordinates, Coordinates> interpretMove(const std::string notationRaw, bool whiteTurn, char& promotionChoiceOut);
    std::vector<std::string> getMovesHistory() const;
};

#endif