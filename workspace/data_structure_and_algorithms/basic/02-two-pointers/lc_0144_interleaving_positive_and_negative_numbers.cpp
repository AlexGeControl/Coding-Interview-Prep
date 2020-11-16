#include <cstdlib>
#include <iostream>

#include <vector>

class Solution {
public:
    /*
     * @param A: An integer array.
     * @return: nothing
     */
    void rerange(std::vector<int> &A) {
        // write your code here
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {-1, -2, -3, 4, 5, 6};
    solution.rerange(nums1);
    for (const int &num: nums1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}