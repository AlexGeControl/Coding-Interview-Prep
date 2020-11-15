#include <iostream>

#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    /**
     * @param nums: an array of integer
     * @param target: An integer
     * @return: An integer
     */
    int numUniquePairs(const std::vector<int> &nums, int target) {
        // format input as hashmap, O(N):
        std::unordered_map<int, bool> complement_nums;
        std::unordered_set<int> used_nums;

        int num_unique_pairs = 0;
        for (const int &num: nums) {
            if ( used_nums.end() != used_nums.find(num) ) continue;

            const int complement_num = target - num;

            if (
                complement_nums.end() != complement_nums.find(num) &&
                !complement_nums.at(num)
            ) {
                complement_nums.at(num) = true;

                ++num_unique_pairs;

                used_nums.insert(num);
                used_nums.insert(complement_num);
            }

            if (
                complement_nums.end() == complement_nums.find(complement_num)
            ) {
                complement_nums[complement_num] = false;
            }
        }

        return num_unique_pairs;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,1,2,45,46,46};
    int target1 = 47;

    std::cout << (2 == solution.numUniquePairs(nums1, target1)) << std::endl;

    std::vector<int> nums2 {7,11,11,1,2,3,4};
    int target2 = 22;

    std::cout << (1 == solution.numUniquePairs(nums2, target2)) << std::endl;

    std::vector<int> nums3 {-1,0,1};
    int target3 = 0;

    std::cout << (1 == solution.numUniquePairs(nums3, target3)) << std::endl;

    std::vector<int> nums4 {
        107,0,107,0,107,0,0,0,0,0,0,0,0,107,0,107,107,106,1,1,9,98,9,97,11,1001,2001,-91,201,203,201,999,345,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,4,5,6,1,1,1,1,1,1,1,1,1,1,1,101,1,1,1,1,1,1,1,1
    };
    int target4 = 107;

    std::cout << (4 == solution.numUniquePairs(nums4, target4)) << std::endl;

    return EXIT_SUCCESS;
}