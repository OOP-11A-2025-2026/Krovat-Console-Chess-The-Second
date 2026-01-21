#include "../include/Game.h"

using namespace std;

// Converts file/rank to coordinates
Coordinates Game::parseSquare(char file, char rank) {
    return Coordinates(8 - (rank - '0'), file - 'a');
}

// Checks if a piece matches a SAN character
bool Game::matchesPiece(Piece* p, char c) {
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
pair<Coordinates, Coordinates> Game::interpretMove(string notationRaw, bool whiteTurn) 
{
    string notation = notationRaw;
    // Remove check/mate symbols
    notation.erase(remove(notation.begin(), notation.end(), '+'), notation.end());
    notation.erase(remove(notation.begin(), notation.end(), '#'), notation.end());

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
    if (notation.find('=') != string::npos) 
    {
        promotionChoice = notation.back();
        notation = notation.substr(0, notation.find('='));
    }

    // Capture
    bool isCapture = notation.find('x') != string::npos;
    notation.erase(remove(notation.begin(), notation.end(), 'x'), notation.end());

    // Destination square
    char file = notation[notation.length() - 2];
    char rank = notation[notation.length() - 1];
    Coordinates to = parseSquare(file, rank);

    // Piece type
    char pieceChar = isupper(notation[0]) ? notation[0] : 'P';

    // Disambiguation by file or rank
    char disFile = 0;
    char disRank = 0;
    
    if (notation.length() == 4) 
    {
        char d = notation[1];
        if (isdigit(d)) disRank = d;
        else disFile = d;
    }

    // Pawn capture disambiguation
    if (pieceChar == 'P' && isCapture) 
    {
        disFile = notation[0];
    }

    // Find candidate starting squares
    vector<Coordinates> candidates;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Coordinates from(i, j);
            Piece* p = board.getPiece(from);

            // Skipping a square if there isn't a piece on it, if the piece is the wrong type or color
            if (!p) continue;
            if (p->getIsWhite() != whiteTurn) continue;
            if (!matchesPiece(p, pieceChar)) continue;

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

void Game::saveGame(string filename) {
    ofstream out(filename);
    if(!out)
        throw runtime_error("Cannot open file for writing.");

    for(size_t i = 0; i < movesHistory.size(); i++) {
        out << movesHistory[i];
        if(i + 1 < movesHistory.size())
            out << ' ';
    }

    out << endl << gameResult << endl;
}

void Game::loadGame(string filename) {
    ifstream in(filename);
    if(!in)
        throw runtime_error("Cannot open file for reading.");

    board.reset();
    movesHistory.clear();
    promotionChoice = ' ';
    gameResult = "*";

    string movesLine;
    getline(in, movesLine);

    stringstream ss(movesLine);
    string move;
    bool whiteTurn = true;

    while (ss >> move) {
        auto [from, to] = interpretMove(move, whiteTurn);

        board.makeMove(from, to, whiteTurn, promotionChoice);
        movesHistory.push_back(move);

        promotionChoice = ' ';
        whiteTurn = !whiteTurn;
    }

    if (!getline(in, gameResult))
        gameResult = "*";
}

void Game::start() {
    cout << "1 - New Game" << endl << "2 - Load Game" << endl << "Choice: ";
    string choice;
    cin >> choice;

    bool whiteTurn = true;

    if (choice == "2") {
        cout << "Enter PGN filename to load: ";
        string filename;
        cin >> filename;
        if (filename.empty()) {
            cout << "No filename provided." << endl;
            return;
        }
        try {
            loadGame(filename);
            whiteTurn = (movesHistory.size() % 2 == 0);
            cout << "Game loaded." << endl;
        } catch (exception& e) {
            cout << "Load failed: " << e.what() << endl;
            return;
        }
    }
    else if (choice != "1") {
        cout << "Invalid choice." << endl;
        return;
    }

    while (true) {
        cout << board.toString() << endl;

        if (gameResult != "*") {
            cout << "The game is already finished: " << gameResult << endl;
            break;
        }

        cout << (whiteTurn ? "White" : "Black") << "'s turn" << endl;
        cout << "Options: [1] Move  [2] Undo Last Move  [3] Save  [4] Offer Draw  [5] Resign" << endl;
        cout << "Choice: ";
        string input;
        cin >> input;

        // Save game
        if (input == "3") {
            cout << "Enter filename (e.g. game.pgn): ";
            string filename;
            cin >> filename;
            if (filename.empty()) filename = "game.pgn";
            try {
                saveGame(filename);
                cout << "Game saved to " << filename << endl;
            } catch (exception& e) {
                cout << "Save failed: " << e.what() << endl;
            }
            continue;
        }

        // Offer draw
        if (input == "4") {
            cout << "Opponent, do you accept the draw? (y/n): ";
            string response;
            cin >> response;
            if (response == "y" || response == "Y") {
                cout << "Game drawn by agreement." << endl;
                break;
            } else {
                cout << "Draw declined. The game continues." << endl;
                continue;
            }
        }

        // Resign
        if (input == "5") {
            cout << (whiteTurn ? "White" : "Black") << " resigns." << endl;
            cout << (whiteTurn ? "Black" : "White") << " wins!" << endl;
            break;
        }

        // Undo
        if (input == "2") {
            try {
                board.undoMove();
                whiteTurn = !whiteTurn;
            } catch (InvalidMove& e) {
                cout << "Undo failed: " << e.what() << endl;
            }
            continue;
        }

        // Move
        if (input == "1") {
            cout << "Enter move (e.g. e4, Nf3, O-O): ";
            string moveStr;
            cin >> moveStr;

            try {
                auto [from, to] = interpretMove(moveStr, whiteTurn);
                int result = board.makeMove(from, to, whiteTurn, promotionChoice);
                movesHistory.push_back(moveStr);
                promotionChoice = ' ';

                if (result == CHECKMATE) {
                    cout << board.toString() << endl;
                    cout << "CHECKMATE! " << (whiteTurn ? "White" : "Black") << " wins." << endl;
                    break;
                }
                if (result == STALEMATE) {
                    cout << board.toString() << endl;
                    cout << "STALEMATE! Game drawn." << endl;
                    break;
                }

                whiteTurn = !whiteTurn;

            } catch (InvalidMove& e) {
                cout << "Invalid move: " << e.what() << endl;
            }
            continue;
        }

        // If input wasn't recognized
        cout << "Invalid option. Please choose again." << endl;
    }
}
