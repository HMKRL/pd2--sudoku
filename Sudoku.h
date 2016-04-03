#ifndef SUDOKU_H
#define SUDOKU_H

struct ch {
	int x;
	int y;
	int num;
	int chance;
};

class Sudoku {
public:
	Sudoku();
	Sudoku(Sudoku &S);
	void giveQuestion();
	void readIn();
	void solve();
	void changeNum(int, int);
	void changeRow(int, int);
	void changeCol(int, int);
	void rotate(int);
	void flip(int);
	void transform();
private:
	ch getMinimumchance();
	bool setUsed(int, int, int);
	void printOut(bool);
	int Backtracking(); //return 0(No sol), 1(unique sol), 2(multi sol)
	int Map[9][9];
	int pNum[9][9];
	bool possible[9][9][9];
};

#endif
