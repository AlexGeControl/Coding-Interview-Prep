#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param nums: a rotated sorted array
     * @return: the minimum number in the array
     */
    int findMin(const std::vector<int> &nums) {
        const int N = nums.size();

        int min_position = N - 1;

        int lo = 0, hi = N - 1;

        while ( lo <= hi ) {
            if ( hi == lo + 1 ) {
                min_position = ( nums.at(lo) < nums.at(hi) ? lo : hi);
                break;
            }

            int mi = (lo + hi) >> 1;

            if ( nums.at(lo) < nums.at(hi) ) {
                hi = mi;
            } else if ( nums.at(lo) < nums.at(mi) ) {
                lo = mi;
            } else if ( nums.at(mi) < nums.at(hi) ){
                hi = mi;
            } else {
                lo = mi;
            }
        }

        return nums.at(min_position);
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {4, 5, 6, 7, 0, 1, 2};

    std::cout << solution.findMin(nums1) << std::endl << std::endl;

    std::vector<int> nums2 {2,1};

    std::cout << solution.findMin(nums2) << std::endl << std::endl;

    std::vector<int> nums3 {1,2,3};

    std::cout << solution.findMin(nums2) << std::endl << std::endl;

    return EXIT_SUCCESS;
}