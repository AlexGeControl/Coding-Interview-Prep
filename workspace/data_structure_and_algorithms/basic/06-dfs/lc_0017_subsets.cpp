#include <iostream>

#include <algorithm>

#include <vector>

#include <stack>

class Solution {
public:
    /**
     * @param nums: A set of numbers
     * @return: A list of lists
     */
    std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
        std::vector<std::vector<int>> subsets;
        // defaults to empty set:
        subsets.push_back( std::vector<int>() );

        const int N = nums.size();
        if ( 0 < N ) {
            // sort nums:
            std::sort(nums.begin(), nums.end());
            // init state:
            State init_state;
            // init stack:
            std::stack<State> stack;
            stack.push(init_state);

            while ( !stack.empty() ) {
                State curr_state = stack.top();
                stack.pop();

                if ( curr_state.n < N ) {
                    if ( N - 1 == curr_state.n ) {
                        if ( !curr_state.subset.empty() ) subsets.push_back(curr_state.subset);

                        curr_state.subset.push_back(nums.at(curr_state.n));

                        subsets.push_back(curr_state.subset);
                    } else {
                        State new_state = curr_state;

                        ++new_state.n;

                        stack.push(new_state);

                        new_state.subset.push_back(nums.at(curr_state.n));
                        stack.push(new_state);
                    }
                }
            }
        }

        return subsets;
    }
private:
    struct State {
        int n;
        std::vector<int> subset;

        State(): n(0) {}
    };
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,2,3};

    for (const auto &subset: solution.subsets(nums1)) {
        for (const int &num: subset) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}