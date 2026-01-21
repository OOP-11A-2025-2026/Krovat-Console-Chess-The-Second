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

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) 

test_bishop:
	$(CXX) $(CXXFLAGS) \
	tests/test_bishop.cpp \
	src/Piece.cpp \
	src/Bishop.cpp \
	-o test_bishop

clean:
	rm -f $(TARGET)