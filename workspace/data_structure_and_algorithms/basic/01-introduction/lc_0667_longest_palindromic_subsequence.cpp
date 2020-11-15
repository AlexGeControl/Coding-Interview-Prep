#include <iostream>
#include <string>

class Solution {
public:
    /**
     * @param s: the maximum length of s is 1000
     * @return: the longest palindromic subsequence's length
     */
    int longestPalindromeSubseq(const std::string &s) {
        return 0;
    }
};

int main() {
    //
    // test case 01:
    //
    std::string input = "bbbab";

    Solution solution;

    std::cout << solution.longestPalindromeSubseq(input) << std::endl;

    return EXIT_SUCCESS;
}