#include <iostream>

#include <vector>
#include <deque>

using namespace std;

struct IndexMinPrefixSum {
    IndexMinPrefixSum(
        size_t index,
        int min_prefix_sum
    ): index_(index), min_prefix_sum_(min_prefix_sum) {}
    
    size_t index_;
    int min_prefix_sum_;
};

class Solution {
public:
    static const int INVALID = -1;
    /**
     * @param A: the array
     * @param K: sum
     * @return: the length
     */
    int shortestSubarray(const vector<int> &A, const int K) {
        const size_t N = A.size();
        
        // build prefix sum & corresponding monotonic queue:
        int prefix_sum = 0;
        deque<IndexMinPrefixSum> monotonic_queue;
        monotonic_queue.push_back(IndexMinPrefixSum(0, 0));
        
        size_t min_subarray_size = N + 1;
        for (size_t index = 1; index <= N; ++index) {
            prefix_sum += A.at(index - 1);
            
            while (
                0 < monotonic_queue.size() &&
                K <= (prefix_sum - monotonic_queue.front().min_prefix_sum_)
            ) {
                min_subarray_size = min(min_subarray_size, index - monotonic_queue.front().index_);
                monotonic_queue.pop_front();
            }
            
            while (
                0 < monotonic_queue.size() &&
                monotonic_queue.back().min_prefix_sum_ >= prefix_sum
            ) {
                monotonic_queue.pop_back();
            }
            
            monotonic_queue.push_back(IndexMinPrefixSum(index, prefix_sum));
        }
        
        return N + 1 == min_subarray_size ? INVALID : min_subarray_size;
    }
};

int main() {
    vector<int> A1 {1};
    const int K1 = 1;

    Solution solution;

    std::cout << solution.shortestSubarray(A1, K1) << std::endl;

    vector<int> A2 {1, 2};
    const int K2 = 4;

    std::cout << solution.shortestSubarray(A2, K2) << std::endl;

    return EXIT_SUCCESS;
}