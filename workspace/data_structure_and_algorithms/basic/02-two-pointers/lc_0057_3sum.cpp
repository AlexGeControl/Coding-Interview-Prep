#include <iostream>

#include <vector>
#include <unordered_set>

#include <algorithm>

class Solution {
public:
    /**
     * @param numbers: Give an array numbers of n integer
     * @return: Find all unique triplets in the array which gives the sum of zero.
     */
    std::vector<std::vector<int>> threeSum(const std::vector<int> &numbers) {
        std::vector<std::vector<int>> result;

        const int N = numbers.size();

        if ( 3 <= N ) {
            // first, sort input numbers, O(N * log(N)):
            std::vector<int> sorted_numbers = numbers;
            std::sort(sorted_numbers.begin(), sorted_numbers.end());

            // then solve N two-sum problem, O(N**2):
            for (int i = 0; i < N; ++i) {
                while ( 
                    0 < i && 
                    ( i < N && sorted_numbers.at(i - 1) == sorted_numbers.at(i) )
                ) {
                    ++i;
                }

                if ( N == i ) break;

                twoSum(sorted_numbers, i, result);
            }
        }

        return result;
    }
private:
    void twoSum(
        const std::vector<int> &sorted_numbers,
        const int a_index,
        std::vector<std::vector<int>> &result
    ) {
        const int N = sorted_numbers.size();
        const int SUM = 0 - sorted_numbers.at(a_index);

        int b_index = a_index + 1, c_index = N - 1;

        while ( b_index < c_index ) {
            if ( SUM - sorted_numbers.at(c_index) < sorted_numbers.at(b_index) ) {
                --c_index;
            } else if ( sorted_numbers.at(b_index) < SUM - sorted_numbers.at(c_index) ) {
                ++b_index;
            } else {
                // find one candidate: add to output:
                std::vector<int> tuple {
                    sorted_numbers.at(a_index), 
                    sorted_numbers.at(b_index), 
                    sorted_numbers.at(c_index)
                };
                // add to output:
                result.push_back(tuple);
                // get ready for next check:
                ++b_index; --c_index;

                // skip duplicate items:
                while ( 
                    b_index < c_index &&
                    sorted_numbers.at(b_index - 1) == sorted_numbers.at(b_index)
                ) {
                    ++b_index;
                }
                while ( 
                    b_index < c_index &&
                    sorted_numbers.at(c_index + 1) == sorted_numbers.at(c_index)
                ) {
                    --c_index;
                }
            }
        }
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {-1,0,1,2,-1,-4};
    for ( const auto &tuple: solution.threeSum(nums1) ) {
        std::cout << tuple.at(0) << ", " << tuple.at(1) << ", " << tuple.at(2) << std::endl;
    }
    
    std::vector<int> nums2 {1,0,-1,-1,-1,-1,0,1,1,1};
    for ( const auto &tuple: solution.threeSum(nums2) ) {
        std::cout << tuple.at(0) << ", " << tuple.at(1) << ", " << tuple.at(2) << std::endl;
    }

    return EXIT_SUCCESS;
}