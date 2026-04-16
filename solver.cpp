#include "solver.h"

using namespace std;

KakuroSolver::KakuroSolver(KakuroPuzzle &p): puzzle(p), n_white(0) {}

vector<int> KakuroSolver::possible_digits(int r, int c) {
    int hb = puzzle.get_cell(r, c).index_horizontal_block;
    int vb = puzzle.get_cell(r, c).index_vertical_block;

    if (hb < 0 || hb >= (int)horizontal_sum.size() ||
        vb < 0 || vb >= (int)vertical_sum.size()) {
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
        if (horizontal_used[hb][d] || vertical_used[vb][d]) {
            continue;
        }

        if (d > remain_horizontal || d > remain_vertical) {
            continue;
        }

        int min_sum_len, max_sum_len;

        if (remain_cells_horizontal > 1) {
            min_sum_len = CombinationGenerator::min_sum_for_len(remain_cells_horizontal - 1);
            max_sum_len = CombinationGenerator::max_sum_for_len(remain_cells_horizontal - 1);

            if (remain_horizontal - d < min_sum_len || remain_horizontal - d > max_sum_len) {
                continue;
            }
        } else if (remain_horizontal - d != 0) {
            continue;
        }

        if (remain_cells_vertical > 1) {
            min_sum_len = CombinationGenerator::min_sum_for_len(remain_cells_vertical - 1);
            max_sum_len = CombinationGenerator::max_sum_for_len(remain_cells_vertical - 1);

            if (remain_vertical - d < min_sum_len || remain_vertical - d > max_sum_len) {
                continue;
            }
        } else if (remain_vertical - d != 0) {
            continue;
        }

        bool valid_horizontal = false;
        for (const auto &comb: horizontal_block.possible_combinations) {
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
                if (horizontal_used[hb][i]) {
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

            if (valid) {
                valid_horizontal = true;
                break;
            }
        }

        bool valid_vertical = false;
        for (const auto &comb: vertical_block.possible_combinations) {
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
                if (vertical_used[vb][i]) {
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

            if (valid) {
                valid_vertical = true;
                break;
            }
        }

        if (valid_horizontal && valid_vertical) {
            candidates.push_back(d);
        }
    }

    return candidates;
}

bool KakuroSolver::backtrack() {
    int best_index = -1;
    int best_count = 10;
    vector<int> best_candidates;

    for (size_t i = 0; i < white_cells.size(); ++i) {
        int row = white_cells[i].first;
        int col = white_cells[i].second;

        if (puzzle.get_cell(row, col).value == 0) {
            vector<int> candidates = possible_digits(row, col);

            if (candidates.empty()) {
                return false;
            }

            if (candidates.size() < (size_t)best_count) {
                best_count = candidates.size();
                best_index = i;
                best_candidates = candidates;

                if (best_count == 1) {
                    break;
                }
            }
        }
    }

    if (best_index == -1) {
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

    int row = white_cells[best_index].first;
    int col = white_cells[best_index].second;
    int horizontal_block = puzzle.get_cell(row, col).index_horizontal_block;
    int vertical_block = puzzle.get_cell(row, col).index_vertical_block;

    if (horizontal_block < 0 || horizontal_block >= (int)horizontal_sum.size() ||
        vertical_block < 0 || vertical_block >= (int)vertical_sum.size()) {
        return false;
    }

    for (int d: best_candidates) {
        puzzle.set_cell_value(row, col, d);
        horizontal_sum[horizontal_block] += d;
        vertical_sum[vertical_block] += d;
        horizontal_filled[horizontal_block]++;
        vertical_filled[vertical_block]++;
        horizontal_used[horizontal_block][d] = true;
        vertical_used[vertical_block][d] = true;

        if (backtrack()) {
            return true;
        }

        puzzle.set_cell_value(row, col, 0);
        horizontal_sum[horizontal_block] -= d;
        vertical_sum[vertical_block] -= d;
        horizontal_filled[horizontal_block]--;
        vertical_filled[vertical_block]--;
        horizontal_used[horizontal_block][d] = false;
        vertical_used[vertical_block][d] = false;
    }
    
    return false;
}

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

    n_white = white_cells.size();
    if (n_white == 0) {
        return true;
    }

    horizontal_sum.resize(puzzle.get_horizontal_blocks().size(), 0);
    vertical_sum.resize(puzzle.get_vertical_blocks().size(), 0);

    horizontal_filled.resize(puzzle.get_horizontal_blocks().size(), 0);
    vertical_filled.resize(puzzle.get_vertical_blocks().size(), 0);
    
    horizontal_used.resize(puzzle.get_horizontal_blocks().size(), vector<bool>(10, false));
    vertical_used.resize(puzzle.get_vertical_blocks().size(), vector<bool>(10, false));

    return backtrack();
}