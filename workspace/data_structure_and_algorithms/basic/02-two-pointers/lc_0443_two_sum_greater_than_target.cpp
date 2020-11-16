#include <iostream>

#include <vector>

#include <algorithm>

class Solution {
public:
    /**
     * @param nums: an array of integer
     * @param target: An integer
     * @return: an integer
     */
    int twoSum2(const std::vector<int> &nums, const int target) {
        const int N = nums.size();

        int num_pairs = 0;

        if ( 1 < N ) {
            // sort numbers, O(N*logN):
            std::vector<int> sorted_nums(nums);
            std::sort(sorted_nums.begin(), sorted_nums.end());

            int left = 0, right = N - 1;
            while ( left < right ) {
                if ( sorted_nums.at(left) + sorted_nums.at(right) > target) {
                    num_pairs += right - left;
                    --right;
                } else {
                    ++left;
                }
            }
        }

        return num_pairs;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {2, 7, 11, 15};
    int target1 = 24;
    
    std::cout << (1 == solution.twoSum2(nums1, target1)) << std::endl;

    std::vector<int> nums2 {1, 1, 1, 1};
    int target2 = 1;
    
    std::cout << (6 == solution.twoSum2(nums2, target2)) << std::endl;

    return EXIT_SUCCESS;
}