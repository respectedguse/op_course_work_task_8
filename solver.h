#ifndef SOLVER_h
#define SOLVER_h

#include "puzzle.h"
#include "combinations.h"

class KakuroSolver {
private:
    KakuroPuzzle &puzzle;

    int n_white;
    std::vector<std::pair<int, int>> white_cells;

    std::vector<int> horizontal_sum;
    std::vector<int> vertical_sum;
    std::vector<int> horizontal_filled;
    std::vector<int> vertical_filled;
    std::vector<std::vector<bool>> horizontal_used;
    std::vector<std::vector<bool>> vertical_used;

    std::vector<int> possible_digits(int r, int c);
    bool backtrack();

public:
    KakuroSolver(KakuroPuzzle &p);
    bool solve();
};

#endif