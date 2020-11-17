#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param A: an integer array
     * @param target: An integer
     * @param k: An integer
     * @return: an integer array
     */
    std::vector<int> kClosestNumbers(const std::vector<int> &A, const int target, const int k) {
        const int N = A.size();

        std::vector<int> k_closest_numbers;

        if ( 0 < N && 0 < k ) {
            if ( k <= N ) {
                int lo = 0, hi = N - 1;

                // first, identify the interval which contains target, O(logN):
                while ( lo <= hi ) {
                    int mi  = ( lo + hi ) >> 1;

                    if ( target == A.at(mi) ) {
                        lo = hi = mi;
                        break;
                    }

                    if ( target < A.at(mi) ) {
                        hi = mi - 1;
                    } else {
                        lo = mi + 1;
                    }
                }

                // init two pointers, O(1):
                if ( lo > hi ) {
                    // find the interval contains target:
                    int position = hi;
                    hi = lo;
                    lo = position;
                } else {
                    // target is inside A, now we continue to find the remaining k - 1 elements:
                    k_closest_numbers.push_back(target);

                    --lo, ++hi;
                }

                // identify the k closest elements, O(k):
                while ( static_cast<size_t>(k) > k_closest_numbers.size() ) {
                    if ( lo < 0 && hi < N) {
                        k_closest_numbers.push_back(A.at(hi++));
                    } 

                    if ( N <= hi && 0 <= lo ) {
                        k_closest_numbers.push_back(A.at(lo--));
                    }

                    if (
                        0 <= lo && hi < N
                    ) {
                        int lo_deviation = std::abs(A.at(lo) - target);
                        int hi_deviation = std::abs(A.at(hi) - target);

                        if ( lo_deviation <= hi_deviation ) {
                            k_closest_numbers.push_back(A.at(lo--));
                        } else {
                            k_closest_numbers.push_back(A.at(hi++));
                        }
                    }
                }
            } else {
                k_closest_numbers.insert(k_closest_numbers.end(), A.begin(), A.end());
            }
        }

        return k_closest_numbers;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1, 2, 3};
    int target1 = 2;
    int k1 = 3;

    std::vector<int> k_closest_numbers1 = solution.kClosestNumbers(nums1, target1, k1);
    for (const int &num: k_closest_numbers1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<int> nums2 {1, 4, 6, 8};
    int target2 = 3;
    int k2 = 3;

    std::vector<int> k_closest_numbers2 = solution.kClosestNumbers(nums2, target2, k2);
    for (const int &num: k_closest_numbers2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}