#include <iostream>
#include <vector>
#include <chrono>
#include "puzzle.h"
#include "combinations.h"
#include "solver.h"

using namespace std;

void test1(CombinationGenerator &combination_generator) {
    KakuroPuzzle puzzle(10, 10);

    for (int i = 0; i < 10; ++i) {
        puzzle.set_black_cell(0, i);
    }

    puzzle.set_black_cell(1, 0);
    puzzle.set_black_cell(1, 7);

    puzzle.set_black_cell(2, 0);
    puzzle.set_black_cell(2, 7);

    puzzle.set_black_cell(3, 0);
    puzzle.set_black_cell(3, 4);

    puzzle.set_black_cell(4, 0);
    puzzle.set_black_cell(4, 3);

    puzzle.set_black_cell(5, 0);
    puzzle.set_black_cell(5, 1);
    puzzle.set_black_cell(5, 2);
    puzzle.set_black_cell(5, 5);
    puzzle.set_black_cell(5, 8);
    puzzle.set_black_cell(5, 9);

    puzzle.set_black_cell(6, 0);
    puzzle.set_black_cell(6, 7);

    puzzle.set_black_cell(7, 0);
    puzzle.set_black_cell(7, 6);

    puzzle.set_black_cell(8, 0);
    puzzle.set_black_cell(8, 3);

    puzzle.set_black_cell(9, 0);
    puzzle.set_black_cell(9, 3);

    vector<vector<int>> horizontal_sum = {
        {},
        {39, 3},
        {23, 9},
        {24, 29},
        {17, 23},
        {4,  17},
        {39, 13},
        {26, 23},
        {11, 27},
        {3, 23}
    };

    vector<vector<int>> vertical_sums = {
        {},
        {23, 10},
        {28, 22},
        {22, 17},
        {5, 21},
        {28, 28},
        {28, 5},
        {22, 22},
        {10, 23},
        {26, 13}
    };

    puzzle.build_blocks(horizontal_sum, vertical_sums, combination_generator);

    KakuroSolver solver(puzzle);

    if (solver.solve()) {
        puzzle.print_grid();
    } else {
        cout << "No solution found." << endl;
    }

}

void test2(CombinationGenerator &combination_generator) {
    KakuroPuzzle puzzle(7, 7);

    for (int i = 0; i < 7; ++i) {
        puzzle.set_black_cell(0, i);
    }

    puzzle.set_black_cell(1, 0);
    puzzle.set_black_cell(1, 1);
    puzzle.set_black_cell(1, 2);
    puzzle.set_black_cell(1, 5);
    puzzle.set_black_cell(1, 6);

    puzzle.set_black_cell(2, 0);
    puzzle.set_black_cell(2, 1);

    puzzle.set_black_cell(3, 0);
    puzzle.set_black_cell(3, 3);
    puzzle.set_black_cell(3, 4);

    puzzle.set_black_cell(4, 0);
    puzzle.set_black_cell(4, 6);

    puzzle.set_black_cell(5, 0);
    puzzle.set_black_cell(5, 1);

    puzzle.set_black_cell(6, 0);
    puzzle.set_black_cell(6, 1);

    vector<vector<int>> horizontal_sum = {
        {},
        {15},
        {26},
        {12, 7},
        {27},
        {34},
        {26},
    };

    vector<vector<int>> vertical_sums = {
        {},
        {16},
        {35},
        {7, 9},
        {16, 19},
        {35},
        {4, 6},
    };

    puzzle.build_blocks(horizontal_sum, vertical_sums, combination_generator);

    KakuroSolver solver(puzzle);

    if (solver.solve()) {
        puzzle.print_grid();
    } else {
        cout << "No solution found." << endl;
    }
}

void test3(CombinationGenerator &combination_generator) {
    KakuroPuzzle puzzle(10, 10);

    for (int i = 0; i < 10; ++i) {
        puzzle.set_black_cell(0, i);
    }

    puzzle.set_black_cell(1, 0);
    puzzle.set_black_cell(1, 4);
    puzzle.set_black_cell(1, 5);
    puzzle.set_black_cell(1, 9);

    puzzle.set_black_cell(2, 0);
    puzzle.set_black_cell(2, 4);

    puzzle.set_black_cell(3, 0);
    puzzle.set_black_cell(3, 1);
    puzzle.set_black_cell(3, 6);

    puzzle.set_black_cell(4, 0);
    puzzle.set_black_cell(4, 1);
    puzzle.set_black_cell(4, 2);
    puzzle.set_black_cell(4, 6);
    puzzle.set_black_cell(4, 7);

    puzzle.set_black_cell(5, 0);

    puzzle.set_black_cell(6, 0);
    puzzle.set_black_cell(6, 3);
    puzzle.set_black_cell(6, 4);
    puzzle.set_black_cell(6, 8);
    puzzle.set_black_cell(6, 9);

    puzzle.set_black_cell(7, 0);
    puzzle.set_black_cell(7, 4);
    puzzle.set_black_cell(7, 9);

    puzzle.set_black_cell(8, 0);
    puzzle.set_black_cell(8, 6);

    puzzle.set_black_cell(9, 0);
    puzzle.set_black_cell(9, 1);
    puzzle.set_black_cell(9, 5);
    puzzle.set_black_cell(9, 6);

    vector<vector<int>> horizontal_sum = {
        {},
        {21, 11},
        {11, 29},
        {27, 8},
        {21, 15},
        {45},
        {8, 13},
        {20, 12},
        {29, 11},
        {12, 22}
    };

    vector<vector<int>> vertical_sums = {
        {},
        {17, 11},
        {15, 34},
        {32, 10},
        {21, 16},
        {28},
        {16, 21},
        {7, 17},
        {16, 9},
        {29, 16}
    };

    puzzle.build_blocks(horizontal_sum, vertical_sums, combination_generator);

    KakuroSolver solver(puzzle);

    if (solver.solve()) {
        puzzle.print_grid();
    } else {
        cout << "No solution found." << endl;
    }

}

int main() {
    CombinationGenerator combination_generator;
    
    cout << "Test 1:" << endl;
    auto start = chrono::high_resolution_clock::now();
    test1(combination_generator);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << " seconds" << endl << endl;

    cout << "Test 2:" << endl;
    start = chrono::high_resolution_clock::now();
    test2(combination_generator);
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << " seconds" << endl << endl;

    cout << "Test 3:" << endl;
    start = chrono::high_resolution_clock::now();
    test3(combination_generator);
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << " seconds" << endl << endl;

    return 0;
}