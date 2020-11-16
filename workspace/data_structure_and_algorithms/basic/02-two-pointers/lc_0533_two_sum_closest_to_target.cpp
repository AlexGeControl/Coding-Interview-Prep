#include <cstdlib>
#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param nums: an integer array
     * @param target: An integer
     * @return: the difference between the sum and the target
     */
    int twoSumClosest(const std::vector<int> &nums, int target) {
        return 0;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {-1, 2, 1, -4};
    int target1 = 4;

    std::cout << solution.twoSumClosest(nums1, target1) << std::endl;

    return EXIT_SUCCESS;
}