#include <iostream>

#include <vector>

#include <unordered_set>

#include <stack>

class Solution {
public:
    /*
     * @param nums: A list of integers.
     * @return: A list of permutations.
     */
    std::vector<std::vector<int>> permute(std::vector<int> &nums) {
        std::vector<std::vector<int>> permutations;

        const int N = nums.size();
        if ( 0 < N ) {
            // init state:
            State init_state;
            for (int i = 0; i < N; ++i) init_state.indices.insert(i);
            // init stack:
            std::stack<State> stack;
            stack.push(init_state);

            while ( !stack.empty() ) {
                State curr_state = stack.top();
                stack.pop();

                if ( 1 == curr_state.indices.size() ) {
                    curr_state.permutation.push_back(nums.at(*curr_state.indices.begin()));
                    permutations.push_back(curr_state.permutation);
                } else {
                    for (const int &index: curr_state.indices) {
                        State new_state = curr_state;

                        new_state.indices.erase(index);
                        new_state.permutation.push_back(nums.at(index));

                        stack.push(new_state);
                    }
                }
            }
        } else {
            permutations.push_back( std::vector<int>() );
        }

        return permutations;
    }
private:
    struct State {
        std::unordered_set<int> indices;
        std::vector<int> permutation;
    };
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,2,3};
    for (const auto &permutation: solution.permute(nums1)) {
        for (const int &num: permutation) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}