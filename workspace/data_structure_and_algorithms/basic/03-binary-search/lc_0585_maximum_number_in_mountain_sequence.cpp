#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param nums: a mountain sequence which increase firstly and then decrease
     * @return: then mountain top
     */
    int mountainSequence(const std::vector<int> &nums) {
        const int N = nums.size();

        if ( 2 == N ) {
            return std::max(nums.at(0), nums.at(1));
        } else {
            int lo = 0, hi = N - 1;

            while ( lo < hi ) {
                if ( hi == lo + 1 ) {
                    return std::max(nums.at(lo), nums.at(hi));
                }

                int mi = ( lo + hi ) >> 1;

                if ( nums.at(lo) < nums.at(mi) ) {
                    if ( nums.at(mi) < nums.at(hi) ) {
                        lo = mi + 1;
                    } else {
                        int new_lo = ( lo + mi ) >> 1;
                        int new_hi = ( mi + hi ) >> 1;

                        if ( nums.at(new_lo) > nums.at(mi) ) {
                            hi = mi - 1;
                        } else if ( nums.at(new_hi) > nums.at(mi) ) {
                            lo = mi + 1;
                        } else {
                            lo = new_lo + 1;
                            hi = new_hi - 1;
                        }
                    }
                } else {
                    hi = mi - 1;
                }
            }

            return nums.at(lo);
        }

        // assume the input array is non-empty:
        return nums.at(0);
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,2,3,4,3,2,1};
    std::cout << ( 4 == solution.mountainSequence(nums1) ) << std::endl;

    std::vector<int> nums2 {10, 9, 8, 7};
    std::cout << ( 10 == solution.mountainSequence(nums2) ) << std::endl;

    return EXIT_SUCCESS;
}