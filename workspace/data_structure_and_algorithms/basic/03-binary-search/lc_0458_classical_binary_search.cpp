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
    int findPosition(const std::vector<int> &nums, const int target) {
        const int N = nums.size(); 

        int index = NOT_FOUND;

        if ( 0 < N ) {
            int lo = 0, hi = N - 1;
            
            while ( lo <= hi ) {
                int mi = (lo + hi) >> 1;

                if ( target == nums.at(mi) ) {
                    index = mi;
                    break;
                }

                if ( target < nums.at(mi) ) {
                    hi = mi - 1;
                } else {
                    lo = mi + 1;
                }
            }
        }

        return index;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,2,2,4,5,5};
    int target1 = 2;

    std::cout << solution.findPosition(nums1, target1) << std::endl;

    std::vector<int> nums2 {1,2,2,4,5,5};
    int target2 = 6;

    std::cout << solution.findPosition(nums2, target2) << std::endl;

    return EXIT_SUCCESS;
}