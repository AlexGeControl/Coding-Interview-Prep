#include <cstdlib>

#include <limits>

#include <vector>

#include <queue>

#include <unordered_set>

#include <iostream>

class Solution {
public:
    /**
     * @param n: An integer
     * @return: return a  integer as description.
     */
    int nthUglyNumber(int n) {
        static std::vector<uint64_t> FACTORS {2, 3, 5};

        uint64_t result = 1;

        if ( 1 < n ) {
            // init visited:
            std::unordered_set<uint64_t> visited;
            // init min pq:
            std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<uint64_t>> min_pq;
            min_pq.push(1);

            // find n-th smallest element, O(n*logn):
            int order = 0;
            while ( order < n ) {
                // get current min. unly number:
                uint64_t curr_seed = min_pq.top();
                min_pq.pop();
                
                if ( visited.end() != visited.find(curr_seed) ) continue;

                // save current ugly number:
                visited.insert(curr_seed);
                ++order;
                result = curr_seed;

                // add new candidates:
                for (const uint64_t factor: FACTORS) {
                    uint64_t candidate = factor * curr_seed;

                    if ( visited.end() == visited.find(candidate) ) min_pq.push(candidate);
                }
            }
        }

        return static_cast<int>(result);
    }
};

int main() {
    Solution solution;

    int n1 = 1665;

    std::cout << ( solution.nthUglyNumber(n1) ) << std::endl;

    return EXIT_SUCCESS;
}