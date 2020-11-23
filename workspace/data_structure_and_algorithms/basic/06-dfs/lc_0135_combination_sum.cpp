#include <iostream>

#include <vector>

#include <stack>

#include <set>

class Solution {
public:
    struct State {
        std::vector<int> num_count;
        int n;
        int target;
    };

    /**
     * @param candidates: A list of integers
     * @param target: An integer
     * @return: A list of lists of integers
     */
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
        std::vector<std::vector<int>> result;

        if ( 0 < candidates.size() ) {
            // make unique & sorted:
            std::set<int> unique_candidates;
            unique_candidates.insert(candidates.begin(), candidates.end());
            std::vector<int> sorted_candidates;
            sorted_candidates.insert(sorted_candidates.end(), unique_candidates.begin(), unique_candidates.end());

            // identify upper bound for each candidate:
            std::vector<int> num_upper_bound;
            for (const int &num: sorted_candidates) {
                if ( num > target ) break;

                num_upper_bound.push_back(target / num);
            }

            const int N = num_upper_bound.size();

            // init state:
            State init_state;
            init_state.num_count.resize(N);
            std::fill(init_state.num_count.begin(), init_state.num_count.end(), 0);
            init_state.n = 0;
            init_state.target = target;

            // init stack:
            std::stack<State> recursion_stack;
            recursion_stack.push(init_state);

            while ( !recursion_stack.empty() ) {
                State curr_state = recursion_stack.top();
                recursion_stack.pop();

                int n = curr_state.n;
                if (n < N) {
                    for (int i = 0; curr_state.num_count.at(n) + i <= num_upper_bound.at(n); ++i) {
                        int new_target = curr_state.target - i * sorted_candidates.at(n);

                        if ( new_target <= 0 ) {
                            if ( 0 == new_target ) {
                                curr_state.num_count.at(n) += i;

                                std::vector<int> proposal;
                                for (int j = 0; j < N; ++j) {
                                    while ( 0 < curr_state.num_count.at(j)-- ) {
                                        proposal.push_back(sorted_candidates.at(j));
                                    }
                                }
                                result.push_back(proposal);
                            }

                            break;
                        } else {
                            State new_state = curr_state;

                            new_state.num_count.at(n) += i;
                            new_state.n = n + 1;
                            new_state.target = new_target;

                            recursion_stack.push(new_state);
                        }
                    }
                }
            }
        }

        return result;
    }
};

int main() {
    Solution solution;
    
    std::vector<int> candidates1 {2, 3, 6, 7};
    int target1 = 7;

    for (const auto &proposal: solution.combinationSum(candidates1, target1)) {
        for (const int &num: proposal) {
            std::cout << num << " "; 
        }
        std::cout << std::endl;
    }

    std::vector<int> candidates2 {2, 2, 3};
    int target2 = 5;

    for (const auto &proposal: solution.combinationSum(candidates2, target2)) {
        for (const int &num: proposal) {
            std::cout << num << " "; 
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}