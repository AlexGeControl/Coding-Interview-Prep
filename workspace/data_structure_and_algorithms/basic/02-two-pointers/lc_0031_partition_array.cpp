#include <cstdlib>
#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param nums: The integer array you should partition
     * @param k: An integer
     * @return: The index after partition
     */
    int partitionArray(std::vector<int> &nums, int k) {
        const int N = nums.size();

        int partition_index = 0;

        if (0 < N) {
            int lo = -1, hi = N;

            while (lo < hi) {
                while ( nums.at(++lo) < k ) {
                    if ( N - 1 == lo ) {
                        return N;
                    }
                }

                while ( nums.at(--hi) >= k ) {
                    if ( 0 == hi ) {
                        return 0;
                    }
                }
                
                if ( lo >= hi) {
                    partition_index = hi + 1;
                    break;
                }

                swap(nums, lo, hi);
            }
        }

        return partition_index;
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

    std::vector<int> nums1 {6,6,8,6,7,9,8,7,9,6,8,6,8,9,8,7,8,6,7,6,6,8,6,6};
    int k1 = 5;

    std::cout << solution.partitionArray(nums1, k1) << std::endl;

    return EXIT_SUCCESS;
}