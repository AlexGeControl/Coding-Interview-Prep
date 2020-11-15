#include <iostream>
#include <string>

class Solution {
public:
    static const int NOT_FOUND = -1;

    /**
     * @param source: 
     * @param target: 
     * @return: return the index
     */
    int strStr(std::string &source, std::string &target) {
        const int N = source.size();
        const int M = target.size();
        
        if ( 0 == M ) return 0; 
        
        if (
            // both are not empty and target size is not greater than source size:
            0 < N && 0 < M && M <= N
        ) {
            const char &first_char_target = target.at(0);

            for (int i = 0; i < N; ++i) {
                if (first_char_target == source.at(i)) {
                    int j = 1;

                    while (j < M && i + j < N && source.at(i + j) == target.at(j)) ++j;

                    if (M == j) return i;
                }
            }
        }

        return NOT_FOUND;
    }
};

int main() {
    //
    // test case 01:
    //
    std::string source = "abcdabcdefg", target = "bcd";

    Solution solution;

    std::cout << solution.strStr(source, target) << std::endl;

    return EXIT_SUCCESS;
}