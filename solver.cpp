#include <iostream>
#include "solver.h"

using namespace std;

/*---------------------------------------------------------------------[<]-
    Function: KakuroSolver
    Synopsis: Constructor that keeps reference to the puzzle to be solved.
  ---------------------------------------------------------------------[>]-*/
KakuroSolver::KakuroSolver(KakuroPuzzle &p): puzzle(p) {}

/*---------------------------------------------------------------------[<]-
    Function: possible_digits
    Synopsis: Returns list of digits that can be placed ad (r, c) without
              violating sum, repetition, and combination constraints.
  ---------------------------------------------------------------------[>]-*/
vector<int> KakuroSolver::possible_digits(int r, int c) const {
    int hb = puzzle.get_cell(r, c).index_horizontal_block;
    int vb = puzzle.get_cell(r, c).index_vertical_block;

    if (hb < 0 || hb >= (int)horizontal_sum.size() || vb < 0 || vb >= (int)vertical_sum.size()) {
        return {};
    }

    const Block &horizontal_block = puzzle.get_horizontal_blocks()[hb];
    const Block &vertical_block = puzzle.get_vertical_blocks()[vb];

    int remain_horizontal = horizontal_block.sum - horizontal_sum[hb];
    int remain_vertical = vertical_block.sum - vertical_sum[vb];
    int remain_cells_horizontal = horizontal_block.cells.size() - horizontal_filled[hb];
    int remain_cells_vertical = vertical_block.cells.size() - vertical_filled[vb];

    vector<int> candidates;

    for (int d = 1; d <= 9; ++d) {
        if (horizontal_used[hb][d] || vertical_used[vb][d] || d > remain_horizontal || d > remain_vertical) {
            continue;
        }

        if (!is_sum_possible(remain_horizontal, remain_cells_horizontal, d) ||
            !is_sum_possible(remain_vertical, remain_cells_vertical, d)) {
            continue;
        }

        if (is_combination_possible(d, horizontal_block, horizontal_used[hb]) &&
            is_combination_possible(d, vertical_block, vertical_used[vb])) {
            candidates.push_back(d);
        }

    }

    return candidates;
}

/*---------------------------------------------------------------------[<]-
    Function: is_sum_possible
    Synopsis: Check if after placing digit, the remain sum can still
              be achieved with remaining cells. 
  ---------------------------------------------------------------------[>]-*/
bool KakuroSolver::is_sum_possible(int remain_sum, int remain_cells, int d) const {
    if (remain_cells > 1) {
        int min_sum_len = CombinationGenerator::min_sum_for_len(remain_cells - 1);
        int max_sum_len = CombinationGenerator::max_sum_for_len(remain_cells - 1);
        int new_remain = remain_sum - d;
    
        return (new_remain >= min_sum_len && new_remain <= max_sum_len);
    }

    return (remain_sum - d == 0);
}

/*---------------------------------------------------------------------[<]-
    Function: backtrack
    Synopsis: Recursive backtracking method. Selects best empty cell,
              tries each candidate digit, and proceeds. Returns true 
              is solved.
  ---------------------------------------------------------------------[>]-*/
bool KakuroSolver::backtrack() {
    vector<int> best_candidates;
    int best_index = find_best_empty_cell(best_candidates);

    if (best_index == END) return false;
    if (best_index == SOLVED) return is_puzzle_solved_correctly();

    int row = white_cells[best_index].first;
    int col = white_cells[best_index].second;
    int horizontal_block = puzzle.get_cell(row, col).index_horizontal_block;
    int vertical_block = puzzle.get_cell(row, col).index_vertical_block;

    if (horizontal_block < 0 || horizontal_block >= (int)horizontal_sum.size() ||
        vertical_block < 0 || vertical_block >= (int)vertical_sum.size()) {
        return false;
    }

    for (int d: best_candidates) {
       apply_digit(row, col, d, horizontal_block, vertical_block);

        if (backtrack()) {
            return true;
        }

        remove_digit(row, col, d, horizontal_block, vertical_block);
    }
    
    return false;
}

/*---------------------------------------------------------------------[<]-
    Function: is_combination_possible
    Synopsis: Checks whether placing digit is compatible with at least 
              one remaining combination from blocks's precomputed
              lists, give already used digits.
  ---------------------------------------------------------------------[>]-*/
bool KakuroSolver::is_combination_possible(int d, const Block &block, const vector<bool> &used_digits) const {
    for (const auto &comb: block.possible_combinations) {
        bool has_d = false;
        for (int x : comb) {
            if (x == d) {
                has_d = true;
                break;
            }
        }
        if (!has_d) continue;

        bool valid = true;
        for (int i = 1; i <= 9; ++i) {
            if (used_digits[i]) {
                bool has_used = false;
                for (int x : comb) {
                    if (x == i) {
                        has_used = true;
                        break;
                    }
                }
                if (!has_used) {
                    valid = false;
                    break;
                }
            }
        }

        if (valid) return true;
    }
    return false;
}

/*---------------------------------------------------------------------[<]-
    Function: find_best_empty_cell
    Synopsis: Selects empty cell with minimum number of candidates.
              If no candidates exist, returns G_STATUS_END. 
              If all cells filled, returns G_STATUS_SOLVED.
  ---------------------------------------------------------------------[>]-*/
int KakuroSolver::find_best_empty_cell(vector<int> &best_candidates) const {
    int best_index = -1;
    int best_count = 10;

    for (size_t i = 0; i < white_cells.size(); ++i) {
        int row = white_cells[i].first;
        int col = white_cells[i].second;

        if (puzzle.get_cell(row, col).value == 0) {
            vector<int> candidates = possible_digits(row, col);

            if (candidates.empty()) return END;

            if (candidates.size() < (size_t)best_count) {
                best_count = candidates.size();
                best_index = i;
                best_candidates = candidates;

                if (best_count == 1) break;
            }
        }
    }
    return (best_index == -1) ? SOLVED : best_index;
}

/*---------------------------------------------------------------------[<]-
    Function: is_puzzle_solved_correctly
    Synopsis: Verifies that all horizontal and vertical sums match
              the target sums.
  ---------------------------------------------------------------------[>]-*/
bool KakuroSolver::is_puzzle_solved_correctly() const {
    for (size_t i = 0; i < puzzle.get_horizontal_blocks().size(); ++i) {
        if (horizontal_sum[i] != puzzle.get_horizontal_blocks()[i].sum) {
            return false;
        }
    }

    for (size_t i = 0; i < puzzle.get_vertical_blocks().size(); ++i) {
        if (vertical_sum[i] != puzzle.get_vertical_blocks()[i].sum) {
            return false;
        }
    }

    return true;
}
 
/*---------------------------------------------------------------------[<]-
    Function: apply_digit
    Synopsis: Places digit into cell and updates all tracking structures.
  ---------------------------------------------------------------------[>]-*/
void KakuroSolver::apply_digit(int row, int col, int d, int horizontal_block, int vertical_block) {
    puzzle.set_cell_value(row, col, d);
    horizontal_sum[horizontal_block] += d;
    vertical_sum[vertical_block] += d;
    horizontal_filled[horizontal_block]++;
    vertical_filled[vertical_block]++;
    horizontal_used[horizontal_block][d] = true;
    vertical_used[vertical_block][d] = true;
}

/*---------------------------------------------------------------------[<]-
    Function: remove_digit
    Synopsis: Removes digit from cell and restores tracking structures.
  ---------------------------------------------------------------------[>]-*/
void KakuroSolver::remove_digit(int row, int col, int d, int horizontal_block, int vertical_block) {
    puzzle.set_cell_value(row, col, 0);
    horizontal_sum[horizontal_block] -= d;
    vertical_sum[vertical_block] -= d;
    horizontal_filled[horizontal_block]--;
    vertical_filled[vertical_block]--;
    horizontal_used[horizontal_block][d] = false;
    vertical_used[vertical_block][d] = false;
}

/*---------------------------------------------------------------------[<]-
    Function: solve
    Synopsis: Prepares data structures, checks combination preconditions,
              and starts backtracking. Returns true is solution found.
  ---------------------------------------------------------------------[>]-*/
bool KakuroSolver::solve() {
    white_cells.clear();
    
    int rows = puzzle.get_rows();
    if (rows == 0) return false;
    int cols = puzzle.get_cols();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!puzzle.get_cell(i, j).is_black) {
                white_cells.push_back({i, j});
            }
        }
    }

    if (white_cells.size() == 0) {
        return true;
    }

    horizontal_sum.resize(puzzle.get_horizontal_blocks().size(), 0);
    vertical_sum.resize(puzzle.get_vertical_blocks().size(), 0);

    horizontal_filled.resize(puzzle.get_horizontal_blocks().size(), 0);
    vertical_filled.resize(puzzle.get_vertical_blocks().size(), 0);
    
    horizontal_used.resize(puzzle.get_horizontal_blocks().size(), vector<bool>(10, false));
    vertical_used.resize(puzzle.get_vertical_blocks().size(), vector<bool>(10, false));

    for (const auto &bl: puzzle.get_horizontal_blocks()) {
        if (bl.possible_combinations.empty()) {
            cerr << "Error! Horizontal block with sum " << bl.sum << " doesn't have combinations!\n";
            return false;
        }
    }

    for (const auto &bl: puzzle.get_vertical_blocks()) {
        if (bl.possible_combinations.empty()) {
            cerr << "Error! Vertical block with sum " << bl.sum << " doesn't have combinations!\n";
            return false;
        }
    }

    return backtrack();
}