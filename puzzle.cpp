#include <iostream>
#include "puzzle.h"

using namespace std;

Cell::Cell() : is_black(false), value(0), index_horizontal_block(-1), index_vertical_block(-1) {}
Cell::Cell(bool black) : is_black(black), value(0), index_horizontal_block(-1), index_vertical_block(-1) {}

Block::Block() : sum(0) {}
Block::Block(int s) : sum(s) {}

KakuroPuzzle::KakuroPuzzle() {}
KakuroPuzzle::KakuroPuzzle(int rows, int cols) : grid(rows, vector<Cell>(cols)) {}

void KakuroPuzzle::set_black_cell(int r, int c) {
    if (r >= 0 && r < (int)grid.size() && c >= 0 && c < (int)grid[0].size()) {
        grid[r][c].is_black = true;
    }
}

void KakuroPuzzle::set_cell_value(int r, int c, int value) {
    if (r >= 0 && r < (int)grid.size() && c >= 0 && c < (int)grid[0].size()) {
        grid[r][c].value = value;
    }
}

int KakuroPuzzle::get_rows() const {
    return grid.size();
}

int KakuroPuzzle::get_cols() const {
    return grid.empty() ? 0 : grid[0].size();
}

Cell &KakuroPuzzle::get_cell(int r, int c) {
    return grid[r][c];
}

vector<Block> &KakuroPuzzle::get_horizontal_blocks() {
    return horizontal_blocks;
}

vector<Block> &KakuroPuzzle::get_vertical_blocks() {
    return vertical_blocks;
}

void KakuroPuzzle::build_blocks(const std::vector<std::vector<int>> &horizontal_sums, const std::vector<std::vector<int>> &vertical_sums, const CombinationGenerator &combination_generator) {
    horizontal_blocks.clear();
    vertical_blocks.clear();

    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (!grid[r][c].is_black) {
                grid[r][c].index_horizontal_block = -1;
                grid[r][c].index_vertical_block = -1;
            }
        }
    }

    for (int r = 0; r < rows; ++r) {
        int start = -1;
        int block_index = 0;

        for (int c = 0; c <= cols; ++c) {
            bool is_black = (c == cols) ? true : grid[r][c].is_black;

            if (!is_black && start == -1) {
                start = c;
            }

            if (is_black && start != -1) {
                int len = c - start;

                if (len > 0) {
                    Block block;

                    if (r < (int)horizontal_sums.size() && block_index < (int)horizontal_sums[r].size()) {
                        block.sum = horizontal_sums[r][block_index];
                    } else {
                        block.sum = 0;
                    }

                    for (int i = start; i < c; ++i) {
                        int cell_index = r * cols + i;
                        block.cells.push_back(cell_index);
                        grid[r][i].index_horizontal_block = horizontal_blocks.size();
                    }

                    block.possible_combinations = combination_generator.get_combinations(block.sum, len);

                    horizontal_blocks.push_back(block);
                }

                start = -1;
                ++block_index;
            }
        }
    }

    for (int c = 0; c < cols; ++c) {
        int start = -1;
        int block_index = 0;

        for (int r = 0; r <= rows; ++r) {
            bool is_black = (r == rows) ? true : grid[r][c].is_black;

            if (!is_black && start == -1) {
                start = r;
            }

            if (is_black && start != -1) {
                int len = r - start;

                if (len > 0) {
                    Block block;

                    if (c < (int)vertical_sums.size() && block_index < (int)vertical_sums[c].size()) {
                        block.sum = vertical_sums[c][block_index];
                    } else {
                        block.sum = 0;
                    }

                    for (int i = start; i < r; ++i) {
                        int cell_index = i * cols + c;

                        block.cells.push_back(cell_index);

                        grid[i][c].index_vertical_block = vertical_blocks.size();
                    }

                    block.possible_combinations = combination_generator.get_combinations(block.sum, len);

                    vertical_blocks.push_back(block);
                }
                
                start = -1;
                ++block_index;
            }
        }
    }
}

void KakuroPuzzle::print_grid() const {
    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j].is_black) {
                cout << "## ";
            } else if (grid[i][j].value == 0) {
                cout << " . ";
            } else {
                cout << ' ' << grid[i][j].value << ' ';
            }
        }
        cout << '\n';
    }
}  