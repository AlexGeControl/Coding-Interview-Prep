#include <iostream>

#include <string>

#include <vector>

class Solution {
public:
    /**
     * @param s: A string 
     * @param p: A string includes "?" and "*"
     * @return: is Match?
     */
    bool isMatch(
        const std::string &s, 
        const std::string &p
    ) {
        if ( s.empty() ) return p.empty() || "*" == p;

        if ( p.empty() ) return false;

        const int N = s.size();
        const int M = p.size();

        // init cache:
        std::vector<std::vector<bool>> cache(
            N + 1, 
            std::vector<bool>(M + 1, false)
        );
        cache[0][0] = true;

        int n = 1, m = 1;

        while ( n <= N || m <= M ) {
            while ( m <= M && '*' == p.at(m - 1) ) {
                int i = 0;
                while ( i <= N && !cache[i][m - 1] ) ++i;

                if (i > N) return false;

                for ( ; i <= N; ++i ) cache[i][m] = true;

                ++m;
            }

            while ( n <= N && '*' == s.at(n - 1) ) {
                int j = 0;
                while ( j <= M && !cache[n - 1][j] ) ++j;

                if (j > M) return false;

                for ( ; j <= M; ++j) cache[n][j] = true;

                ++n;
            }

            if ( m <= M ) {
                for ( int i = n; i <= N; ++i ) {
                    if ( cache[i - 1][m - 1] ) {
                        cache[i][m] = isEqual(s.at(i - 1), p.at(m - 1));
                    }
                }
                ++m;
            }

            if ( n <= N ) {
                for ( int j = m; j <= M; ++j ) {
                    if ( cache[n - 1][j - 1] ) {
                        cache[n][j] = isEqual(p.at(j - 1), s.at(n - 1));
                    }
                }
                ++n;
            }            
        }

        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= M; ++j) {
                std::cout << cache[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        return cache[N][M];
    }
private:
    static bool isEqual(const char s, const char p) {
        return !( 
            '*' != s && '?' != s && 
            '?' != p && 
            s != p
        );
    }
};

int main() {
    Solution solution;

    const std::string s1("aa");
    const std::string p1("*");

    std::cout << ( true == solution.isMatch(s1, p1) ) << std::endl;

    return EXIT_SUCCESS;
}