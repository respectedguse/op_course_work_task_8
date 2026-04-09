#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include <vector>
#include <map>

class CombinationGenerator {
private:
    std::map<std::pair<int, int>, std::vector<std::vector<int>>> combinations;
    bool combinations_precomputed;

    static void generate_combination(int start, int remain_len, int remain_sum, std::vector<int> &current, std::vector<std::vector<int>> &result);

public:
    CombinationGenerator();

    void compute_all_combinations();
    std::vector<std::vector<int>> generate_all_combinations(int len, int sum);
    std::vector<std::vector<int>> get_combinations(int sum, int len) const;

    static int min_sum_for_len(int len);
    static int max_sum_for_len(int len);
};

#endif