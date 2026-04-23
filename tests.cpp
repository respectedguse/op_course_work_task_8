#include <iostream>
#include <cassert>
#include <vector>
#include "combinations.h"
#include "puzzle.h"
#include "solver.h"

using namespace std;

void test_min_max_sum() {
    cout << "test_min_max_sum... ";
    
    assert(CombinationGenerator::min_sum_for_len(1) == 1);
    assert(CombinationGenerator::min_sum_for_len(2) == 3);
    assert(CombinationGenerator::min_sum_for_len(3) == 6);
    assert(CombinationGenerator::min_sum_for_len(4) == 10);
    assert(CombinationGenerator::min_sum_for_len(5) == 15);
    assert(CombinationGenerator::min_sum_for_len(9) == 45);
    
    assert(CombinationGenerator::max_sum_for_len(1) == 9);
    assert(CombinationGenerator::max_sum_for_len(2) == 17);
    assert(CombinationGenerator::max_sum_for_len(3) == 24);
    assert(CombinationGenerator::max_sum_for_len(4) == 30);
    assert(CombinationGenerator::max_sum_for_len(5) == 35);
    assert(CombinationGenerator::max_sum_for_len(9) == 45);
    
    cout << "OK" << endl;
}

void test_combinations_generator() {
    cout << "test_combinations_generator... ";
    
    CombinationGenerator gen;
    
    auto combs = gen.get_combinations(5, 1);
    assert(combs.size() == 1);
    assert(combs[0].size() == 1);
    assert(combs[0][0] == 5);
    
    combs = gen.get_combinations(3, 2);
    assert(combs.size() == 1);
    assert(combs[0][0] == 1 && combs[0][1] == 2);
    
    combs = gen.get_combinations(4, 2);
    assert(combs.size() == 1);
    assert(combs[0][0] == 1 && combs[0][1] == 3);
    
    combs = gen.get_combinations(5, 2);
    assert(combs.size() == 2);
    
    combs = gen.get_combinations(6, 3);
    assert(combs.size() == 1);
    assert(combs[0][0] == 1 && combs[0][1] == 2 && combs[0][2] == 3);
    
    combs = gen.get_combinations(7, 3);
    assert(combs.size() == 1);
    assert(combs[0][0] == 1 && combs[0][1] == 2 && combs[0][2] == 4);
    
    combs = gen.get_combinations(10, 3);
    assert(combs.size() == 4);
    
    combs = gen.get_combinations(2, 2);  
    assert(combs.empty());
    combs = gen.get_combinations(18, 2);
    assert(combs.empty());
    combs = gen.get_combinations(50, 5);
    assert(combs.empty());
    
    cout << "OK" << endl;
}



void test_build_blocks() {
    cout << "test_build_blocks... ";
    
    CombinationGenerator gen;
    KakuroPuzzle puzzle(5, 5);
    
    for (int i = 0; i < 5; ++i) puzzle.set_black_cell(0, i);
    for (int i = 0; i < 5; ++i) puzzle.set_black_cell(i, 0);
    puzzle.set_black_cell(2, 2);
    for (int i = 0; i < 5; ++i) puzzle.set_black_cell(4, i);
    
    vector<vector<int>> hor_sums = {
        {}, {15}, {6, 7}, {20}, {}
    };
    
    vector<vector<int>> ver_sums = {
        {},        
        {10},      
        {8, 12},   
        {12},      
        {7}        
    };
    
    puzzle.build_blocks(hor_sums, ver_sums, gen);
    
    assert(puzzle.get_horizontal_blocks().size() == 4);
    assert(puzzle.get_vertical_blocks().size() == 5);
    
    const auto& hb = puzzle.get_horizontal_blocks();
    assert(hb[0].sum == 15);
    assert(hb[1].sum == 6);
    assert(hb[2].sum == 7);
    assert(hb[3].sum == 20);
    
    const auto& vb = puzzle.get_vertical_blocks();
    assert(vb[0].sum == 10);
    assert(vb[1].sum == 8);
    assert(vb[2].sum == 12);
    assert(vb[3].sum == 12);
    assert(vb[4].sum == 7);
    
    assert(puzzle.get_cell(1,1).index_horizontal_block == 0);
    assert(puzzle.get_cell(1,1).index_vertical_block == 0);
    
    assert(puzzle.get_cell(2,1).index_horizontal_block == 1);
    assert(puzzle.get_cell(2,1).index_vertical_block == 0);
    
    assert(puzzle.get_cell(3,1).index_horizontal_block == 3);
    assert(puzzle.get_cell(3,1).index_vertical_block == 0);
    
    assert(puzzle.get_cell(1,2).index_horizontal_block == 0);
    assert(puzzle.get_cell(1,2).index_vertical_block == 1);
    
    assert(puzzle.get_cell(3,2).index_horizontal_block == 3);
    assert(puzzle.get_cell(3,2).index_vertical_block == 2);
    
    assert(puzzle.get_cell(2,3).index_horizontal_block == 2);
    assert(puzzle.get_cell(2,3).index_vertical_block == 3);
    
    cout << "OK" << endl;
}



void test_solver_small() {
    cout << "test_solver_small... ";
    
    CombinationGenerator gen;
    KakuroPuzzle puzzle(3, 3);
    for (int i = 0; i < 3; ++i) puzzle.set_black_cell(0, i);
    for (int i = 0; i < 3; ++i) puzzle.set_black_cell(i, 0);
    puzzle.set_black_cell(1, 2);
    puzzle.set_black_cell(2, 1);
    puzzle.set_black_cell(2, 2);
    
    vector<vector<int>> hor_sums = {{}, {5}}; 
    vector<vector<int>> ver_sums = {{}, {5}}; 
    
    puzzle.build_blocks(hor_sums, ver_sums, gen);
    KakuroSolver solver(puzzle);
    
    assert(solver.solve());
    assert(puzzle.get_cell(1, 1).value == 5);
    
    cout << "OK" << endl;
}

void test_solver_impossible() {
    cout << "test_solver_impossible... ";
    
    cerr.setstate(ios::failbit);

    CombinationGenerator gen;
    KakuroPuzzle puzzle(3, 3);
    for (int i = 0; i < 3; ++i) puzzle.set_black_cell(0, i);
    for (int i = 0; i < 3; ++i) puzzle.set_black_cell(i, 0);
    puzzle.set_black_cell(2, 1);
    puzzle.set_black_cell(2, 2);
    
    vector<vector<int>> hor_sums = {{}, {2}};
    vector<vector<int>> ver_sums = {{}, {1}, {1}}; 
    
    puzzle.build_blocks(hor_sums, ver_sums, gen);
    KakuroSolver solver(puzzle);
    
    assert(!solver.solve()); 

    cerr.clear();

    cout << "OK" << endl;
}



int main() {
    cout << "Running tests\n" << endl;

    test_min_max_sum();
    test_combinations_generator();
    test_build_blocks();
    test_solver_small();
    test_solver_impossible();
    
    cout << "\nAll tests passed successfully!" << endl;
    return 0;
}