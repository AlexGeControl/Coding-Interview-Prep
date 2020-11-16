#include <iostream>

#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @param nums: an array of integer
     * @param target: an integer
     * @return: an integer
     */
    int twoSum5(const std::vector<int> &nums, const int target) {
        const int N = nums.size();
        
        int num_pairs = 0;

        if ( 1 < N ) {
            // sort input nums, O(N*logN):
            std::vector<int> sorted_nums(nums);
            std::sort(sorted_nums.begin(), sorted_nums.end());

            // identify tuples:
            int left = 0, right = N - 1;
            while ( left < right ) {
                const int curr_sum = sorted_nums.at(left) + sorted_nums.at(right);
                if ( curr_sum <= target ) {
                    ++left;
                } else {
                    num_pairs += right - left;
                    --right;
                }
            }

            num_pairs = N * (N - 1) / 2 - num_pairs;
        }

        return num_pairs;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {2, 7, 11, 15};
    int target1 = 24;

    std::cout << (5 == solution.twoSum5(nums1, target1)) << std::endl;

    return EXIT_SUCCESS;
}