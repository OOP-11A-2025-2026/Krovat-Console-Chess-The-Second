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

std::vector<std::string> Game::getMovesHistory() const { 
    return movesHistory; 
}


// Interprets a move in Standard Algebraic Notation (SAN) and returns the corresponding coordinates
pair<Coordinates, Coordinates> Game::interpretMove(const string notationRaw, bool whiteTurn, char &promotionChoiceOut) {
    string notation = notationRaw;

    // Remove check/mate symbols
    notation.erase(remove(notation.begin(), notation.end(), '+'), notation.end());
    notation.erase(remove(notation.begin(), notation.end(), '#'), notation.end());

    // Castling
    if (notation == "O-O" || notation == "0-0") {
        int row = whiteTurn ? 7 : 0; // White back rank = 7
        return { Coordinates(row, 4), Coordinates(row, 6) };
    }
    if (notation == "O-O-O" || notation == "0-0-0") {
        int row = whiteTurn ? 7 : 0;
        return { Coordinates(row, 4), Coordinates(row, 2) };
    }

    // Promotion
    size_t eqPos = notation.find('=');
    if (eqPos != string::npos) {
        promotionChoiceOut = notation.back();
        notation = notation.substr(0, eqPos);
    } else {
        promotionChoiceOut = ' ';
    }

    // Capture
    bool isCapture = notation.find('x') != string::npos;
    notation.erase(remove(notation.begin(), notation.end(), 'x'), notation.end());

    // Destination square (last two characters)
    if (notation.size() < 2)
        throw InvalidMove("Invalid notation: " + notationRaw);
    char destFile = notation[notation.size() - 2];
    char destRank = notation[notation.size() - 1];
    Coordinates to = parseSquare(destFile, destRank);

    // Piece type
    char pieceChar = isupper(notation[0]) ? notation[0] : 'P';

    // Disambiguation (optional file/rank)
    char disFile = 0;
    char disRank = 0;
    for (size_t i = 1; i < notation.size() - 2; ++i) {
        if (isdigit(notation[i])) disRank = notation[i];
        else disFile = notation[i];
    }

    // Pawn capture disambiguation
    if (pieceChar == 'P' && isCapture) disFile = notation[0];

    // Find candidate starting squares
    vector<Coordinates> candidates;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            Coordinates from(row, col);
            Piece* p = board.getPiece(from);
            if (!p) continue;
            if (p->getIsWhite() != whiteTurn) continue;
            if (!matchesPiece(p, pieceChar)) continue;
            if (disFile && col != disFile - 'a') continue;
            if (disRank && row != 8 - (disRank - '0')) continue;

            // Promotion defaults to Queen if not specified
            char promotion = (promotionChoiceOut == ' ') ? 'Q' : promotionChoiceOut;
            if (board.isLegalMove(from, to, whiteTurn, promotion))
                candidates.push_back(from);
        }
    }

    if (candidates.empty())
        throw InvalidMove("No legal move found for notation: " + notationRaw);
    if (candidates.size() > 1)
        throw InvalidMove("Ambiguous SAN: " + notationRaw);

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

    if(gameResult != "*")
        out << endl << gameResult << endl;
}

void Game::loadGame(const string& filename) {
    ifstream in(filename);
    if (!in) throw runtime_error("Cannot open file for reading.");

    movesHistory.clear();
    promotionChoice = ' ';
    gameResult = "*";

    string line;
    vector<string> tokens;

    while (getline(in, line)) {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty()) continue;
        if (line[0] == '[') continue; // PGN tags

        // Remove comments { ... }
        size_t pos;
        while ((pos = line.find('{')) != string::npos) {
            size_t end = line.find('}', pos);
            if (end == string::npos) break;
            line.erase(pos, end - pos + 1);
        }

        stringstream ss(line);
        string token;

        while (ss >> token) {
            // Strip move numbers like "1." or "23..."
            size_t dotPos = token.find('.');
            if (dotPos != string::npos) {
                token = token.substr(dotPos + 1);
            }

            if (token.empty()) continue;

            // Game results
            if (token == "1-0") {
                gameResult = "White wins!";
                continue;
            }
            if (token == "0-1") {
                gameResult = "Black wins!";
                continue;
            }
            if (token == "1/2-1/2") {
                gameResult = "Draw!";
                continue;
            }


            tokens.push_back(token);
        }
    }

    // Replay all moves from the starting position
    bool whiteTurn = true;
    for (const string& move : tokens) {
        char movePromotion = ' ';
        auto [from, to] = interpretMove(move, whiteTurn, movePromotion);
        board.makeMove(from, to, whiteTurn, movePromotion);
        movesHistory.push_back(move);
        whiteTurn = !whiteTurn;
    }
}


void Game::start() {
    bool whiteTurn = true;
    cout << "1 - New Game\n2 - Load Game\nChoice: ";
    string choice;
    cin >> choice;

    if (choice == "2") {
        cout << "Enter PGN filename to load: ";
        string filename;
        cin >> filename;
        if (!filename.empty()) {
            try {
                loadGame(filename);
                whiteTurn = (movesHistory.size() % 2 == 0);
                cout << "Game loaded.\n";
            } catch (exception& e) {
                cout << "Load failed: " << e.what() << endl;
                return;
            }
        } else {
            cout << "No filename provided.\n";
            return;
        }
    } else if (choice != "1") {
        cout << "Invalid choice.\n";
        return;
    }

    while (true) {
        cout << board.toString() << endl;
        if (gameResult != "*") {
            cout << "The game is already finished: " << gameResult << endl;
            break;
        }

        cout << (whiteTurn ? "White" : "Black") << "'s turn\n";
        cout << "Options: [1] Move  [2] Undo Last Move  [3] Save  [4] Offer Draw  [5] Resign\nChoice: ";
        string input;
        cin >> input;

        if (input == "3") { // Save
            cout << "Enter filename (e.g. game.pgn): ";
            string filename;
            cin >> filename;
            if (filename.empty()) filename = "game.pgn";
            try { saveGame(filename); } 
            catch (exception& e) { cout << "Save failed: " << e.what() << endl; }
            continue;
        }

        if (input == "4") { // Draw
            cout << "Opponent, accept draw? (y/n): ";
            string response;
            cin >> response;
            if (response == "y" || response == "Y") {
                cout << "Game drawn by agreement.\n";
                break;
            } else {
                cout << "Draw declined. Game continues.\n";
                continue;
            }
        }

        if (input == "5") { // Resign
            cout << (whiteTurn ? "White" : "Black") << " resigns\n";
            cout << (whiteTurn ? "Black" : "White") << " wins!\n";
            break;
        }

        if (input == "2") { // Undo
            try {
                board.undoMove();
                whiteTurn = !whiteTurn;
            } catch (InvalidMove& e) {
                cout << "Undo failed: " << e.what() << endl;
            }
            continue;
        }

        if (input == "1") { // Move
            cout << "Enter move (e.g. e4, Nf3, O-O): ";
            cin >> input;
        }

        try {
            auto [from, to] = interpretMove(input, whiteTurn, promotionChoice);
            int result = board.makeMove(from, to, whiteTurn, promotionChoice);
            promotionChoice = ' ';
            movesHistory.push_back(input);

            if (result == CHECKMATE) {
                cout << board.toString() << "\nCHECKMATE! " << (whiteTurn ? "White" : "Black") << " wins.\n";
                break;
            } else if (result == STALEMATE) {
                cout << board.toString() << "\nSTALEMATE! Game drawn.\n";
                break;
            }

            whiteTurn = !whiteTurn;

        } catch (InvalidMove& e) {
            cout << "Invalid Move: " << e.what() << endl;
        }
    }
}
