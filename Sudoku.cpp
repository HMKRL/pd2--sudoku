#include"Sudoku.h"
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

int Ans[9][9] = {{0}};

Sudoku::Sudoku() {
	fill(pNum[0], pNum[0] + 81, 9);
	fill(Map[0], Map[0] + 81, 0);
	fill(possible[0][0], possible[0][0] + 729, true);
};

Sudoku::Sudoku(Sudoku &S) {
	*this = S;
};

void Sudoku::giveQuestion() {
	int arr[9][9] = {
		{0, 0, 0, 0, 5, 0, 0, 9, 0},
		{4, 0, 0, 0, 0, 0, 0, 0, 2},
		{0, 0, 6, 7, 0, 0, 0, 0, 0},
		{2, 0, 0, 0, 0, 0, 0, 0, 0},
		{9, 5, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 6, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 3},
		{0, 8, 0, 0, 0, 0, 7, 0, 6},
		{0, 0, 0, 0, 1, 3, 0, 0, 0},
	};
	copy(arr[0], arr[0] + 81, Map[0]);
	transform();
};

void Sudoku::readIn() {
	for(int i = 0;i < 9;++i) {
		for(int j = 0;j < 9;++j) {
			scanf("%d", &Map[i][j]);
		}
	}
};

void Sudoku::solve() {
	for(int i = 0;i < 9;++i) {
		for(int j = 0;j < 9;++j) {
			if(Map[i][j]) {
				if(!setUsed(i, j, Map[i][j])) {
					puts("0");
					return;
				}
			}
		}
	}
	int solved = Backtracking();
	if(solved == 0) printf("%d\n", 0);
	else if(solved == 1) {
		printf("%d\n", 1);
		printOut(true);
	}
	else printf("%d\n", 2);
	return;
};

void Sudoku::changeNum(int a, int b) {
	for(int i = 0;i < 9;++i) {
		for(int j = 0;j < 9;++j) {
			if(Map[i][j] == a) Map[i][j] = b;
			else if(Map[i][j] == b) Map[i][j] = a;
		}
	}
};

void Sudoku::changeRow(int a, int b) {
	int temp;
	if(a == b) return;
	int adjust = 3 * (b - a);
	for(int i = a * 3;i < a * 3 + 3;++i) {
		for(int j = 0;j < 9;++j) {
			temp = Map[i][j];
			Map[i][j] = Map[i + adjust][j];
			Map[i + adjust][j] = temp;
		}
	}
};

void Sudoku::changeCol(int a, int b) {
	int temp;
	if(a == b) return;
	int adjust = 3 * (b - a);
	for(int i = 0;i < 9;++i) {
		for(int j = a * 3;j < a * 3 + 3;++j) {
			temp = Map[i][j];
			Map[i][j] = Map[i][j + adjust];
			Map[i][j + adjust] = temp;
		}
	}
};

void Sudoku::rotate(int n) {
	if(n == 0) return;
	else if(n > 3) n %= 4;
	
	int temp[9][9];
	copy(Map[0], Map[0] + 81, temp[0]);
	switch(n) {
		case 1:
			for(int i = 0;i < 9;++i) {
				for(int j = 0;j < 9;++j) {
					Map[i][j] = temp[8 - j][i];
				}
			}
			break;
		case 2:
			for(int i = 0;i < 9;++i) {
				for(int j = 0;j < 9;++j) {
					Map[i][j] = temp[8 - i][8 - j];
				}
			}
			break;
		case 3:
			for(int i = 0;i < 9;++i) {
				for(int j = 0;j < 9;++j) {
					Map[i][j] = temp[j][8 - i];
				}
			}
			break;
		default:
			break;
	}
};

void Sudoku::flip(int n) {
	int temp;
	if(n) {
		for(int i = 0;i < 9;++i) {
			for(int j = 0;j < 4;++j) {
				temp = Map[i][j];
				Map[i][j] = Map[i][8 - j];
				Map[i][8 - j] = temp;
			}
		}
	}
	else {
		for(int i = 0;i < 4;++i) {
			for(int j = 0;j < 9;++j) {
				temp = Map[i][j];
				Map[i][j] = Map[8 - i][j];
				Map[8 - i][j] = temp;
			}
		}
	}
};

void Sudoku::transform() {
	srand(time(NULL));
	changeNum(rand() % 9 + 1,rand() % 9 + 1);
	rotate(rand() % 101);
	changeCol(rand() % 3, rand() % 3);
	changeRow(rand() % 3, rand() % 3);
	printOut(false);
};

bool Sudoku::setUsed(int row, int col, int val) {
	int adjrow = (row / 3) * 3, adjcol = (col / 3) * 3;
	int index = val - 1;
	bool not_conflict = true;
	if(!possible[row][col][index]) not_conflict = false; //No solution!! Map conflicts;
	pNum[row][col] = -1;
	possible[row][col][index] = false;
	for(int i = 0;i < 9;++i) {
			if(possible[row][i][index]) {
				possible[row][i][index] = false;
				--pNum[row][i];
			}
			if(possible[i][col][index]) {
				possible[i][col][index] = false;
				--pNum[i][col];
			}
	}
	for(int i = 0;i < 3;++i) {
		for(int j = 0;j < 3;++j) {
			int R = i + adjrow;
			int C = j + adjcol;
				if(possible[R][C][index]) {
					possible[R][C][index] = false;
					--pNum[R][C];
				}
		}
	}
	/*
	possible[row][0][index] = false;
	possible[0][col][index] = false;
	possible[row][1][index] = false;
	possible[1][col][index] = false;
	possible[row][2][index] = false;
	possible[2][col][index] = false;
	possible[row][3][index] = false;
	possible[3][col][index] = false;
	possible[row][4][index] = false;
	possible[4][col][index] = false;
	possible[row][5][index] = false;
	possible[5][col][index] = false;
	possible[row][6][index] = false;
	possible[6][col][index] = false;
	possible[row][7][index] = false;
	possible[7][col][index] = false;
	possible[row][8][index] = false;
	possible[8][col][index] = false;
	
	possible[0 + adjrow][0 + adjcol][index] = false;
	possible[0 + adjrow][1 + adjcol][index] = false;
	possible[0 + adjrow][2 + adjcol][index] = false;
	possible[1 + adjrow][0 + adjcol][index] = false;
	possible[1 + adjrow][1 + adjcol][index] = false;
	possible[1 + adjrow][2 + adjcol][index] = false;
	possible[2 + adjrow][0 + adjcol][index] = false;
	possible[2 + adjrow][1 + adjcol][index] = false;
	possible[2 + adjrow][2 + adjcol][index] = false;
	*/
	return not_conflict;
};

void Sudoku::printOut(bool ans) {
	
	for(int i = 0;i < 9;++i) {
		for(int j = 0;j < 9;++j) {
			if(j) printf("%c", ' ');
			if(ans) printf("%d", Ans[i][j]);
			else printf("%d", Map[i][j]);
		}
		puts("");
	}
};

int Sudoku::Backtracking() {
	ch P = getMinimumchance();
	if(P.chance == 10) {
		if(Ans[0][0] == 0) copy(Map[0], Map[0] + 81, Ans[0]);
		return 1; //solved
	}
	else if(P.chance == 0) {
		return 0; //No soluion
	}
	else if (P.chance == 1) { //only my possible answer
		setUsed(P.x, P.y, P.num + 1);
		Map[P.x][P.y] = P.num + 1;
		return Backtracking();
	}
	else {
		Sudoku Next(*this);
		Next.setUsed(P.x, P.y, P.num + 1);
		Next.Map[P.x][P.y] = P.num + 1;
		int result = Next.Backtracking();
		if(result == 0) { //current try has no solution
			possible[P.x][P.y][P.num] = false;
			--pNum[P.x][P.y];
			return Backtracking();
		}
		else if(result == 1) {
			Sudoku M_test(*this);
			M_test.possible[P.x][P.y][P.num] = false;
			--M_test.pNum[P.x][P.y];
			int M_result = M_test.Backtracking();
			return M_result == 0 ? 1 : 2;
		}
		else return 2;
	}
};

ch Sudoku::getMinimumchance() {
	ch out{-1, -1, -1, 10};
	for(int i = 0;i < 9;++i) {
		for(int j = 0;j < 9;++j) {
			if(pNum[i][j] >= 0 && pNum[i][j] < out.chance) {
				out.x = i;
				out.y = j;
				out.chance = pNum[i][j];
/*				if(possible[i][j][0]) {
					temp = 0;
					++count;
				}
				if(possible[i][j][1]) {
					temp = 1;
					++count;
				}
				if(possible[i][j][2]) {
					temp = 2;
					++count;
				}
				if(possible[i][j][3]) {
					temp = 3;
					++count;
				}
				if(possible[i][j][4]) {
					temp = 4;
					++count;
				}
				if(possible[i][j][5]) {
					temp = 5;
					++count;
				}
				if(possible[i][j][6]) {
					temp = 6;
					++count;
				}
				if(possible[i][j][7]) {
					temp = 7;
					++count;
				}
				if(possible[i][j][8]) {
					temp = 8;
					++count;
				}
*/					
//				if(count < out.chance) {
//					if(count < 2) return out;
//				}
			}
		}
	}
	if(out.chance < 10) {
		for(int k = 0;k < 9;++k) {
			if(possible[out.x][out.y][k]) {
				out.num = k;
				break;
			}
		}
	}
	return out;
}
