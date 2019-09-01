# Sudoku Checker

### Overview
*For a class project in CPSC 380 Operating Systems, I was told to use multithreading to validate sudoku puzzles.*
>The program will request a ".txt" file input.  Enter the filename (without the extension), and the result will be outputted as an ".out" file.

### Thread Description
>I used 4 threads for my project.  The main method in Sudoku.cpp asks for a file input and opens object puzzle from pch.h and pch.cpp.  The puzzle object initiates threads verT, horT, and gridT in the init() method, and simultaneously checks for three kinds of errors (vertical, horizontal, and grid).  In each thread, two variables are compared at a time, and if the variables are equal a copy of the puzzle will overwrite each variable with 0 to indicate an empty cell.  The init() method then initiates thread solveT which searches for a viable solution and creates an error log.  An output with the inputted file name is outputted as an .out file.  The program will inquire if you’d like to enter another file or exit.

>I used threads verT, horT, and gridT simultaneously to find errors quickly.  Thread solveT is not initiated until after all previous threads have started.  Each thread is able to access the global ofstream out to write an output file with the results.

#### Classes
* pch.h
* pch.cpp

#### Runner
* Sudoku.cpp

#### Test Files
* Test1.txt
* Test2.txt

#### Test Results
* Test1.out
* Test2.out
