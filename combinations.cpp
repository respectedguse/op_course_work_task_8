#include "combinations.h"

using namespace std;

CombinationGenerator::CombinationGenerator(): combinations_precomputed(false) {
    compute_all_combinations();
}

void CombinationGenerator::compute_all_combinations() {
    if (combinations_precomputed) {
        return;
    }

    for (int len = 1; len <= 9; ++len) {
        for (int sum = 1; sum <= 45; ++sum) {
            auto combs = generate_all_combinations(len, sum);
            
            if (!combs.empty()) {
                combinations[{sum, len}] = combs;
            }
        }
    }

    combinations_precomputed = true;
}

vector<vector<int>> CombinationGenerator::generate_all_combinations(int len, int sum) {
    vector<vector<int>> result;
    vector<int> current;

    generate_combination(1, len, sum, current, result);

    return result;
}

void CombinationGenerator::generate_combination(int start, int remain_len, int remain_sum, vector<int> &current, vector<vector<int>> &result) {
    if (remain_len == 0) {
        if (remain_sum == 0) {
            result.push_back(current);
        }
        return;
    }

    for (int digit = start; digit <= 9; ++digit) {
        if (digit > remain_sum) {
            break;
        }

        current.push_back(digit);

        generate_combination(digit + 1, remain_len - 1, remain_sum - digit, current, result);
        
        current.pop_back();
    }
}

vector<vector<int>> CombinationGenerator::get_combinations(int sum, int len) const {
    auto it = combinations.find({sum, len});

    if (it != combinations.end()) {
        return it->second;
    }

    return {};
}

int CombinationGenerator::min_sum_for_len(int len) {
    return (len * (len + 1)) / 2;
}

int CombinationGenerator::max_sum_for_len(int len) {
    return (len * (19 - len)) / 2;
}