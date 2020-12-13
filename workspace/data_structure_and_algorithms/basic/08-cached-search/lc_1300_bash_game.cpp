#include <cstdlib>
#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param n: an integer
     * @return: whether you can win the game given the number of stones in the heap
     */
    bool canWinBash(int n) {
        if ( n <= 3 ) return true;

        /*
        std::vector<bool> can_win_bash(4, true);

        for (int i = 3; i < n; ++i) {
            can_win_bash.at(i % 4) = (
                !can_win_bash.at( (i - 1) % 4 ) ||
                !can_win_bash.at( (i - 2) % 4 ) ||
                !can_win_bash.at( (i - 3) % 4 )
            );
        }

        return can_win_bash.at( (n - 1) % 4 );
        */

        return 0 != n % 4;     
    }
};

int main() {
    Solution solution;

    int n1 = 4;
    std::cout << ( false == solution.canWinBash(n1) ) << std::endl;

    int n2 = 5;
    std::cout << ( true == solution.canWinBash(n2) ) << std::endl;

    int n3 = 40000000;
    std::cout << ( false == solution.canWinBash(n3) ) << std::endl;

    return EXIT_SUCCESS;
}