#include "../include/Board.h"

// Default constructor to initialize the chess board with pieces in starting positions
// Above is black in lowercase letters, below is white in uppercase letters
Board::Board() {
    // Initialize an empty board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            squares[i][j] = nullptr;
            undoSquares[i][j] = nullptr;
        }
    }

    // Pawns
    for (int j = 0; j < BOARD_SIZE; j++) {
        squares[1][j] = new Pawn(false);
        squares[6][j] = new Pawn(true);
    }

    // Rooks
    squares[0][0] = new Rook(false);
    squares[0][7] = new Rook(false);
    squares[7][0] = new Rook(true);
    squares[7][7] = new Rook(true);

    // Knights
    squares[0][1] = new Knight(false);
    squares[0][6] = new Knight(false);
    squares[7][1] = new Knight(true);
    squares[7][6] = new Knight(true);

    // Bishops
    squares[0][2] = new Bishop(false);
    squares[0][5] = new Bishop(false);
    squares[7][2] = new Bishop(true);
    squares[7][5] = new Bishop(true);

    // Queens
    squares[0][3] = new Queen(false);
    squares[7][3] = new Queen(true);

    // Kings
    squares[0][4] = new King(false);
    squares[7][4] = new King(true);
}

// Destructor to clean up dynamically allocated pieces
Board::~Board() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            delete squares[i][j];
            delete undoSquares[i][j];
        }
}

// Save the current board state for undo functionality
void Board::saveUndoState() {
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            delete undoSquares[i][j]; // Clean up previous undo state
            if (squares[i][j] != nullptr) 
                undoSquares[i][j] = squares[i][j]->copy();
            else
                undoSquares[i][j] = nullptr;
        }
    }
    undoAvailable = true;
}

// Undo the last move by restoring the previous board state
void Board::undoMove() {
    if (!undoAvailable)
        throw InvalidMove("No move to undo");

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            delete squares[i][j]; // Clean up current board state
            squares[i][j] = undoSquares[i][j];
            undoSquares[i][j] = nullptr;
        }
    }

    undoAvailable = false;
}

// Get the coordinates of the king of the specified color
Coordinates Board::getKingCoordinates(bool isKingWhite) {
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (squares[i][j] != nullptr) 
            {
                King* k = dynamic_cast<King*>(squares[i][j]);
                if (k && k->getIsWhite() == isKingWhite) return Coordinates(i, j);
            }
        }
    }
    throw InvalidMove("King not found");
}

// Verify that the given coordinates are within the bounds of the board
void Board::verifyCoordinates(Coordinates coords) {
    if (coords.first < 0 || coords.first >= BOARD_SIZE || coords.second < 0 || coords.second >= BOARD_SIZE)
        throw std::invalid_argument("Coordinates out of bounds");
}

Piece* Board::getPiece(Coordinates coords) {
    verifyCoordinates(coords);
    return squares[coords.first][coords.second];
}

// Check if the king of the specified color is in check
bool Board::checkCheck(bool isKingWhite) {
    bool opponentIsWhite = !isKingWhite;
    
    Coordinates king = getKingCoordinates(isKingWhite);
    
    Piece* piece;
    int row = king.first, col = king.second;
    
    // Checking down - Queens and Rooks
    for (int i = row + 1; i < BOARD_SIZE; i++) 
    {
        piece = squares[i][col];
        if (!piece) continue;

        if (piece->getIsWhite() == opponentIsWhite && (dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece)))
            return true;
        break;
    }

    // Checking up - Queens and Rooks
    for (int i = row - 1; i >= 0; i--) 
    {
        piece = squares[i][col];
        if (!piece) continue;

        if (piece->getIsWhite() == opponentIsWhite && (dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece)))
            return true;
        break;
    }

    // Checking right - Queens and Rooks
    for (int i = col + 1; i < BOARD_SIZE; i++) 
    {
        piece = squares[row][i];
        if (!piece) continue;

        if (piece->getIsWhite() == opponentIsWhite && (dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece)))
            return true;
        break;
    }

    // Checking left - Queens and Rooks
    for (int i = col - 1; i >= 0; i--) 
    {
        piece = squares[row][i];
        if (!piece) continue;

        if (piece->getIsWhite() == opponentIsWhite && (dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece)))
            return true;
        break;
    }

    // Checking down right diagonal - Queens and Bishops
    for (int i = 1; row + i < BOARD_SIZE && col + i < BOARD_SIZE; i++) 
    {
        piece = squares[row + i][col + i];
        if (!piece) continue;

        if (piece->getIsWhite() == opponentIsWhite && (dynamic_cast<Bishop*>(piece) || dynamic_cast<Queen*>(piece)))
            return true;
        break;
    }

    // Checking down left diagonal - Queens and Bishops
    for (int i = 1; row + i < BOARD_SIZE && col - i >= 0; i++) 
    {
        piece = squares[row + i][col - i];
        if (!piece) continue;

        if (piece->getIsWhite() == opponentIsWhite && (dynamic_cast<Bishop*>(piece) || dynamic_cast<Queen*>(piece)))
            return true;
        break;
    }

    // Checking up right diagonal - Queens and Bishops
    for (int i = 1; row - i >= 0 && col + i < BOARD_SIZE; i++) 
    {
        piece = squares[row - i][col + i];
        if (!piece) continue;

        if (piece->getIsWhite() == opponentIsWhite && (dynamic_cast<Bishop*>(piece) || dynamic_cast<Queen*>(piece)))
            return true;
        break;
    }

    // Checking up left diagonal - Queens and Bishops
    for (int i = 1; row - i >= 0 && col - i >= 0; i++) 
    {
        piece = squares[row - i][col - i];
        if (!piece) continue;

        if (piece->getIsWhite() == opponentIsWhite && (dynamic_cast<Bishop*>(piece) || dynamic_cast<Queen*>(piece)))
            return true;
        break;
    }

    // Knights
    for (auto& knightMove : knightMoves) 
    {
        int nrow = row + knightMove[0], ncol = col + knightMove[1];
        
        if (nrow < 0 || nrow >= BOARD_SIZE || ncol < 0 || ncol >= BOARD_SIZE) continue;
        
        piece = squares[nrow][ncol];
        if (piece && dynamic_cast<Knight*>(piece) && piece->getIsWhite() == opponentIsWhite)
            return true;
    }

    // Pawn checks
    int opponentPawnDirection = isKingWhite ? -1 : 1; // Black pawns move down (small index), white pawns move up (big index)
    int prow = row + opponentPawnDirection;
    if (prow >= 0 && prow < BOARD_SIZE) 
    {
        
        int pLeftCol = col - 1;
        int pRightCol = col + 1;
        
        if (pLeftCol >= 0) 
        {
            piece = squares[prow][pLeftCol];
            if (piece && dynamic_cast<Pawn*>(piece) && piece->getIsWhite() == opponentIsWhite)
                return true;
        }

        if(pRightCol < BOARD_SIZE) 
        {
            piece = squares[prow][pRightCol];
            if (piece && dynamic_cast<Pawn*>(piece) && piece->getIsWhite() == opponentIsWhite)
                return true;
        }
    }

    // Enemy king adjacency check
    for (int dr = -1; dr <= 1; dr++) 
    {
        for (int dc = -1; dc <= 1; dc++) 
        {
            if (dr == 0 && dc == 0) continue;

            int krow = row + dr;
            int kcol = col + dc;

            if (krow < 0 || krow >= BOARD_SIZE || kcol < 0 || kcol >= BOARD_SIZE) continue;

            piece = squares[krow][kcol];
            if (piece && dynamic_cast<King*>(piece) && piece->getIsWhite() != isKingWhite)
                return true;
        }
    }

    return false;
}

// This function checks if there are any pieces between 2 sets of coordinates
// It does not count as a collision if there is a piece on the given sets of coordinates
bool Board::checkCollision(Coordinates from, Coordinates to) {
    verifyCoordinates(from);
    verifyCoordinates(to);
    
    int frow = from.first, fcol = from.second;
    int trow = to.first, tcol = to.second;

    // Row (up and/or down) collision
    if (frow == trow) 
    {
        for (int i = std::min(fcol, tcol) + 1; i < std::max(fcol, tcol); i++)
            if (squares[frow][i]) return true;
    } 
    
    // Column (left and/or right) collision
    else if (fcol == tcol) 
    {
        for (int i = std::min(frow, trow) + 1; i < std::max(frow, trow); i++)
            if (squares[i][fcol]) return true;
    } 
    
    // Diagonal collision
    else if (std::abs(frow - trow) == std::abs(fcol - tcol))
    {
        int rowStep = (trow > frow) ? 1 : -1;
        int colStep = (tcol > fcol) ? 1 : -1;
        
        int r = frow + rowStep;
        int c = fcol + colStep;

        while (r != trow && c != tcol) {
            if (squares[r][c]) return true;
            r += rowStep;
            c += colStep;
        }
    } 
    
    else {
        throw InvalidMove("Coordinates have to be in a straight or diagonal line");
    }

    return false;
}

// Convert the board state to a string representation
std::string Board::toString() {
    std::ostringstream out;
    out << "  | a b c d e f g h\n";
    out << "--+----------------\n";

    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        out << BOARD_SIZE - i << " | ";
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            if (!squares[i][j]) 
                out << ((i % 2 == j % 2) ? "* " : ". ");
            else
                out << squares[i][j]->getSymbol() << ' ';
        }
        out << '\n';
    }
    return out.str();
}

void Board::resetAllEnPassantEligibility() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Pawn* p = dynamic_cast<Pawn*>(squares[i][j]);
            if (p) p->setEnPassantEligible(false);
        }
    }
}

void Board::checkPin(Coordinates from, Coordinates to) {
    verifyCoordinates(from);
    verifyCoordinates(to);
    
    Piece* movingPiece = getPiece(from);
    Piece* capturedPiece = getPiece(to);

    // Make the move (assigning pointers)
    squares[to.first][to.second] = movingPiece;
    squares[from.first][from.second] = nullptr;

    bool inCheck = checkCheck(movingPiece->getIsWhite());

    // Undo the move
    squares[from.first][from.second] = movingPiece;
    squares[to.first][to.second] = capturedPiece;

    if (inCheck) throw std::invalid_argument("Move leaves king in check");
}

void Board::enPassant(Coordinates from, Coordinates to) {
    verifyCoordinates(from);
    verifyCoordinates(to);
    
    Piece* p1 = getPiece(from);
    
    delete squares[from.first][to.second]; 
    squares[from.first][to.second] = nullptr; 

    squares[to.first][to.second] = p1;
    squares[from.first][from.second] = nullptr;
    
    static_cast<Pawn*>(p1)->setHasPawnMoved(true);
    resetAllEnPassantEligibility();
}

void Board::promotion(Coordinates coords, char choice) {
    verifyCoordinates(coords);

    Pawn* p = dynamic_cast<Pawn*>(getPiece(coords));
    if (!p) return;

    // Check if the pawn is on the last rank
    if ((p->getIsWhite() && coords.first != 0) || (!p->getIsWhite() && coords.first != 7))
        return;

    bool w = p->getIsWhite();
    Piece* n = nullptr;

    switch (toupper(choice)) {
        case 'R': n = new Rook(w); break;
        case 'B': n = new Bishop(w); break;
        case 'N': n = new Knight(w); break;
        default:  n = new Queen(w); break;
    }

    // Clean up the memory of the pawn before replacing the pointer
    delete squares[coords.first][coords.second]; 
    squares[coords.first][coords.second] = n;
}

bool Board::checkEnPassant(Coordinates from, Coordinates to) {
    verifyCoordinates(from);
    verifyCoordinates(to);

    Pawn* p1 = dynamic_cast<Pawn*>(getPiece(from));
    if (!p1) return false;

    int direction = p1->getIsWhite() ? -1 : 1;
    
    // 1. Must move diagonally one square
    if ((int)to.first - (int)from.first != direction || 
        std::abs((int)to.second - (int)from.second) != 1) {
        return false;
    }

    // 2. Target square must be empty
    if (getPiece(to) != nullptr) return false;

    // 3. Enemy pawn must be at the same row as 'from' and same column as 'to'
    Coordinates enemyCoords = { from.first, to.second };
    Pawn* p2 = dynamic_cast<Pawn*>(getPiece(enemyCoords));

    // 4. Enemy must be a Pawn, opposite color, and eligible
    if (p2 && p2->getIsWhite() != p1->getIsWhite() && p2->isEnPassantEligible()) {
        return true;
    }
    return false;
}

int Board::makeMove(Coordinates from, Coordinates to, bool isWhiteTurn, char promotionChoice) {
    verifyCoordinates(from);
    verifyCoordinates(to);

    Piece* moving = getPiece(from);
    if (!moving)
        throw InvalidMove("No piece on starting square");

    // Turn validation
    if (moving->getIsWhite() != isWhiteTurn)
        throw InvalidMove("Not your turn");

    // Correct color capture validation
    Piece* target = getPiece(to);
    if (target && target->getIsWhite() == isWhiteTurn)
        throw InvalidMove("Cannot capture your own piece");

    // Castling
    if (dynamic_cast<King*>(moving)) 
    {
        if (checkCastle(from, to)) 
        {
            saveUndoState();
            castle(from, to);
            return 0;
        }
    }

    // En Passant
    if (dynamic_cast<Pawn*>(moving)) 
    {
        if (checkEnPassant(from, to)) 
        {
            saveUndoState();
            enPassant(from, to);
            resetAllEnPassantEligibility();
            return 0;
        }
    }

    // Regular movement check
    if (!moving->regularMovement(from, to))
        throw InvalidMove("Illegal movement");

    // Pawn movement and capture extra checks
    if (dynamic_cast<Pawn*>(moving)) 
    {
        int colDiff = std::abs(to.second - from.second);

        if (colDiff == 1 && !target)
            throw InvalidMove("Pawn diagonal move requires capture");

        if (colDiff == 0 && target)
            throw InvalidMove("Pawn cannot capture forward");
    }

    // Collision check (except knight)
    if (!dynamic_cast<Knight*>(moving) && checkCollision(from, to))
        throw InvalidMove("Path blocked");

    // Pin / king safety check
    checkPin(from, to);

    saveUndoState();

    // Move the piece
    squares[to.first][to.second] = moving;
    squares[from.first][from.second] = nullptr;

    // Update movement flags
    if (Rook* rook = dynamic_cast<Rook*>(moving)) {
        rook->setHasRookMoved(true);
    }
    else if (Pawn* pawn = dynamic_cast<Pawn*>(moving)) {
        pawn->setHasPawnMoved(true);
    }
    else if (King* king = dynamic_cast<King*>(moving)) {
        king->setHasKingMoved(true);
    }

    // En Passant and Promotion
    resetAllEnPassantEligibility();

    if (Pawn* pawn = dynamic_cast<Pawn*>(moving)) {

        int startRow = pawn->getIsWhite() ? 6 : 1;
        int diff = std::abs(from.first - to.first);

        if (from.first == startRow && diff == 2) {
            pawn->setEnPassantEligible(true);
        }

        promotion(to, promotionChoice);
    }

    // Endgame checks
    bool opponentIsWhite = !moving->getIsWhite();

    if (checkMate(opponentIsWhite)) {
        return CHECKMATE;
    }
    else if (checkStalemate(opponentIsWhite)) {
        return STALEMATE;
    }
    else if (checkCheck(opponentIsWhite)) {
        return CHECK;
    }

    return NORMAL;
}

bool Board::isLegalMove(Coordinates from, Coordinates to, bool isWhiteTurn, char promotionChoice) {
    verifyCoordinates(from);
    verifyCoordinates(to);
    
    try {
        makeMove(from, to, isWhiteTurn, promotionChoice);
        undoMove();
        return true;
    } catch (const InvalidMove&) {
        if(undoAvailable) undoMove();
        return false;
    }
}

bool Board::hasValidMoves(bool isKingWhite) {
    for(int fromFst = 0; fromFst < BOARD_SIZE; fromFst++) {
        for(int fromSnd = 0; fromSnd < BOARD_SIZE; fromSnd++) {
            Piece* p = squares[fromFst][fromSnd];

            if(p == nullptr || p->getIsWhite() != isKingWhite)
                continue;

            Coordinates from;
            from.first = fromFst;
            from.second = fromSnd;
            for(int toFst = 0; toFst < BOARD_SIZE; toFst++) {
                for(int toSnd = 0; toSnd < BOARD_SIZE; toSnd++) {
                    if(fromFst == toFst && fromSnd == toSnd)
                        continue;

                    Coordinates to;
                    to.first = toFst;
                    to.second = toSnd;

                    if(!p->regularMovement(from, to))
                        continue;

                    Piece* target = squares[toFst][toSnd];

                    if(target != nullptr && target->getIsWhite() == isKingWhite)
                        continue;

                    if(dynamic_cast<Pawn*>(p) != nullptr) {
                        int colDiff = abs(toSnd - fromSnd);

                        if (colDiff == 1 && target == nullptr)
                            continue;

                        if (colDiff == 0 && target != nullptr)
                            continue;
                    }

                    if(!dynamic_cast<Knight*>(p) && checkCollision(from, to))
                        continue;

                    squares[toFst][toSnd] = p;
                    squares[fromFst][fromSnd] = nullptr;

                    bool kingInCheck = checkCheck(isKingWhite);

                    squares[fromFst][fromSnd] = p;
                    squares[toFst][toSnd] = target;

                    if(!kingInCheck) return true;
                }
            }
        }
    }
    return false;
}

bool Board::checkStalemate(bool isKingWhite) {
    return (!hasValidMoves(isKingWhite) && !checkCheck(isKingWhite));
}

bool Board::checkMate(bool isKingWhite) {
    return (!hasValidMoves(isKingWhite) && checkCheck(isKingWhite));
}

bool Board::checkCastle(Coordinates from, Coordinates to) {
    King* king = dynamic_cast<King*>(getPiece(from));
    if (!king) return false;

    if (king->getHasKingMoved()) return false;

    int row = from.first;
    int diff = (int)to.second - (int)from.second;

    if (std::abs(diff) != 2) return false;

    if (checkCheck(king->getIsWhite()))
        throw InvalidMove("King in check");

    int rookCol = diff > 0 ? 7 : 0;
    int step = diff > 0 ? 1 : -1;

    Rook* rook = dynamic_cast<Rook*>(squares[row][rookCol]);
    if (!rook || rook->getHasRookMoved())
        throw InvalidMove("Invalid rook");

    for (int c = from.second + step; c != rookCol; c += step) {
        if (squares[row][c] != nullptr)
            throw InvalidMove("Piece between king and rook");
    }

    for (int i = 1; i <= 2; i++) {
        Coordinates temp = { (usint)row, (usint)(from.second + step * i) };
        Piece* saved = squares[row][temp.second];

        squares[row][temp.second] = king;
        squares[from.first][from.second] = nullptr;

        bool inCheck = checkCheck(king->getIsWhite());

        squares[from.first][from.second] = king;
        squares[row][temp.second] = saved;

        if (inCheck)
            throw InvalidMove("Castling through check");
    }

    return true;
}

void Board::castle(Coordinates from, Coordinates to) {
    King* king = static_cast<King*>(getPiece(from));

    int row = from.first;
    int diff = (int)to.second - (int)from.second;

    int rookFrom = diff > 0 ? 7 : 0;
    int rookTo = diff > 0 ? to.second - 1 : to.second + 1;

    Rook* rook = static_cast<Rook*>(squares[row][rookFrom]);

    squares[row][to.second] = king;
    squares[from.first][from.second] = nullptr;

    squares[row][rookTo] = rook;
    squares[row][rookFrom] = nullptr;

    king->setHasKingMoved(true);
    rook->setHasRookMoved(true);
}