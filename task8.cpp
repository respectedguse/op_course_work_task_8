#include <iostream>
#include <vector>
#include "puzzle.h"
#include "combinations.h"
#include "solver.h"

using namespace std;

int main() {
    CombinationGenerator combination_generator;
    KakuroPuzzle puzzle(10, 10);

    for (int i = 0; i < 10; ++i) {
        puzzle.set_black_cell(0, i);
    }

    puzzle.set_black_cell(1, 0);
    puzzle.set_black_cell(1, 3);
    puzzle.set_black_cell(1, 6);

    puzzle.set_black_cell(2, 0);
    puzzle.set_black_cell(2, 6);

    puzzle.set_black_cell(3, 0);
    puzzle.set_black_cell(3, 4);

    puzzle.set_black_cell(4, 0);
    puzzle.set_black_cell(4, 1);
    puzzle.set_black_cell(4, 2);
    puzzle.set_black_cell(4, 7);

    puzzle.set_black_cell(5, 0);
    puzzle.set_black_cell(5, 5);

    puzzle.set_black_cell(6, 0);
    puzzle.set_black_cell(6, 3);
    puzzle.set_black_cell(6, 8);
    puzzle.set_black_cell(6, 9);

    puzzle.set_black_cell(7, 0);
    puzzle.set_black_cell(7, 6);

    puzzle.set_black_cell(8, 0);
    puzzle.set_black_cell(8, 4);

    puzzle.set_black_cell(9, 0);
    puzzle.set_black_cell(9, 4);
    puzzle.set_black_cell(9, 7);

    vector<vector<int>> horizontal_sum = {
        {},
        {15, 7, 23},
        {33, 24},
        {21, 21},
        {13, 16},
        {14, 16},
        {12, 10},
        {34, 10},
        {21, 32},
        {9, 17, 11}
    };

    vector<vector<int>> vertical_sums = {
        {},
        {23, 33},
        {13, 15},
        {19, 16},
        {15, 26},
        {21, 28},
        {10, 16},
        {17, 27},
        {32, 7},
        {26, 15}
    };

    puzzle.build_blocks(horizontal_sum, vertical_sums, combination_generator);

    KakuroSolver solver(puzzle);

    if (solver.solve()) {
        puzzle.print_grid();
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}