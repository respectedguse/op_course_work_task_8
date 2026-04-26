# Kakuro Puzzle Solver

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Qt](https://img.shields.io/badge/Qt-6.11-green.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

## Project Overview

**Kakuro Puzzle Solver** is a C++ application designed to automatically solve **Kakuro** logic puzzles. 

The objective of Kakuro is to fill the empty white cells with digits from 1 to 9 so that the sum of the digits in each horizontal and vertical block matches the clue provided in the adjacent black cells. A crucial rule is that **digits cannot be repeated** within the same block.

**Example of a puzzle and its solution:**
![Kakuro Example](screenshots/example.png)

This application features a graphical user interface built with the **Qt framework**. It includes three built-in test cases ranging in difficulty, allowing users to load a puzzle and instantly compute and visualize the solution.

---

## Algorithm

The solver utilizes a highly optimized **Backtracking algorithm** enhanced with several techniques to avoid brute-force inefficiencies:

* **Combination Pre-generation:** Before solving begins, the program computes all valid digit combinations for every possible sum (1–45) and block length (1–9). This drastically reduces the search space by instantly discarding invalid digit sets.
* **Minimum Remaining Values Heuristic:** At each step, the algorithm prioritizes filling the cell that has the fewest valid candidate digits. This minimizes branching and speeds up the search process.
* **Sum Pruning:** The solver proactively checks if the remaining target sum can actually be achieved with the remaining empty cells in a block, pruning impossible paths early.

The algorithm is guaranteed to find a solution if one exists, or it will report that the puzzle is unsolvable.

---

## Build Requirements

* **C++ Standard:** C++17 or newer
* **Framework:** Qt 6.11
* **Build System:** CMake 3.16+
* **Compiler:** MinGW 64-bit

---