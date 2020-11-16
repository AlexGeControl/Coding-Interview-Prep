#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param nums: an integer array
     * @return: nothing
     */
    void moveZeroes(std::vector<int> &nums) {
        const int N = nums.size();

        if ( 0 < N ) {
            // init two pointers, slow & fast:
            int non_zero_index = 0, curr_index = 0;

            while (
                curr_index < N
            ) {
                while ( 
                    curr_index < N && 
                    0 == nums.at(curr_index)
                ) {
                    ++curr_index;
                }

                if ( curr_index >= N ) break;

                if ( non_zero_index != curr_index ) {
                    nums.at(non_zero_index) = nums.at(curr_index);
                    nums.at(curr_index) = 0;
                }

                ++non_zero_index;
                ++curr_index;
            }
        }
    }
private:
    void swap(std::vector<int> &nums, int i, int j) {
        int value = nums.at(i);
        nums.at(i) = nums.at(j);
        nums.at(j) = value;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {0, 1, 0, 3, 12};
    solution.moveZeroes(nums1);

    for (const int &num1: nums1) {
        std::cout << num1 << " ";
    }
    std::cout << std::endl;

    std::vector<int> nums2 {0, 0, 0, 3, 1};
    solution.moveZeroes(nums2);

    for (const int &num2: nums2) {
        std::cout << num2 << " ";
    }
    std::cout << std::endl;
}