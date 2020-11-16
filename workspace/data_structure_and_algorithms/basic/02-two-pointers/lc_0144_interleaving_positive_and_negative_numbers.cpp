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
        const int N = A.size();

        // fist, quick sort/partition the input array:
        int pos_index = partitionByZero(A);

        int num_pos = N - pos_index;
        int num_neg = N - num_pos;

        if ( num_neg <= num_pos ) {
            for (int i = 0; pos_index < N && i < N; i += 2, pos_index += 1) {
                swap(A, i, pos_index);
            }
        } else {
            for (int i = 1, j = N - 1; pos_index <= j && i < N; i += 2, j -= 2) {
                swap(A, i, j);
            }
        }
    }
private:
    int partitionByZero(std::vector<int> &A) {
        const int N = A.size();

        if ( 0 < N ) {
            int lo = -1, hi = N;

            while ( lo < hi ) {
                while (A.at(++lo) < 0 ) {
                    if ( N - 1 == lo ) return N;
                }

                while (A.at(--hi) > 0 ) {
                    if ( 0 == hi ) return 0;
                }

                if ( lo >= hi ) break;

                swap(A, lo, hi);
            }

            return hi + 1;
        }

        return 0;
    }

    inline void swap(std::vector<int> &A, int i, int j) {
        int value = A.at(i);
        A.at(i) = A.at(j);
        A.at(j) = value;
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

    std::vector<int> nums2 {-1, -2, -3, -4, 1, 2, 3};
    solution.rerange(nums2);
    for (const int &num: nums2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<int> nums3 {-1, -2, -3, 1, 2, 3, 4};
    solution.rerange(nums3);
    for (const int &num: nums3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}