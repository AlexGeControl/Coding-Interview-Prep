#include <iostream>
#include <string>

class Solution {
public:
    /**
     * @param str: A string
     * @param left: a left offset
     * @param right: a right offset
     * @return: return a rotate string
     */
    std::string RotateString2(const std::string &str, int left, int right) {
        const int N = str.size();

        if ( left != right ) {
            int rotate_amount = left - right;

            if ( 0 < rotate_amount ) {
                rotate_amount = rotate_amount % N;

                if (0 < rotate_amount) {
                    return str.substr(rotate_amount, N - rotate_amount) + str.substr(0, rotate_amount);
                }
            } else {
                rotate_amount = (-rotate_amount) % N;

                if (0 < rotate_amount) {
                    return str.substr(N - rotate_amount, rotate_amount) + str.substr(0, N - rotate_amount);
                }
            }
        }

        return str;
    }
};

int main() {
    //
    // test case 01:
    //
    std::string input = "abcdefg";

    Solution solution;

    std::cout << solution.RotateString2(input, 3, 1) << std::endl;
    std::cout << solution.RotateString2(input, 0, 0) << std::endl;
    std::cout << solution.RotateString2(input, 1, 2) << std::endl;

    return EXIT_SUCCESS;
}