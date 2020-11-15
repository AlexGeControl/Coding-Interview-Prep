#include <iostream>
#include <string>

class Solution {
public:
    /**
     * @param s: a string which consists of lowercase or uppercase letters
     * @return: the longest palindrome substring
     */
    std::string longestPalindrome(const std::string &s) {
        const int N = s.size();

        if (1 < N) {
            // case 1: two-char string
            if ( 2 == N ) {
                if ( s.at(0) != s.at(1) ) return s.substr(0, 1);
            // case 2: at least 3 chars:
            } else {
                int pos = 0;
                int substr_len, len = 1;

                for (int i = 1; i < N - 1; ++i) {
                    if ( s.at(i) == s.at(i - 1) ) {
                        substr_len = getPalindromeSize(s, i - 1, i);

                        if ( len < substr_len ) {
                            pos = i - (substr_len >> 1);
                            len = substr_len;
                        }
                    }

                    if ( s.at(i) == s.at(i + 1) ) {
                        substr_len = getPalindromeSize(s, i, i + 1);

                        if ( len < substr_len ) {
                            pos = i - (substr_len >> 1) + 1;
                            len = substr_len;
                        }
                    }

                    substr_len = getPalindromeSize(s, i);

                    if ( len < substr_len ) {
                        pos = i - (substr_len >> 1);
                        len = substr_len;
                    }
                }

                return s.substr(pos, len);
            }
        }

        //
        // case 3: empty, 1-char and 2-same-char string
        //
        return s;
    }

private:
    int getPalindromeSize(const std::string &s, int center_left, int center_right) {
        const int N = s.size();

        int size = 0;

        while (
            0 <= center_left && center_right < N && 
            s.at(center_left) == s.at(center_right)
        ) {
            size += 2;

            --center_left;
            ++center_right;
        }

        return size;
    }

    int getPalindromeSize(const std::string &s, int center) {
        const int N = s.size();

        int size = 1;

        int center_left = center - 1, center_right = center + 1;
        while (
            0 <= center_left && center_right < N && 
            s.at(center_left) == s.at(center_right)
        ) {
            size += 2;

            --center_left;
            ++center_right;
        }

        return size;
    }
};

int main() {
    //
    // test case 01:
    //
    std::string input = "abcdzdcab";

    Solution solution;

    std::cout << solution.longestPalindrome(input) << std::endl;

    return EXIT_SUCCESS;
}