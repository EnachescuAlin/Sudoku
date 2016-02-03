CFLAGS = -std=c++11 -Wall -c
INCLUDE = -Iinclude `wx-config --cxxflags`
OBJ = bin/board.o bin/sudoku.o bin/main.o bin/configpane.o bin/gamepane.o \
      bin/mainpane.o bin/loadpane.o bin/frame.o bin/highscorepane.o

all: board.o sudoku.o main.o configpane.o gamepane.o mainpane.o loadpane.o \
     frame.o highscorepane.o sudoku

board.o: src/board.cpp
	mkdir -p bin
	g++ $(CFLAGS) -o bin/board.o src/board.cpp $(INCLUDE)

sudoku.o: src/sudoku.cpp
	g++ $(CFLAGS) -o bin/sudoku.o src/sudoku.cpp $(INCLUDE)

main.o: src/main.cpp
	g++ $(CFLAGS) -o bin/main.o src/main.cpp $(INCLUDE)

configpane.o: src/configpane.cpp
	g++ $(CFLAGS) -o bin/configpane.o src/configpane.cpp $(INCLUDE)

gamepane.o: src/gamepane.cpp
	g++ $(CFLAGS) -o bin/gamepane.o src/gamepane.cpp $(INCLUDE)

mainpane.o: src/mainpane.cpp
	g++ $(CFLAGS) -o bin/mainpane.o src/mainpane.cpp $(INCLUDE)

loadpane.o: src/loadpane.cpp
	g++ $(CFLAGS) -o bin/loadpane.o src/loadpane.cpp $(INCLUDE)

frame.o: src/frame.cpp
	g++ $(CFLAGS) -o bin/frame.o src/frame.cpp $(INCLUDE)

highscorepane.o: src/highscorepane.cpp
	g++ $(CFLAGS) -o bin/highscorepane.o src/highscorepane.cpp $(INCLUDE)

sudoku: $(OBJ)
	g++ -std=c++11 -Wall -o sudoku $(OBJ) $(INCLUDE) `wx-config --libs`

clean:
	rm sudoku
	rm -r bin
