#include <iostream>
#include <unordered_map>

class Solution {
public:
    /**
     * @param s: a string which consists of lowercase or uppercase letters
     * @return: the length of the longest palindromes that can be built
     */
    int longestPalindrome(const std::string &s) {
        const int N = s.size();

        // build char count:
        std::unordered_map<char, int> char_counts;
        for (int i = 0; i < N; ++i) {
            const char &key = s.at(i);

            if (
                char_counts.end() == char_counts.find(key)
            ) {
                char_counts[key] = 0;
            }

            ++char_counts.at(key);
        }

        // get longest palindrome size:
        bool has_odd_count = false;
        int size = 0;
        for (const auto &key_value: char_counts) {
            int char_count = key_value.second;

            if ( 1 == (char_count % 2) ) {
                has_odd_count = true;
            }

            size += char_count - (char_count % 2);
        }

        return size + (has_odd_count ? 1 : 0);
    }
};

int main() {
    //
    // test case 01:
    //
    std::string input = "abccccdd";

    Solution solution;

    std::cout << solution.longestPalindrome(input) << std::endl;

    return EXIT_SUCCESS;
}