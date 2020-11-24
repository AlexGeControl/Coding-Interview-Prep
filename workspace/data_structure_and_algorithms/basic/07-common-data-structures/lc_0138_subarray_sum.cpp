#include <iostream>

#include <vector>

#include <unordered_map>

class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number and the index of the last number
     */
    std::vector<int> subarraySum(std::vector<int> &nums) {
        // init result:
        std::vector<int> result;

        // init prefix sum lookup:
        std::unordered_map<int, int> prefix_sum_lookup;
        int prefix_sum = 0;

        const int N = nums.size();
        for (int i = 0; i < N; ++i) {
            prefix_sum += nums.at(i);

            if ( 0 == prefix_sum ) {
                result.push_back( 0 );
                result.push_back( i );
                break;   
            }

            if ( prefix_sum_lookup.end() == prefix_sum_lookup.find(prefix_sum) ) {
                prefix_sum_lookup[prefix_sum] = i;
            } else {
                result.push_back( prefix_sum_lookup.at(prefix_sum) + 1 );
                result.push_back( i );
                break;
            }
        } 

        return result;  
    }
};

int main() {
    Solution solution;

    std::vector<int> nums1 {-3, 1, 2, -3, 4};
    for (const int &index: solution.subarraySum(nums1)) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    std::vector<int> nums2 {-3, 1, -4, 2, -3, 4};
    for (const int &index: solution.subarraySum(nums2)) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}