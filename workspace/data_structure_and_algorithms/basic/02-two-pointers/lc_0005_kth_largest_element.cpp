#include <cstdlib>
#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param n: An integer
     * @param nums: An array
     * @return: the Kth largest element
     */
    int kthLargestElement(std::vector<int> &nums, int k) {
        const int N = nums.size();
        
        // transform to the kth smallest element:
        k = N + 1 - k;

        // use fast selection based on partition:
        int lo = 0, hi = N - 1;
        while ( lo <= hi ) {
            if ( lo == hi ) return nums.at(lo);

            int partition_index = getPartitionIndex(nums, lo, hi);

            if ( k - 1 == partition_index ) break;

            if ( partition_index < k - 1 ) {
                lo = partition_index + 1;
            } else {
                hi = partition_index - 1;
            }
        }
        
        return nums.at(k - 1);
    }
private:
    inline void setLastValueAsPartitionKey(std::vector<int> &nums, int lo, int hi) {
        int mi = ( lo + hi ) / 2;

        if ( lo < mi && nums.at(lo) > nums.at(mi) ) swap(nums, lo, mi);
        if ( mi < hi && nums.at(mi) > nums.at(hi) ) swap(nums, mi, hi);
        if ( lo < mi && nums.at(lo) > nums.at(mi) ) swap(nums, lo, mi);

        // set partition key as the last element:
        if ( mi < hi ) swap(nums, mi, hi);
    }

    int getPartitionIndex(std::vector<int> &nums, int lo, int hi) {
        setLastValueAsPartitionKey(nums, lo, hi);

        if ( hi == lo + 1 ) {
            swap(nums, lo, hi);
            return lo;
        } else if ( hi == lo + 2 ) {
            swap(nums, hi - 1, hi);
            return hi - 1;
        } 
        
        const int partition_key = nums.at(hi);

        int left = lo - 1, right = hi;
        while ( left < right ) {
            while ( nums.at(++left) < partition_key ) {
                if ( hi == left ) return hi + 1;
            }

            while ( nums.at(--right) >= partition_key ) {
                if ( lo == right ) return lo;
            }

            if ( left >= right) break;

            swap(nums, left, right);
        }

        int partition_index = right + 1;

        swap(nums, partition_index, hi);

        return partition_index;
    }

    void swap(std::vector<int> &nums, int i, int j) {
        int value = nums.at(i);
        nums.at(i) = nums.at(j);
        nums.at(j) = value;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,3,4,2};
    int k1 = 1;

    std::cout << (4 == solution.kthLargestElement(nums1, k1)) << std::endl;

    std::vector<int> nums2 {9,3,2,4,8};
    int k2 = 3;

    std::cout << (4 == solution.kthLargestElement(nums2, k2)) << std::endl;

    return EXIT_SUCCESS;
}