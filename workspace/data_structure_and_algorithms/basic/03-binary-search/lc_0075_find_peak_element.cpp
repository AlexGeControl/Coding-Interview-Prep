#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param A: An integers array.
     * @return: return any of peek positions.
     */
    int findPeak(const std::vector<int> &A) {
        const int N = A.size();

        int lo = 0, hi = N - 1;

        while ( lo <= hi ) {
            int mi = (lo + hi) >> 1;

            if ( hi == lo + 1 ) break;

            if ( A.at(lo) >= A.at(mi) ) {
                hi = mi;
            } else if ( A.at(mi) <= A.at(hi) ) {
                lo = mi;
            } else {
                int new_lo = (lo + mi) >> 1;
                int new_hi = (hi + mi) >> 1;

                if ( A.at( new_lo ) >= A.at(mi) ) {
                    hi = mi;
                } else if ( A.at(mi) <= A.at( new_hi ) ){
                    lo = mi;
                } else {
                    lo = (lo + mi) >> 1;
                    hi = (hi + mi) >> 1;
                }
            }
        }

        return A.at(lo) < A.at(hi) ? hi : lo;
    }
};


int main() {
    Solution solution;

    std::vector<int> A1 {1, 2, 1, 3, 4, 5, 7, 6};

    std::cout << solution.findPeak(A1) << std::endl << std::endl;

    std::vector<int> A2 {1,2,3,4,1};

    std::cout << solution.findPeak(A2) << std::endl << std::endl;

    std::vector<int> A3 {
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
    };

    std::cout << solution.findPeak(A3) << std::endl << std::endl;

    return EXIT_SUCCESS;
}