#include <iostream>

#include <vector>

#include <unordered_map>

class Solution {
public:
    static const int NOT_FOUND = -1;

    /**
     * @param nums: a continuous stream of numbers
     * @param number: a number
     * @return: returns the first unique number
     */
    int firstUniqueNumber(std::vector<int> &nums, int number) {
        const int N = nums.size();

        // init state lookup:
        std::unordered_map<int, State> state_lookup;
        int i = 0;
        while ( i < N ) {
            // update state:
            if ( state_lookup.end() == state_lookup.find(nums.at(i)) ) {
                State state;

                state.index = i;
                state.repeated = false;

                state_lookup[nums.at(i)] = state;
            } else if ( !state_lookup.at(nums.at(i)).repeated ) {
                state_lookup.at(nums.at(i)).repeated = true;
            }

            if ( nums.at(i) == number ) {
                int first_non_repeated_value;
                int first_non_repeated_index = N;

                for (const auto &state: state_lookup) {
                    if ( !state.second.repeated && state.second.index < first_non_repeated_index) {
                        first_non_repeated_index = state.second.index;
                        first_non_repeated_value = state.first;
                    }
                }

                return first_non_repeated_value;
            }

            ++i;
        }

        return NOT_FOUND;
    }
private:
    struct State {
        int index;
        bool repeated;
    };
};

int main() {
    Solution solution;

    std::vector<int> nums1 {1, 2, 2, 1, 3, 4, 4, 5, 6};
    int signal1 = 5;

    std::cout << ( 3 == solution.firstUniqueNumber(nums1, signal1) ) << std::endl;

    std::vector<int> nums2 {1, 2, 2, 1, 3, 4, 4, 5, 6};
    int signal2 = 7;

    std::cout << ( Solution::NOT_FOUND == solution.firstUniqueNumber(nums2, signal2) ) << std::endl;

    std::vector<int> nums3 {1, 2, 2, 1, 3, 4};
    int signal3 = 3;

    std::cout << ( 3 == solution.firstUniqueNumber(nums3, signal3) ) << std::endl;

    return EXIT_SUCCESS;
}