#include <iostream>

#include <string>

#include <vector>

class Solution {
public:
    /**
     * @param word1: A string
     * @param word2: A string
     * @return: The minimum number of steps.
     */
    int minDistance(const std::string &wordA, const std::string &wordB) {
        const int N = wordA.size();
        const int M = wordB.size();

        if ( 0 == N || 0 == M ) { return std::max(N, M); }

        // build DP table:
        std::vector<std::vector<int>> dp_table(
            2, 
            std::vector<int>(M + 1, 0)
        );

        // a. init:
        for ( int m = 0; m <= M; ++m ) {
            // if word A is empty, the edit distance would equal to the length of word B:
            dp_table[0][m] = m;
        }

        // b. dynamic planning using rolling table:
        for ( int n = 1; n <= N; ++n ) {
            const int prev = ( n - 1 ) % 2;
            const int curr = ( n + 0 ) % 2;

            // the edit distance between word A and empty string is always wordA.size():
            dp_table[curr][0] = n;

            // only modify sub string of word A:
            for ( int m = 1; m <= M; ++m ) {
                // current two chars are the same: 
                if ( wordA.at(n - 1) == wordB.at(m - 1) ) {
                    dp_table[curr][m] = std::min(
                        // 1. do nothing:
                        dp_table[prev][m - 1],
                        std::min(
                            // 2. add:
                            dp_table[curr][m - 1] + 1, 
                            // 3. delete: 
                            dp_table[prev][m] + 1
                        )
                    );
                // current two chars are different:
                } else {
                    dp_table[curr][m] = std::min(
                        // 1. replace:
                        dp_table[prev][m - 1] + 1,
                        std::min(
                            // 2. add:
                            dp_table[curr][m - 1] + 1,
                            // 3. delete:
                            dp_table[prev][m] + 1
                        )
                    );
                }
            }
        }

        return dp_table[N % 2][M];
    }
};

int main() {
    Solution solution;

    std::string wordA1("horse");
    std::string wordB1("ros");

    std::cout << solution.minDistance(wordA1, wordB1) << std::endl;

    return EXIT_SUCCESS;
}