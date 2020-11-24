#include <iostream>

#include <vector>

#include <map>

#include <stack>

class Solution {
public:
    /**
     * @param nums: A set of numbers.
     * @return: A list of lists. All valid subsets.
     */
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
        std::vector<std::vector<int>> subsets;
        // defaults to empty set:
        subsets.push_back( std::vector<int>() );

        const int N = nums.size();
        if ( 0 < N ) {
            // init num count:
            std::map<int, int> num_count;
            for (const int &num: nums) {
                if ( num_count.end() == num_count.find(num) ) {
                    num_count[num] = 0;
                }

                ++num_count.at(num);
            }
            // init state:
            State init_state;
            // init stack:
            std::stack<State> stack;
            stack.push(init_state);

            // generate all subsets:
            const int M = num_count.size();
            while ( !stack.empty() ) {
                State curr_state = stack.top();
                stack.pop();

                // get current num count:
                const auto curr_num_count = std::next(num_count.begin(), curr_state.n);
                const int curr_num = curr_num_count->first;
                const int curr_count = curr_num_count->second;

                if ( M - 1 == curr_state.n ) {
                    if ( !curr_state.subset.empty() ) subsets.push_back(curr_state.subset);

                    for (int i = 0; i < curr_count; ++i) {
                        curr_state.subset.push_back(curr_num);
                        subsets.push_back(curr_state.subset);
                    }
                } else {
                    State new_state = curr_state;

                    ++new_state.n;

                    stack.push(new_state);

                    for (int i = 0; i < curr_count; ++i) {
                        new_state.subset.push_back(curr_num);
                        stack.push(new_state);
                    }
                }
            }
        }

        return subsets;
    };
private:
    struct State {
        int n;
        std::vector<int> subset;
        State(): n(0) {}
    };
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,2,2};

    for (const auto &subset: solution.subsetsWithDup(nums1)) {
        for (const int &num: subset) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}