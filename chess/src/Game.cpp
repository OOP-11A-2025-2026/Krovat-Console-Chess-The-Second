#include "../include/Game.h"

// Converts file/rank to coordinates
Coordinates parseSquare(char file, char rank) {
    return Coordinates(8 - (rank - '0'), file - 'a');
}

// Checks if a piece matches a SAN character
bool matchesPiece(Piece* p, char c) {
    switch (c) 
    {
        case 'P': return dynamic_cast<Pawn*>(p) != nullptr;
        case 'N': return dynamic_cast<Knight*>(p) != nullptr;
        case 'B': return dynamic_cast<Bishop*>(p) != nullptr;
        case 'R': return dynamic_cast<Rook*>(p) != nullptr;
        case 'Q': return dynamic_cast<Queen*>(p) != nullptr;
        case 'K': return dynamic_cast<King*>(p) != nullptr;
        default: return false;
    }
}

// Interprets a move in Standard Algebraic Notation (SAN) and returns the corresponding coordinates
std::pair<Coordinates, Coordinates> Game::interpretMove(std::string notationRaw, bool whiteTurn) 
{
    std::string notation = notationRaw;
    // Remove check/mate symbols
    notation.erase(std::remove(notation.begin(), notation.end(), '+'), notation.end());
    notation.erase(std::remove(notation.begin(), notation.end(), '#'), notation.end());

    // Castling
    if (notation == "O-O" || notation == "0-0") 
    {
        int row = whiteTurn ? 7 : 0;
        return { Coordinates(row, 4), Coordinates(row, 6) };
    }
    if (notation == "O-O-O" || notation == "0-0-0") 
    {
        int row = whiteTurn ? 7 : 0;
        return { Coordinates(row, 4), Coordinates(row, 2) };
    }

    // Promotion
    if (notation.find('=') != std::string::npos) 
    {
        promotionChoice = notation.back();
        notation = notation.substr(0, notation.find('='));
    }

    // Capture
    bool isCapture = notation.find('x') != std::string::npos;
    notation.erase(std::remove(notation.begin(), notation.end(), 'x'), notation.end());

    // Destination square
    char file = notation[notation.length() - 2];
    char rank = notation[notation.length() - 1];
    Coordinates to = parseSquare(file, rank);

    // Piece type
    char pieceChar = std::isupper(notation[0]) ? notation[0] : 'P';

    // Disambiguation by file or rank
    char disFile = 0;
    char disRank = 0;
    
    if (notation.length() == 4) 
    {
        char d = notation[1];
        if (std::isdigit(d)) disRank = d;
        else disFile = d;
    }

    // Pawn capture disambiguation
    if (pieceChar == 'P' && isCapture) 
    {
        disFile = notation[0];
    }

    // Find candidate starting squares
    std::vector<Coordinates> candidates;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Coordinates from(i, j);
            Piece* p = board.getPiece(from);

            // Skipping a square if there isn't a piece on it, if the piece is the wrong type or color
            if (!p) continue;
            if (p->getIsWhite() != whiteTurn) continue;
            if (!matchesPiece(*p, pieceChar)) continue;

            // Skipping a piece if it does not match the file/rank disambiguation
            if (disFile && j != disFile - 'a') continue;
            if (disRank && i != 8 - (disRank - '0')) continue;

            char promotion = (promotionChoice == ' ') ? 'Q' : promotionChoice;
            
            // Checking if the move is legal, if it isn't it is not a valid candidate
            if (board.isLegalMove(from, to, whiteTurn, promotion)) {
                candidates.push_back(from);
            }
        }
    }

    if (candidates.empty()) 
    {
        throw InvalidMove("No legal move found for notation: " + notation);
    }
    
    if (candidates.size() > 1) 
    {
        throw InvalidMove("Ambiguous SAN: " + notation);
    }

    return { candidates[0], to };
}