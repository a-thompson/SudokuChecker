// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <queue>
using namespace std;
class puzzle {
public:
	puzzle();
	puzzle(string theFile);
	void init();

	int** getSudoku();
	int** getFix();
	int** getSolve();
	queue<string> getErrorLog();
	string getFile();
	bool getPass();
private:
	int** sudoku; //save all error locations; any coordinates listed 2x is changed to 0
	int** fix;
	int** solve;
	queue<string> errorLog;
	string file;
	bool pass;
	ofstream out;

	int P_SIZE = 9; //puzzle size
	int G_SIZE = 3; //grid size

	void Vertical();
	void Horizontal();
	void Grid();
	void Solve();

	void hor(int** map);
	void ver(int** map);
	int** grid(int** map);

	bool checkRow(int** map, int row, int num1);
	bool checkCol(int** map, int col, int num1);
	bool checkGrid(int** map, int row, int col, int num1);
	bool isComplete(int** map);

	bool solvePuzzle(int** map);
	void exitSequence();
	queue<string> findSol();

	void createVar();
	void print(int** map);
	void readPuzzle();
};
// TODO: add headers that you want to pre-compile here

#endif //PCH_H

