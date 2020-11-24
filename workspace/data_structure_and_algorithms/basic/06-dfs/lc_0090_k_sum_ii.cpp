#include <iostream>

#include <vector>

#include <stack>

class Solution {
public:
    /*
     * @param A: an integer array
     * @param k: a postive integer <= length(A)
     * @param target: an integer
     * @return: A list of lists of integer
     */
    std::vector<std::vector<int>> kSumII(std::vector<int> &A, size_t k, int target) {
        std::vector<std::vector<int>> candidates;

        const size_t N = A.size();

        if ( 0 < N && k <= N ) {
            // init state:
            State init_state(target);
            // init recursion stack:
            std::stack<State> recursion_stack;
            recursion_stack.push(init_state);

            while ( !recursion_stack.empty() ) {
                State curr_state = recursion_stack.top();
                recursion_stack.pop();

                if ( curr_state.indices.size() < k ) {
                    int nums_to_be_added = k - curr_state.indices.size();
                    int max_n = N - nums_to_be_added;

                    if ( curr_state.n < max_n ) {
                        State new_state = curr_state;

                        // select current number:
                        int new_target = curr_state.target - A.at(curr_state.n);
                        if ( 0 < new_target ) {
                            new_state.indices.push_back(curr_state.n);
                            new_state.target = new_target;
                            ++new_state.n;

                            recursion_stack.push(new_state);
                        } else if ( 0 == new_target && new_state.indices.size() == k - 1 ) {
                            new_state.indices.push_back(curr_state.n);
                            std::vector<int> candidate;
                            for (const int i: new_state.indices) candidate.push_back(A.at(i));
                            candidates.push_back(candidate);
                        }

                        // don't select current number, move directly to next:
                        ++curr_state.n;
                        recursion_stack.push(curr_state);
                    } else {
                        int new_target = curr_state.target;

                        for (size_t i = max_n; i < N; ++i) {
                            new_target -= A.at(i);
                            if ( new_target < 0 ) break;
                            curr_state.indices.push_back(i);
                        }

                        if ( 0 == new_target ) {
                            std::vector<int> candidate;
                            for (const int i: curr_state.indices) candidate.push_back(A.at(i));
                            candidates.push_back(candidate);
                        };
                    }
                }
            }
        }

        return candidates;
    }
private:
    struct State {
        int n;
        int target;
        std::vector<int> indices;

        State(const int target) {
            this->n = 0;
            this->target = target;
        }
    };
};

int main() {
    Solution solution;

    std::vector<int> A1 {1,2,3,4};
    int k1 = 2;
    int target1 = 5;

    for ( const auto &candidate: solution.kSumII(A1, k1, target1) ) {
        for ( const int &num: candidate ) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    return EXIT_SUCCESS;
}