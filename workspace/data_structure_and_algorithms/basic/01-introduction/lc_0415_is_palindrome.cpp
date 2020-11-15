#include <iostream>

#include <string>
#include <ctype.h>
#include <vector>

class Solution {
public:
    /**
     * @param s: A string
     * @return: Whether the string is a valid palindrome
     */
    bool isPalindrome(std::string &s) {
        const int N = s.size();

        if (0 < N) {
            // pre-process: keep only alpha and digit
            std::vector<char> s_processed;
            for (int i = 0; i < N; ++i) {
                const char &c = s.at(i);

                if (
                    isalpha(c) || isdigit(c)
                ) {
                    s_processed.push_back(isupper(c) ? tolower(c) : c);
                }
            }

            // palindrome check:
            const int M = s_processed.size();
            if (0 < M) {
                bool should_start_from_center = ( 1 == (M % 2));
                int center =  (M >> 1);

                if (should_start_from_center) {
                    return isPalindrome(s_processed, center); 
                } else {
                    return isPalindrome(s_processed, center - 1, center);
                }
            }
        }
        
        return true;
    }
private:
    bool isPalindrome(const std::vector<char> &s, int center) {
        const int N = s.size();

        int left = center - 1, right = center + 1;

        while (
            0 <= left && right < N 
        ) {
            if (s.at(left) != s.at(right) ) return false;

            --left;
            ++right;
        }

        return true;
    }

    bool isPalindrome(const std::vector<char> &s, int left, int right) {
        const int N = s.size();

        while (
            0 <= left && right < N 
        ) {
            if (s.at(left) != s.at(right) ) return false;

            --left;
            ++right;
        }

        return true;
    }
};

int main() {
    //
    // test case 01:
    //
    std::string input = "A man, a plan, a canal: Panama";

    Solution solution;

    std::cout << solution.isPalindrome(input) << std::endl;

    return EXIT_SUCCESS;
}