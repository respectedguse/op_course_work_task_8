#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <map>
#include <utility>
#include "combinations.h"

/*---------------------------------------------------------------------[<]-
    Class: Cell
    Synopsis: The class was created for representing a single cell in
              Kakuro grid.              
  ---------------------------------------------------------------------[>]-*/
class Cell {
public:
    bool is_black;
    int value;
    int index_horizontal_block;
    int index_vertical_block;

    Cell();
    Cell(bool black);
};

/*---------------------------------------------------------------------[<]-
    Class: Block
    Synopsis: The class was created for representing a horizontal or 
              vertical sequence of white cell.
  ---------------------------------------------------------------------[>]-*/
class Block {
public:
    int sum;
    std::vector<int> cells;
    std::vector<std::vector<int>> possible_combinations;

    Block();
    Block(int s);
};

/*---------------------------------------------------------------------[<]-
    Class: KakuroPuzzle
    Synopsis: Main class that represents puzzle. Holds grid, horizontal 
              and vertical blocks.
  ---------------------------------------------------------------------[>]-*/
class KakuroPuzzle {
private:
    std::vector<std::vector<Cell>> grid;
    std::vector<Block> horizontal_blocks;
    std::vector<Block> vertical_blocks;

    void reset_grid_indices();
    void build_horizontal_blocks(const std::vector<std::vector<int>> &sums, const CombinationGenerator &combination_generator);
    void build_vertical_blocks(const std::vector<std::vector<int>> &sums, const CombinationGenerator &combination_generator);

public:
    KakuroPuzzle();
    KakuroPuzzle(int rows, int cols);

    void set_black_cell(int r, int c);
    void set_cell_value(int r, int c, int value);

    int get_rows() const;
    int get_cols() const;
    Cell &get_cell(int r, int c);
    const Cell &get_cell(int r, int c) const;
    std::vector<Block> &get_horizontal_blocks();
    const std::vector<Block> &get_horizontal_blocks() const;
    std::vector<Block> &get_vertical_blocks();
    const std::vector<Block> &get_vertical_blocks() const; 

    void build_blocks(const std::vector<std::vector<int>> &horizontal_sums, const std::vector<std::vector<int>> &vertical_sums, const CombinationGenerator &combination_generator);
    void print_grid() const;
};

#endif