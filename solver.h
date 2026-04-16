#ifndef SOLVER_h
#define SOLVER_h

#include "puzzle.h"
#include "combinations.h"

class KakuroSolver {
private:
    KakuroPuzzle &puzzle;

    std::vector<std::pair<int, int>> white_cells;

    std::vector<int> horizontal_sum;
    std::vector<int> vertical_sum;
    std::vector<int> horizontal_filled;
    std::vector<int> vertical_filled;
    std::vector<std::vector<bool>> horizontal_used;
    std::vector<std::vector<bool>> vertical_used;

    bool is_sum_possible(int remain_sum, int remain_cells, int d) const;
    bool is_combination_possible(int d, const Block &block, const std::vector<bool> &used_digits) const;
    std::vector<int> possible_digits(int r, int c) const;

    int find_best_empty_cell(std::vector<int> &best_candidates) const;
    bool is_puzzle_solved_correctly() const;
    void apply_digit(int row, int col, int d, int horizontal_block, int vertical_block);
    void remove_digit(int row, int col, int d, int horizontal_block, int vertical_block);
    bool backtrack();

public:
    KakuroSolver(KakuroPuzzle &p);
    bool solve();
};

#endif