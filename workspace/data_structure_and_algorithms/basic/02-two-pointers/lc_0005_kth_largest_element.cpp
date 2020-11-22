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
    int kthLargestElement(int n, std::vector<int> &nums) {
        // convert the problem to Kth smallest element:
        const int N = nums.size();
        const int k = N - n;
        
        return getKthSmallestElement(nums, 0, N - 1, k);
    }
private:
    inline void swap(std::vector<int> &nums, int i, int j) {
        int value = nums.at(i);
        nums.at(i) = nums.at(j);
        nums.at(j) = value;
    }
    int partitionByMedian(std::vector<int> &nums, const int lo, const int hi) {
        // put estimated median to the last element of array:
        const int N = hi - lo + 1;
        const int mid_index = (lo + hi) >> 1;
        
        if ( nums.at(lo) > nums.at(mid_index) ) swap(nums, lo, mid_index);
        if ( nums.at(mid_index) > nums.at(hi) ) swap(nums, mid_index, hi);
        if ( nums.at(lo) > nums.at(mid_index) ) swap(nums, lo, mid_index);
        
        if ( 3 < N ) {
            swap(nums, mid_index, hi);
            
            const int partition_key = nums.at(hi);
            
            std::cout << "Partition by " << partition_key << std::endl;

            int left = lo - 1, right = hi;
            
            while ( left < right ) {
                while ( nums.at(++left) < partition_key ) {
                    if ( hi - 1 == left ) return hi;
                }
                
                while ( partition_key < nums.at(--right) ) {
                    if ( lo == right ) {
                        swap(nums, right, hi);
                        return right;
                    }
                }
                
                if ( left >= right ) {
                    swap(nums, left, hi);
                    return left;   
                }
                
                swap(nums, left, right);
            }
        }
        
        return mid_index;
    }
    int getKthSmallestElement(std::vector<int> &nums, const int lo, const int hi, const int k) {
        const int N = hi - lo + 1;
        
        if ( 1 == N ) {
            return nums.at(lo);
        } else if ( 2 == N ) {
            if ( nums.at(lo) > nums.at(hi) ) {
                swap(nums, lo, hi);
            }
            
            return ( 0 == k ? nums.at(lo) : nums.at(hi) ); 
        } else {
            int mid_index = partitionByMedian(nums, lo, hi);
            
            for (const int &num: nums) {
                std::cout << num << " ";
            }
            std::cout << " @ " << mid_index << ", " << k << std::endl;

            if ( k == mid_index ) {
                return nums.at(mid_index);
            } else if ( mid_index < k ) {
                return getKthSmallestElement(nums, mid_index + 1, hi, k);
            } else {
                return getKthSmallestElement(nums, lo, mid_index - 1, k);
            }
        }
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1,3,4,2};
    int k1 = 1;

    std::cout << (4 == solution.kthLargestElement(k1, nums1)) << std::endl;

    std::vector<int> nums2 {9,3,2,4,8};
    int k2 = 3;

    std::cout << (4 == solution.kthLargestElement(k2, nums2)) << std::endl;

    return EXIT_SUCCESS;
}