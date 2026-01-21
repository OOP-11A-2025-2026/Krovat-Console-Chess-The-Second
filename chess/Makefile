# Variable for compiler
CXX = g++

# Compiler flags
# -std=c++17 : Use C++17 standard
# -Wall : Enable all warnings
# -Iinclude : Include the 'include' directory for header files
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Name of the compiled exe
TARGET = chess

SRC = main.cpp \
    src/Board.cpp \
    src/Piece.cpp \
    src/Pawn.cpp \
	src/Rook.cpp \
    src/Knight.cpp \
    src/Bishop.cpp \
    src/Queen.cpp \
    src/King.cpp \
	src/Game.cpp 

TESTS = test_pawn \
	test_rook \
	test_queen \
	test_bishop \
	test_knight \
	test_king


all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) 

test_bishop:
	$(CXX) $(CXXFLAGS) \
	tests/test_bishop.cpp \
	src/Piece.cpp \
	src/Bishop.cpp \
	-o test_bishop

test_knight:
	$(CXX) $(CXXFLAGS) \
	tests/test_knight.cpp \
	src/Piece.cpp \
	src/Knight.cpp \
	-o test_knight

test_king:
	$(CXX) $(CXXFLAGS) \
	tests/test_king.cpp \
	src/Piece.cpp \
	src/King.cpp \
	-o test_king

test_pawn:
	$(CXX) $(CXXFLAGS) \
	tests/test_pawn.cpp \
	src/Piece.cpp \
	src/Pawn.cpp \
	-o test_pawn

test_rook:
	$(CXX) $(CXXFLAGS) \
	tests/test_rook.cpp \
	src/Piece.cpp \
	src/Rook.cpp \
	-o test_rook

test_queen:
	$(CXX) $(CXXFLAGS) \
	tests/test_queen.cpp \
	src/Piece.cpp \
	src/Queen.cpp \
	-o test_queen

test_board:
	$(CXX) $(CXXFLAGS) \
	tests/test_board.cpp \
	src/Board.cpp \
    src/Piece.cpp \
    src/Pawn.cpp \
	src/Rook.cpp \
    src/Knight.cpp \
    src/Bishop.cpp \
    src/Queen.cpp \
    src/King.cpp \
	-o test_board

clean:
	rm -f $(TARGET) $(TESTS)