#include "pch.h"

//class function and initiation
puzzle::puzzle()
{
	file = "puzzle";
	createVar();
	init();
}
puzzle::puzzle(string theFile)
{
	string x;
	file = theFile;
	createVar();

	
	init();
}
void puzzle::createVar()
{
	pass = true;
	//size sudoku puzzle
	sudoku = new int*[P_SIZE];
	for (int i = 0; i < P_SIZE; i++)
	{
		sudoku[i] = new int[P_SIZE];
	}
	fix = new int*[P_SIZE];
	for (int j = 0; j < P_SIZE; j++)
	{
		fix[j] = new int[P_SIZE];
	}
	solve = new int*[P_SIZE];
	for (int m = 0; m < P_SIZE; m++)
	{
		solve[m] = new int[P_SIZE];
	}
}
void puzzle::init()
{
	readPuzzle();
	out << "Original Puzzle" << endl;
	print(sudoku);
	//thread creation
	thread verT = thread(&puzzle::Vertical, this);
	thread horT = thread(&puzzle::Horizontal, this);
	thread gridT = thread(&puzzle::Grid, this);
	verT.join();
	horT.join();
	gridT.join();

	thread solveT = thread(&puzzle::Solve, this);
	solveT.join();

}


//threads
void puzzle::Vertical() //check vertical for match
{
	ver(sudoku); //call function
}
void puzzle::Horizontal() //check horizontal for match
{
	hor(sudoku); //call function
}
void puzzle::Grid() //check horizontal for match
{
	//smaller 2d array
	//size sudoku puzzle
	int j, k; //iterate which 3x3 matrix unit 
	int x, y; //iterate within 3x3 matrix unit
	int count = 1; //determine which 3x3 unit we are checking

	for (j = 0; j < G_SIZE; j++)
	{
		for (k = 0; k < G_SIZE; k++)
		{
			int** matrix = new int*[G_SIZE]; //create separate arrays to be checked
			for (int i = 0; i < G_SIZE; i++)
			{
				matrix[i] = new int[G_SIZE];
			}
			for (x = 0; x < G_SIZE; x++)
			{
				for (y = 0; y < G_SIZE; y++)
				{
					matrix[x][y] = sudoku[x + j * 3][y + k * 3];
				}
			}
			int** temp = new int*[G_SIZE]; //create separate arrays to be checked
			for (int i = 0; i < G_SIZE; i++)
			{
				temp[i] = new int[G_SIZE];
			}
			temp = grid(matrix); //call function
			for (x = 0; x < G_SIZE; x++)
			{
				for (y = 0; y < G_SIZE; y++)
				{
					if (matrix[x][y] != temp[x][y])
					{
						pass = false;
						fix[x + j * 3][y + k * 3] = 0;
						solve[x + j * 3][y + k * 3] = 0;
					}
				}
			}
			count++;
		}

	}
}

//functions used by threads
void puzzle::hor(int** map)
{
	int x, y;
	int val1 = 0;
	int val2 = 0;
	int count = 0;
	int row = 0;
	for (row = 0; row < P_SIZE; row++)
	{
		for (x = 0; x < P_SIZE; x++)
		{
			for (y = 0; y < P_SIZE; y++)
			{
				val1 = map[row][y];
				val2 = map[x][y]; //compare values
				if ((val1 == val2) && (x != row))
				{
					pass = false;
					fix[x][y] = 0;
					solve[x][y] = 0;
				}
			}
		}
	}
}
void puzzle::ver(int** map)
{
	int x, y;
	int val1 = 0;
	int val2 = 0;
	int count = 0;
	int col = 0;
	for (col = 0; col < P_SIZE; col++)
	{

		for (x = 0; x < P_SIZE; x++)
		{
			for (y = 0; y < P_SIZE; y++)
			{
				val1 = map[x][col];
				val2 = map[x][y]; //compare values
				if ((val1 == val2) && (y != col))
				{
					pass = false;
					fix[x][y] = 0;
					solve[x][y] = 0;
				}
			}
		}
	}
}
int** puzzle::grid(int** map)
{
	int num1 = 0;
	int num2 = 0;

	int x, y;
	int row, col;

	//create fix matrix as newMap
	int** newMap = new int*[G_SIZE];
	for (int i = 0; i < G_SIZE; i++)
	{
		newMap[i] = new int[G_SIZE];
	}

	for (row = 0; row < G_SIZE; row++)
	{
		for (col = 0; col < G_SIZE; col++)
		{
			newMap[row][col] = map[row][col]; //copy variables from map to newMap
			for (x = 0; x < G_SIZE; x++)
			{
				for (y = 0; y < G_SIZE; y++)
				{
					num1 = map[row][col];
					num2 = map[x][y];


					if ((num1 == num2) && ((x != row) | (y != col)))
					{
						newMap[x][y] = 0;
					}
				}
			}
		}

	}

	return newMap;
}

bool puzzle::solvePuzzle(int** map)
{
	if (isComplete(map))
	{
		out << "\nComplete Puzzle" << endl;
		print(map);
		return true;
	}

	int row, col, num;

	for (row = 0; row < P_SIZE; row++)
	{
		for (col = 0; col < P_SIZE; col++)
		{
			if (map[row][col] == 0) //check if empty space exists
			{
				for (num = 1; num <= 9; num++) //attempt all possible options
				{
					//check if number exists in row, column, and grid
					if ((checkRow(map, row, num)) && (checkCol(map, col, num)) && (checkGrid(map, row - row % 3, col - col % 3, num)))
					{
						map[row][col] = num;
						if (solvePuzzle(map)) //recursively solve each empty space with brute force
							return true;
						else
							map[row][col] = 0; //attempt another solution
					}
				}
			}
		}
	}
	return false; //unfinished puzzle
}
bool puzzle::checkRow(int** map, int row, int num1)
{
	int num2;
	int x;
	for (x = 0; x < P_SIZE; x++)
	{
		num2 = map[row][x];
		if (num1 == num2) //comparison
		{
			return false; //the number exists //fail
		}
	}
	return true;//pass
}
bool puzzle::checkCol(int** map, int col, int num1)
{
	int num2;
	int x;
	for (x = 0; x < P_SIZE; x++)
	{
		num2 = map[x][col];
		if (num1 == num2) //comparison
		{
			return false; //the number exists //fail
		}
	}
	return true; //pass
}
bool puzzle::checkGrid(int** map, int row, int col, int num1)
{
	int x, y;
	int num2;
	for (x = 0; x < G_SIZE; x++)
	{
		for (y = 0; y < G_SIZE; y++)
		{
			num2 = map[x + row][y + col];
			if (num1 == num2) //compare
			{
				return false; //the number exists // fail 
			}
		}
	}
	return true; //pass
}

bool puzzle::isComplete(int** map)
{//check if puzzle is solved
	int i, j;

	for (i = 0; i < P_SIZE; i++)
	{
		for (j = 0; j < P_SIZE; j++)
		{
			if (map[i][j] == 0) //0 is empty spot
			{
				return false; //unfinished
			}
		}
	}
	return true;
}
queue<string> puzzle::findSol()
{//create error log with corrections
	int i, j;

	for (i = 0; i < P_SIZE; i++)
	{
		for (j = 0; j < P_SIZE; j++)
		{
			if (fix[i][j] == 0) //deleted space
			{
				if ((solve[i][j] != sudoku[i][j])) //corrected answer
				{
					errorLog.push("Row " + to_string(i + 1) + " Col " + to_string(j + 1) + " :: " + to_string(sudoku[i][j]) + " --> " + to_string(solve[i][j]));
				}
			}
		}
	}
	if (errorLog.empty())
		errorLog.push("Correct!"); //the puzzle is viable!
	return errorLog;
}
void puzzle::Solve()
{
	if (pass == false)
		solvePuzzle(solve);
	errorLog = findSol();
	out << "\n";
	while (!errorLog.empty())
	{
		out << errorLog.front() << endl;
		errorLog.pop();
	}
	out.close(); //close writer
}

void puzzle::print(int** map)
{
	for (int x = 0; x < P_SIZE; x++)
	{
		for (int y = 0; y < P_SIZE; y++)
		{

			out << map[x][y];
		}
		out << "\n";
	}
}

void puzzle::readPuzzle()
{
	//make 2D array global variable
	ifstream reader;
	string text = ".txt";
	string output = ".out";
	reader.open(file + text); //open reader
	if (reader)
	{
		
		string nextLine;
		int counter = 0;
		char temp;
		int num;
		while (getline(reader, nextLine))
		{
			if ((nextLine.length() != 18) && (nextLine.length() != 17))
			{
				exitSequence();
			}
			for (int x = 0; x < 18; x++) //9 digits, 9 commas
			{
				temp = nextLine[x];
				if (temp != ',')
				{
					num = int(temp) - 48; //ASCII numbers start from 48
					sudoku[counter][(x + 1) / 2] = num; //(x+1)/2 reprisents the index of each digit, taking into account commas
					fix[counter][(x + 1) / 2] = num;
					solve[counter][(x + 1) / 2] = num;
				}
			}
			counter++;
		}
		out.open(file + output); //open writer
		out << file << "\n";
	}
	else
	{
		exitSequence();
	}
	
}
void puzzle::exitSequence()
{
	cout << "Invalid File Input\n";
	system("PAUSE");
	exit(0);
}

//getters
int** puzzle::getSudoku()
{
	return sudoku;
}
int** puzzle::getFix()
{
	return fix;
}
int** puzzle::getSolve()
{
	return solve;
}
queue<string> puzzle::getErrorLog()
{
	return errorLog;
}
string puzzle::getFile()
{
	return file;
}
bool puzzle::getPass()
{
	return pass;
}
