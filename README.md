# Kakuro Solver

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Qt](https://img.shields.io/badge/Qt-6.11-green.svg)

## What is this?

A small application that solves **Kakuro puzzles**.  
You pick one of three built‑in puzzles, press “Solve”, and the program fills in the digits.  
The solving time is shown on the screen.



Kakuro is a math puzzle where you put digits 1‑9 into white cells.  
Each horizontal or vertical block has a sum written in a black cell.  
Digits inside a block must be with **no repeats**.

Example:
<img width="823" height="371" alt="Example puzzle and solution" src="https://github.com/user-attachments/assets/1b4fab10-4434-47fb-ae24-52c8aeb54ca9" />

## How the solver works

The solver uses a **backtracking** algorithm with a few optimisations:

- **Combination pre‑generation**  
  Before solving, it builds all possible digit sets for every sum (1‑45) and length (1‑9).  
  That way it never wastes time on impossible combinations.

- **Minimum remaining values**  
  At each step it picks the empty cell that has the fewest candidate digits.  
  This cuts down the search tree a lot.

- **Sum pruning**  
  While placing a digit, it checks whether the remaining sum can still be achieved with the remaining cells in the block.  
  If not, it backtracks immediately.

If a solution exists, the algorithm will find it. Otherwise it reports that the puzzle has no solution.

## Building the project

### Build Requirements:
- **C++17**
- **Qt 6.11**
- **CMake 3.16+**

1. Open the project.
2. Configure CMake to find Qt.
3. Build the `KakuroSolver` target.

The repository also contains a `KakuroTests` executable that runs unit tests on the core logic.

## Running the tests

```bash
./KakuroTests
```

## File task:

[Завдання №8.pdf](https://github.com/user-attachments/files/27163446/8.pdf)