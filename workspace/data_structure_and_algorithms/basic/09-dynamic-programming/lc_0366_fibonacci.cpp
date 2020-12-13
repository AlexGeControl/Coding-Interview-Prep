#include <cstdlib>
#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param n: an integer
     * @return: an ineger f(n)
     */
    int fibonacci(int n) {
        if ( 1 == n ) { return 0; }
        else if ( 2 == n ) { return 1; }

        // init rolling table:
        std::vector<int> fibonacci_table(3, 0);
        fibonacci_table.at(0) = 0;
        fibonacci_table.at(1) = 1;

        for (int k = 3; k <= n; ++k) {
            const int k_0 = ( k - 1 ) % 3;
            const int k_1 = ( k - 2 ) % 3;
            const int k_2 = ( k - 3 ) % 3;

            fibonacci_table.at(k_0) = fibonacci_table.at(k_1) + fibonacci_table.at(k_2);
        }

        return fibonacci_table.at( (n - 1) % 3 );
    }
};

int main() {
    Solution solution;

    std::cout << solution.fibonacci(3) << std::endl;

    return EXIT_SUCCESS;
}