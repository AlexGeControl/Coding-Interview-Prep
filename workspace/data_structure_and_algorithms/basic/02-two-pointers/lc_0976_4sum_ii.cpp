#include <iostream>

#include <vector>

#include <unordered_map>

class Solution {
public:
    /**
     * @param A: a list
     * @param B: a list
     * @param C: a list
     * @param D: a list
     * @return: how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero
     */
    int fourSumCount(
        const std::vector<int> &A, 
        const std::vector<int> &B, 
        const std::vector<int> &C, 
        const std::vector<int> &D
    ) {
        // getSumCount, O(N**2):
        std::unordered_map<int, int> AB_sum_count = getSumCount(A, B);
        std::unordered_map<int, int> CD_sum_count = getSumCount(C, D);

        int sum_count = 0;
        for (const auto &ab_sum_count: AB_sum_count) {
            const int sum = ab_sum_count.first;
            const int count = ab_sum_count.second;

            if ( CD_sum_count.end() != CD_sum_count.find(-sum) ) {
                sum_count += count * CD_sum_count.at(-sum);
            }
        }

        return sum_count;
    }
private:
    std::unordered_map<int, int> getSumCount(
        const std::vector<int> &X,
        const std::vector<int> &Y
    ) {
        std::unordered_map<int, int> sum_count;

        for (const int &x: X) {
            for (const int &y: Y) {
                const int sum = x + y;

                if ( sum_count.end() == sum_count.find(sum) ) {
                    sum_count[sum] = 0;
                }

                ++sum_count.at(sum);
            }
        }

        return sum_count;
    }
};

int main() {
    Solution solution;

    std::vector<int> A { 1, 2};
    std::vector<int> B {-2,-1};
    std::vector<int> C {-1, 2};
    std::vector<int> D { 0, 2};

    std::cout << (solution.fourSumCount(A, B, C, D)) << std::endl;

    return EXIT_SUCCESS;
}