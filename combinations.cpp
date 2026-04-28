#include "combinations.h"

using namespace std;

/*---------------------------------------------------------------------[<]-
    Function: CombinationGenerator
    Synopsis: Constructor
  ---------------------------------------------------------------------[>]-*/
CombinationGenerator::CombinationGenerator(): combinations_precomputed(false) {
    compute_all_combinations();
}

/*---------------------------------------------------------------------[<]-
    Function: compute_all_combinations
    Synopsis: Precompute all combinations for sum 1...45 and length 1...9.
  ---------------------------------------------------------------------[>]-*/
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

/*---------------------------------------------------------------------[<]-
    Function: generate_all_combinations
    Synopsis: Generate all combinations of len and sum.
  ---------------------------------------------------------------------[>]-*/
vector<vector<int>> CombinationGenerator::generate_all_combinations(int len, int sum) {
    vector<vector<int>> result;
    vector<int> current;

    generate_combination(1, len, sum, current, result);

    return result;
}

/*---------------------------------------------------------------------[<]-
    Function: generate_combination
    Synopsis: Recursive function that generate combination for given sum 
              and lengths.
  ---------------------------------------------------------------------[>]-*/
void CombinationGenerator::generate_combination(int start, int remain_len, int remain_sum, vector<int> &current, vector<vector<int>> &result) {
    if (remain_len == 0) {
        if (remain_sum == 0) {
            result.push_back(current);
        }
        return;
    }

    for (int digit = start; digit <= 9; ++digit) {
        if (digit > remain_sum) break;

        current.push_back(digit);

        generate_combination(digit + 1, remain_len - 1, remain_sum - digit, current, result);
        
        current.pop_back();
    }
}

/*---------------------------------------------------------------------[<]-
    Function: get_combinations
    Synopsis: Returns precomputed combinations for given sum and length.
  ---------------------------------------------------------------------[>]-*/
vector<vector<int>> CombinationGenerator::get_combinations(int sum, int len) const {
    auto it = combinations.find({sum, len});

    if (it != combinations.end()) {
        return it->second;
    }

    return {};
}

/*---------------------------------------------------------------------[<]-
    Function: min_sum_for_len
    Synopsis: Returns minimum possible sum for a block of given length.
  ---------------------------------------------------------------------[>]-*/
int CombinationGenerator::min_sum_for_len(int len) {
    return (len * (len + 1)) / 2;
}

/*---------------------------------------------------------------------[<]-
    Function: max_sum_for_len
    Synopsis: Returns maximum possible sum for a block of given length.
  ---------------------------------------------------------------------[>]-*/
int CombinationGenerator::max_sum_for_len(int len) {
    return (len * (19 - len)) / 2;
}