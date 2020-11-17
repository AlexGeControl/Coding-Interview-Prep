#include <iostream>

#include <vector>

class Solution {
public:
    static const int NOT_FOUND = -1;
    /**
     * @param nums: The integer array.
     * @param target: Target to find.
     * @return: The first position of target. Position starts from 0.
     */
    int binarySearch(const std::vector<int> &nums, const int target) {
        const int N = nums.size();

        int position = N;

        if ( 0 < N ) {
            int lo = 0, hi = N - 1;

            while ( lo <= hi ) {
                int mi = ( lo + hi ) >> 1;

                if ( target <= nums.at(mi) ) {
                    if ( target == nums.at(mi) ) {
                        // update min. position;
                        position = std::min(position, mi);
                    }
                    hi = mi - 1;
                } else {
                    lo = mi + 1;
                }
            }
        }

        return ( N == position ? NOT_FOUND : position);
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,4,4,5,7,7,8,9,9,10};
    int target1 = 1;

    std::cout << (0 == solution.binarySearch(nums1, target1)) << std::endl;

    std::vector<int> nums2 {1,2,3,3,4,5,10};
    int target2 = 3;

    std::cout << (2 == solution.binarySearch(nums2, target2)) << std::endl;

    std::vector<int> nums3 {1,2,3,3,4,5,10};
    int target3 = 6;

    std::cout << (Solution::NOT_FOUND == solution.binarySearch(nums3, target3)) << std::endl;

    return EXIT_SUCCESS;
}