#include <cstdlib>
#include <vector>

#include <unordered_map>
#include <unordered_set>

#include <iostream>

class Solution {
public:
    /**
     * @param num: A list of integers
     * @return: An integer
     */
    int longestConsecutive(std::vector<int> &nums) {
        int max_length = 0;

        if ( 0 < nums.size() ) {
            max_length = 1;

            std::unordered_map<int, Seq> seqs;
            for (const int num: nums) {
                if ( seqs.end() == seqs.find(num) ) {
                    seqs[num] = Seq(num, num);

                    const int prev = num - 1;
                    const int next = num + 1;

                    if ( seqs.end() != seqs.find(prev) ) seqs.at(num).begin = seqs.at(prev).begin;
                    if ( seqs.end() != seqs.find(next) ) seqs.at(num).end = seqs.at(next).end;

                    if ( seqs.end() != seqs.find(prev) ){
                        seqs.at(seqs.at(prev).begin).end = seqs.at(prev).end = seqs.at(num).end;
                    }

                    if ( seqs.end() != seqs.find(next) ) {
                        seqs.at(seqs.at(next).end).begin = seqs.at(next).begin = seqs.at(num).begin;
                    }

                    max_length = std::max(max_length, seqs.at(num).end - seqs.at(num).begin + 1);
                }
            }
        }

        return max_length;
    }
private:
    struct Seq {
        int begin;
        int end;

        Seq() {}

        Seq(const int b, const int e): begin(b), end(e) {}
    };
};

int main() {
    Solution solution;

    std::vector<int> nums1 {
        100, 4, 200, 1, 3, 2
    };

    std::cout << (4 == solution.longestConsecutive(nums1) ) << std::endl << std::endl;

    std::vector<int> nums2 {
        3,1,4,1,5,9,2,6,5
    };

    std::cout << (6 == solution.longestConsecutive(nums2) ) << std::endl << std::endl;

    return EXIT_SUCCESS;
}