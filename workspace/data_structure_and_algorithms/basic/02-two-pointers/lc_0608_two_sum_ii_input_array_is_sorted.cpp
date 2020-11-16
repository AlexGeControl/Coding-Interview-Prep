#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param nums: an array of Integer
     * @param target: target = nums[index1] + nums[index2]
     * @return: [index1 + 1, index2 + 1] (index1 < index2)
     */
    std::vector<int> twoSum(const std::vector<int> &nums, const int target) {
        const int N = nums.size();

        std::vector<int> tuple;

        if ( 1 < N ) {
            int left = 0, right = N - 1;

            while ( left < right ) {
                const int curr_sum = nums.at(left) + nums.at(right);

                if ( curr_sum > target ) {
                    --right;
                } else if ( curr_sum == target ) {
                    tuple.push_back(left + 1);
                    tuple.push_back(right + 1);
                    break;
                } else {
                    ++left;
                }
            }
        }

        return tuple;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {2, 7, 11, 15};
    int target1 = 9;

    std::vector<int> tuple1 = solution.twoSum(nums1, target1); 
    std::cout << tuple1.at(0) << ", " << tuple1.at(1) << std::endl;

    return EXIT_SUCCESS;
}