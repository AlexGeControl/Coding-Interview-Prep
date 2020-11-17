#include <cstdlib>
#include <iostream>

#include <vector>

class Solution {
public:
    static const int RED = 0;
    static const int WHITE = 1;
    static const int BLUE = 2;
    
    /**
     * @param nums: A list of integer which is 0, 1 or 2 
     * @return: nothing
     */
    void sortColors(std::vector<int> &nums) {
        const int N = nums.size();
        
        int lo = 0, curr = 0, hi = N - 1;
        
        while ( curr <= hi ) {
            if ( RED == nums.at(curr) ) {
                swap(nums, lo, curr);
                // after swap, the value under curr could only be blue;
                ++lo;
                ++curr;
            } else if ( BLUE == nums.at(curr) ) {
                swap(nums, hi, curr);
                --hi;
            } else {
                ++curr;
            }
        }
    }
private:
    void swap(std::vector<int> &nums, int i, int j) {
        if ( i != j ) {
            int color = nums.at(i);
            nums.at(i) = nums.at(j);
            nums.at(j) = color;
        }
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {2,0,2,2,1,2,2,1,2,0,0,0,1};
    solution.sortColors(nums1);

    for (const int &num: nums1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<int> nums2 {2,0,0,1,2,0,2};
    solution.sortColors(nums2);

    for (const int &num: nums2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<int> nums3 {0,2,2,2,2,1,0,1,0,0,0,1,0,2,0};
    solution.sortColors(nums3);

    for (const int &num: nums3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}