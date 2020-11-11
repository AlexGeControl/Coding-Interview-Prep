#include <iostream>

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    /**
     * @param nums: a list of integer
     * @param k: an integer
     * @return: return an integer, denote the minimum length of continuous subarrays whose sum equals to k
     */
    int subarraySumEqualsKII(vector<int> &nums, int k) {
        const size_t N = nums.size();
        
        if (N < 1) {
            return -1;
        }
        
        // init prefix sum & corresponding lookup table:
        int prefix_sum = 0;
        unordered_map<int, size_t> prefix_sum_loopup;
        prefix_sum_loopup[0] = 0;
        
        // iterate while lookup:
        size_t min_subarray_size = N + 1;
        for (size_t upper_exclude = 0; upper_exclude < N; ++upper_exclude) {
            prefix_sum += nums.at(upper_exclude);
            prefix_sum_loopup[prefix_sum] = upper_exclude + 1;
            
            if (prefix_sum_loopup.end() != prefix_sum_loopup.find(prefix_sum - k)) {
                size_t subarray_size = upper_exclude + 1 - prefix_sum_loopup.find(prefix_sum - k)->second;
                
                // update subarray size:
                if (subarray_size < min_subarray_size) {
                    min_subarray_size = subarray_size;
                }
            }
        }
        
        return (N + 1 == min_subarray_size) ? -1 : min_subarray_size;
    }
};

int main() {
    vector<int> nums {1,1,1,2};

    Solution solution;

    std::cout << solution.subarraySumEqualsKII(nums, 2) << std::endl;

    return EXIT_SUCCESS;
}