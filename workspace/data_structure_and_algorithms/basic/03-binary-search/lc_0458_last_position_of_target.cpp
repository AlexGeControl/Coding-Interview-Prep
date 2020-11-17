#include <iostream>

#include <vector>

class Solution {
public:
    static const int NOT_FOUND = -1;

    /**
     * @param nums: An integer array sorted in ascending order
     * @param target: An integer
     * @return: An integer
     */
    int lastPosition(const std::vector<int> &nums, const int target) {
        const int N = nums.size();

        int position = NOT_FOUND;

        if ( 0 < N ) { 
            int lo = 0, hi = N - 1;

            while ( lo <= hi ) {
                int mi = ( lo + hi ) >> 1;

                if ( target < nums.at(mi) ) {
                    hi = mi - 1;
                } else {
                    if ( target == nums.at(mi) ) {
                        // update latest position:
                        position = std::max(position, mi);
                    }

                    lo = mi + 1;
                }
            }
        }   

        return position;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,4,4,5,7,7,8,9,9,10};
    int target1 = 7;

    std::cout << (5 == solution.lastPosition(nums1, target1)) << std::endl;

    std::vector<int> nums2 {1,2,3,3,4,5,10};
    int target2 = 3;

    std::cout << (3 == solution.lastPosition(nums2, target2)) << std::endl;

    std::vector<int> nums3 {1,2,3,3,4,5,10};
    int target3 = 6;

    std::cout << (Solution::NOT_FOUND == solution.lastPosition(nums3, target3)) << std::endl;

    return EXIT_SUCCESS;
}