#include <iostream>

#include <cstdlib>

#include <limits>

#include <queue>

#include <vector>

class Solution {
public:
    /**
     * @param n: An integer
     * @return: return a  integer as description.
     */
    int nthUglyNumber(int n) {
        static const std::vector<uint64_t> FACTORS {2, 3, 5};

        std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<uint64_t>> pq;
        pq.push(1);

        Result result;
        while ( result.index < n ) {
            while ( pq.top() == result.value ) pq.pop();

            result.value = pq.top();

            ++result.index;

            for (const uint64_t &f: FACTORS) {
                uint64_t new_num = f*pq.top();
                pq.push(new_num);
            }

            pq.pop();
        }

        return static_cast<int>(result.value);
    }
private:
    struct Result {
        int index;
        uint64_t value;

        Result() : index(0), value(0) {}
    };
};

int main() {
    Solution solution;

    int n1 = 1665;

    std::cout << ( solution.nthUglyNumber(n1) ) << std::endl;

    return EXIT_SUCCESS;
}