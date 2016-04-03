SOURCE=Sudoku.h Sudoku.cpp giveQuestion.cpp solve.cpp transform.cpp
OBJECT=Sudoku.o Sudoku.h
CXXFLAGS=-g -Wall -std=c++0x -pg
CXX=g++
EXECUTABLE=giveQuestion solve transform

all:$(SOURCE) $(EXECUTABLE)

solve:solve.o $(OBJECT)
	$(CXX) -o solve $(CXXFLAGS) solve.o Sudoku.o

giveQuestion:giveQuestion.o $(OBJECT)
	$(CXX) -o giveQuestion $(CXXFLAGS) giveQuestion.o Sudoku.o

transform:transform.o $(OBJECT)
	$(CXX) -o transform $(CXXFLAGS) transform.o Sudoku.o

%.o:%.cpp
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm *.o $(EXECUTABLE)
