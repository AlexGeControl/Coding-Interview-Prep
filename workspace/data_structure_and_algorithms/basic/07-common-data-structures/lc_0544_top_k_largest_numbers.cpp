#include <cstdlib>
#include <iostream>

#include <vector>

#include <algorithm>

class Solution {
public:
    /**
     * @param nums: an integer array
     * @param k: An integer
     * @return: the top k largest numbers in array
     */
    std::vector<int> topk(std::vector<int> &nums, const int k) {
        std::vector<int> result;

        const int N = nums.size();

        if ( 0 < N && 0 < k ) {
            if ( k < N ) {
                int lo = 0, hi = N - 1;

                while ( lo < hi ) {
                    int idx = partition(nums, lo, hi);

                    if ( N - k == idx ) break;

                    if ( idx < N - k ) {
                        lo = idx + 1;
                    } else {
                        hi = idx - 1;
                    }
                }

                for (int i = N - k; i < N; ++i) {
                    result.push_back(nums.at(i));
                }
            } else {
                result.insert(result.end(), nums.begin(), nums.end());
            }

            std::sort(result.begin(), result.end(), [](int x, int y) { return x > y; } );
        } 

        return result;
    }
private:
    static void swap(std::vector<int> &nums, const int i, const int j) {
        if ( i != j ) {
            int val = nums.at(i);
            nums.at(i) = nums.at(j);
            nums.at(j) = val;
        }
    }

    static int setPartitionKey(std::vector<int> &nums, const int lo, const int hi) {
        // here assumes that there are at least 3 elements:
        int mi = (lo + hi) / 2;

        if ( nums.at(lo) > nums.at(mi) ) swap(nums, lo, mi);
        if ( nums.at(mi) > nums.at(hi) ) swap(nums, mi, hi);
        if ( nums.at(lo) > nums.at(mi) ) swap(nums, lo, mi);

        // move partition key to hi:
        swap(nums, mi, hi);

        return nums.at(hi);
    }

    static int partition(std::vector<int> &nums, const int lo, const int hi) {
        if ( lo < hi ) {
            if ( hi == lo + 1) {
                if ( nums.at(lo) > nums.at(hi) ) swap(nums, lo, hi);
            } else {
                int key = setPartitionKey(nums, lo, hi);

                int begin = lo - 1, end = hi;

                while ( begin < end ) {
                    while ( nums.at(++begin) < key ) {
                        if ( hi == begin ) break;
                    }

                    while ( nums.at(--end) > key ) {
                        if ( lo == end ) break;
                    }

                    if ( begin >= end ) break;

                    swap(nums, begin, end);
                }
                swap(nums, begin, hi);

                return begin;
            }
        }

        return hi;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {
        3, 10, 1000, -99, 4, 100
    };
    int k1 = 3;
    for (const int num: solution.topk(nums1, k1)) {
        std::cout << num << " " << std::endl;
    }

    std::vector<int> nums2 {
        8, 7, 6, 5, 4, 3, 2, 1, 7, 8
    };
    int k2 = 5;
    for (const int num: solution.topk(nums2, k2)) {
        std::cout << num << " " << std::endl;
    }

    return EXIT_SUCCESS;
}