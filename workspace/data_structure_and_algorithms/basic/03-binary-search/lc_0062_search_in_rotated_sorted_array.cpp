#include <iostream>

#include <vector>

class Solution {
public:
    static const int NOT_FOUND = -1;

    /**
     * @param A: an integer rotated sorted array
     * @param target: an integer to be searched
     * @return: an integer
     */
    int search(const std::vector<int> &A, const int target) {
        const int N = A.size();

        if ( 0 < N ) {
            // first, identify the correct boundary of sorted array:
            int lo = 0, hi = N - 1;

            while ( lo < hi ) {
                int mi = (lo + hi) >> 1;

                if ( A.at(lo) > A.at(mi) ) {
                    hi = mi - 1;
                } else {
                    if ( A.at(mi) < A.at(hi) ) {
                        lo = mi + 1;
                    } else {
                        int new_hi = (mi + hi) >> 1;

                        if ( A.at(mi) < A.at(new_hi) ) {
                            lo = mi + 1;
                        } else {
                            hi = mi;
                        }
                    }
                }
            }

            // then create ArrayWithOffset:
            int offset = lo;
            ArrayWithOffset array_with_offset(A, offset + 1);

            // search in origin sorted array:
            lo = 0, hi = N - 1;

            while ( lo <= hi ) {
                int mi = (lo + hi) >> 1;

                if ( target == array_with_offset.getValue(mi) ) {
                    return array_with_offset.getIndex(mi);
                } else if ( target < array_with_offset.getValue(mi) ) {
                    hi = mi - 1;
                } else {
                    lo = mi + 1;
                }
            }
        }

        return NOT_FOUND;
    }
private:
    class ArrayWithOffset {
    public:
        ArrayWithOffset(const std::vector<int> &A, const int offset) : A_(A), offset_(offset) {
            N_ = A_.size();
        }
        int getValue(int i) const {
            return A_.at( (offset_ + i) % N_ );
        }
        int getIndex(int i) const {
            return (offset_ + i) % N_;
        }
    private:
        const std::vector<int> &A_;
        int N_;
        int offset_;
    };
};

int main() {
    Solution solution;

    std::vector<int> nums1 {4, 5, 1, 2, 3};
    int target1 = 1;

    std::cout << ( 2 == solution.search(nums1, target1) ) << std::endl;

    std::vector<int> nums2 {4, 5, 1, 2, 3};
    int target2 = 0;

    std::cout << ( Solution::NOT_FOUND == solution.search(nums2, target2) ) << std::endl;

    return EXIT_SUCCESS;
}