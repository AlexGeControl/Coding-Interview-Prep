#include <iostream>

#include <string>

#include <unordered_set>

class Solution {
public:
    /**
     * @param s: A string 
     * @param p: A string includes "." and "*"
     * @return: A boolean
     */
    bool isMatch(
        const std::string &s, 
        const std::string &p
    ) {
        if ( s.empty() ) return p.empty() || ( 2 == p.size() && '*' == p.back() );
        if ( p.empty() ) return false;

        const int N = s.size();
        const int M = p.size();

        // init cache:
        std::unordered_set<int> cache;
        cache.insert(getID(N, M, 0, 0));

        int n = 1, m = 1;
        while ( m <= M ) {
            while ( n <= N && m <= M - 1 && '*' == p.at(m) ) {
                int k = n - 1;

                while ( 
                    k <= N && 
                    ( 1 == m || cache.end() != cache.find(getID(N, M, k, m - 1)) ) && 
                    ( n - 1 == k || !isEqual(s.at(k - 1), p.at(m - 1)) )
                ) {
                    cache.insert(getID(N, M, k, m + 0));
                    cache.insert(getID(N, M, k, m + 1));
                    ++k;
                }

                while (
                    k <= N &&
                    ( 1 == m || cache.end() != cache.find(getID(N, M, k - 1, m - 1))) &&
                    isEqual(s.at(k - 1), p.at(m - 1))
                ) {
                    cache.insert(getID(N, M, k, m + 0));
                    cache.insert(getID(N, M, k, m + 1));
                    ++k;
                }

                m += 2;
            }

            if ( m > M ) break;

            if ( n <= N ) {
                for ( int k = n; k <= N; ++k ) {
                    if ( 
                        cache.end() != cache.find(getID(N, M, k - 1, m - 1)) &&
                        isEqual(s.at(k - 1), p.at(m - 1))
                    ) {
                        cache.insert(getID(N, M, k, m));
                    }
                }
                ++n;
            }

            ++m;
        } 

        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= M; ++j) {
                std::cout << (cache.end() != cache.find(getID(N, M, i, j))) << " ";
            }
            std::cout << std::endl;
        }

        return cache.end() != cache.find(getID(N, M, N, M));
    }
private:
    static int getID(
        const int N, const int M,
        const int n, const int m
    ) {
        return n * (M + 1) + m;
    }

    static bool isEqual(
        const char s,
        const char p
    ) {
        return s == p || '.' == p;
    }
};

int main() {
    Solution solution;

    const std::string s1("aa");
    const std::string p1("a*");

    std::cout << ( true == solution.isMatch(s1, p1) ) << std::endl;

    const std::string s2("abab");
    const std::string p2("a*b*");

    std::cout << ( false == solution.isMatch(s2, p2) ) << std::endl;

    return EXIT_SUCCESS;
}