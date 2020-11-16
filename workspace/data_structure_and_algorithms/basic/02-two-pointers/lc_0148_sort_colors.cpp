#include <cstdlib>
#include <iostream>

#include <vector>

class Solution {
public:
    static const int RED = 0;
    static const int WHITE = 1;
    static const int BLUE = 2;

    /**
     * @param nums: A list of integer which is 0, 1 or 2 
     * @return: nothing
     */
    void sortColors(std::vector<int> &nums) {
        /*
         * Option 1: partition & bubble sorting
        const int PARTITION_KEY = WHITE;
        const int N = nums.size();

        if ( 0 < N ) {
            int lo = -1, hi = N;

            while ( lo < hi ) {
                while ( nums.at(++lo) < PARTITION_KEY ) {
                    if ( N - 1 == lo ) return;
                }

                while ( nums.at(--hi) >= PARTITION_KEY ) {
                    ensureOrder(nums, hi);
                    if ( 0 == hi ) return;
                }

                if ( lo >= hi ) break;

                swap(nums, lo, hi);
                ensureOrder(nums, hi);
            }
        }
        */

        const int PARTITION_KEY = WHITE;
        const int N = nums.size();

        if ( 0 < N ) {
            int lo = -1, hi = N;
            int white_count = 0;

            while ( lo < hi ) {
                while ( nums.at(++lo) < PARTITION_KEY ) {
                   if ( lo == N - 1 ) break; 
                }
                
                while ( nums.at(--hi) >= PARTITION_KEY ) {
                    white_count += coverWhiteWithBlue(nums, hi);
                    if ( 0 == hi ) break;
                }

                if (lo >= hi) break;

                swap(nums, lo, hi);
                white_count += coverWhiteWithBlue(nums, hi);
            }
            
            std::cout << lo << ", " << hi << std::endl;

            if ( 0 < white_count) {
                if ( 0 == hi ) hi = -1;
                for (int i = 0; i < white_count; ++i) {
                    nums.at(hi + 1 + i) = WHITE;
                }
            }
        }
    }
private:
    void swap(std::vector<int> &nums, int i, int j) {
        int value = nums.at(i);
        nums.at(i) = nums.at(j);
        nums.at(j) = value;
    }

    void ensureOrder(std::vector<int> &nums, int hi) {
        const int N = nums.size();
        while ( 
            hi < N - 1 &&
            BLUE == nums.at(hi) && WHITE == nums.at(hi + 1)
        ) {
            swap(nums, hi, hi + 1);
            ++hi;
        }
    }

    int coverWhiteWithBlue(std::vector<int> &nums, int i) {
        if ( WHITE == nums.at(i) ) {
            nums.at(i) = BLUE;
            return 1;
        }

        return 0;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums {2,0,2,2,1,2,2,1,2,0,0,0,1};
    solution.sortColors(nums);

    for (const int &num: nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}