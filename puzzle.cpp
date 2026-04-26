#include <iostream>
#include "puzzle.h"

using namespace std;

/*---------------------------------------------------------------------[<]-
    Functions: Cell 
    Synopsis: Cell() - default constructor that initializes as non-black,
              value 0, block indices to -1.
              Cell(bool black) - constructor that sets cell as black
              or not, value 0, block indices to -1.
  ---------------------------------------------------------------------[>]-*/
Cell::Cell() : is_black(false), value(0), index_horizontal_block(-1), index_vertical_block(-1) {}
Cell::Cell(bool black) : is_black(black), value(0), index_horizontal_block(-1), index_vertical_block(-1) {}

/*---------------------------------------------------------------------[<]-
    Functions: Block
    Synopsis: Block() - default constructor that initializes sum to 0.
              Block(int s) - constructor that sets sum for the block.
  ---------------------------------------------------------------------[>]-*/
Block::Block() : sum(0) {}
Block::Block(int s) : sum(s) {}

/*---------------------------------------------------------------------[<]-
    Functions: KakuroPuzzle
    Synopsis: KakuroPuzzle() - default constructor that creates an empty 
              puzzle.
              KakuroPuzzle(int row, int cols) - constructor that creates
              a puzzle grid of give size.
  ---------------------------------------------------------------------[>]-*/
KakuroPuzzle::KakuroPuzzle() {}
KakuroPuzzle::KakuroPuzzle(int rows, int cols) : grid(rows, vector<Cell>(cols)) {}

/*---------------------------------------------------------------------[<]-
    Function: set_black_cell
    Synopsis: Sets the cell as (r, c) as black.
  ---------------------------------------------------------------------[>]-*/
void KakuroPuzzle::set_black_cell(int r, int c) {
    if (r >= 0 && r < (int)grid.size() && c >= 0 && c < (int)grid[0].size()) {
        grid[r][c].is_black = true;
    }
}

/*---------------------------------------------------------------------[<]-
    Function: set_cell_value
    Synopsis: Sets the digit value for a white cell.
  ---------------------------------------------------------------------[>]-*/
void KakuroPuzzle::set_cell_value(int r, int c, int value) {
    if (r >= 0 && r < (int)grid.size() && c >= 0 && c < (int)grid[0].size()) {
        grid[r][c].value = value;
    }
}

/*---------------------------------------------------------------------[<]-
    Function: get_rows
    Synopsis: Returns the number of rows in the grid.
  ---------------------------------------------------------------------[>]-*/
int KakuroPuzzle::get_rows() const {
    return grid.size();
}

/*---------------------------------------------------------------------[<]-
    Function: get_cols
    Synopsis: Returns the number of cols in the grid.              
  ---------------------------------------------------------------------[>]-*/
int KakuroPuzzle::get_cols() const {
    return grid.empty() ? 0 : grid[0].size();
}

/*---------------------------------------------------------------------[<]-
    Function: get_cell
    Synopsis: Returns a reference to the cell at (r, c).
  ---------------------------------------------------------------------[>]-*/
Cell &KakuroPuzzle::get_cell(int r, int c) {
    return grid[r][c];
}

/*---------------------------------------------------------------------[<]-
    Function: get_horizontal_blocks
    Synopsis: Returns a reference to the vector of horizontal blocks.
  ---------------------------------------------------------------------[>]-*/
vector<Block> &KakuroPuzzle::get_horizontal_blocks() {
    return horizontal_blocks;
}

/*---------------------------------------------------------------------[<]-
    Function: get_vertical_blocks
    Synopsis: Returns a reference to the vector of vertical blocks.
  ---------------------------------------------------------------------[>]-*/
vector<Block> &KakuroPuzzle::get_vertical_blocks() {
    return vertical_blocks;
}

/*---------------------------------------------------------------------[<]-
    Function: get_cell
    Synopsis: Returns a const reference to the cell at (r, c).
  ---------------------------------------------------------------------[>]-*/
const Cell &KakuroPuzzle::get_cell(int r, int c) const {
    return grid[r][c];
}

/*---------------------------------------------------------------------[<]-
    Function: get_horizontal_blocks
    Synopsis: Returns a const reference to the vector of horizontal blocks.
  ---------------------------------------------------------------------[>]-*/
const vector<Block> &KakuroPuzzle::get_horizontal_blocks() const {
    return horizontal_blocks;
}

/*---------------------------------------------------------------------[<]-
    Function: get_vertical_blocks
    Synopsis: Returns a const reference to the vector of vertical blocks.
  ---------------------------------------------------------------------[>]-*/
const vector<Block> &KakuroPuzzle::get_vertical_blocks() const {
    return vertical_blocks;
}

/*---------------------------------------------------------------------[<]-
    Function: clear_solution
    Synopsis: Resets the value of all non-black cells to 0, clear
              the current puzzle solution.
  ---------------------------------------------------------------------[>]-*/
void KakuroPuzzle::clear_solution() {
    for (auto &row: grid) {
        for (auto &cell: row) {
            if (!cell.is_black) {
                cell.value = 0;
            }
        }
    }
}

/*---------------------------------------------------------------------[<]-
    Function: build_blocks 
    Synopsis: Builds horizontal and vertical block from given sums.
              Clears existing blocks, resets indices and build blocks
              using the combination generator.
  ---------------------------------------------------------------------[>]-*/
void KakuroPuzzle::build_blocks(const vector<vector<int>> &horizontal_sums, 
                                const vector<vector<int>> &vertical_sums, 
                                const CombinationGenerator &combination_generator) {
    horizontal_blocks.clear();
    vertical_blocks.clear();

    if (grid.empty()) return;

    reset_grid_indices();
    build_horizontal_blocks(horizontal_sums, combination_generator);
    build_vertical_blocks(vertical_sums, combination_generator);
}

/*---------------------------------------------------------------------[<]-
    Function: reset_grid_indices
    Synopsis: Resets the horizontal and vertical blocks indices for all
              white cells to -1.
  ---------------------------------------------------------------------[>]-*/
void KakuroPuzzle::reset_grid_indices() {
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
}

/*---------------------------------------------------------------------[<]-
    Function: build_horizontal_blocks
    Synopsis: Creates horizontal blocks for each row of given sums.
              Assigns block indices to cells and stores possible 
              combinations.
  ---------------------------------------------------------------------[>]-*/
void KakuroPuzzle::build_horizontal_blocks(const vector<vector<int>> &sums, const CombinationGenerator &combination_generator) {
    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();

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

                    if (r < (int)sums.size() && block_index < (int)sums[r].size()) {
                        block.sum = sums[r][block_index];
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
}

/*---------------------------------------------------------------------[<]-
    Function: build_vertical_blocks
    Synopsis: Creates vertical blocks for each row of given sums.
              Assigns block indices to cells and stores possible 
              combinations.
  ---------------------------------------------------------------------[>]-*/
void KakuroPuzzle::build_vertical_blocks(const vector<vector<int>> &sums, const CombinationGenerator &combination_generator) {
    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();

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

                    if (c < (int)sums.size() && block_index < (int)sums[c].size()) {
                        block.sum = sums[c][block_index];
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

/*---------------------------------------------------------------------[<]-
    Function: print_grid
    Synopsis: Prints the grid to console.
  ---------------------------------------------------------------------[>]-*/
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