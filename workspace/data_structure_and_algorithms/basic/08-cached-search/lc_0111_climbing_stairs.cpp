#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param n: An integer
     * @return: An integer
     */
    int climbStairs(int n) {
        if ( 0 == n ) return 0;
        
        // init table:
        std::vector<int> climb_stairs_table(3, 0);

        climb_stairs_table.at(0) = 1;
        climb_stairs_table.at(1) = 2;

        for (int i = 2; i < n; ++i) {
            climb_stairs_table.at( i % 3 ) = (
                climb_stairs_table.at( (i - 1) % 3 ) + 
                climb_stairs_table.at( (i - 2) % 3 )
            );
        }

        return climb_stairs_table.at( (n - 1) % 3 );
    }
};

int main() {
    Solution solution;

    int n1 = 3;
    std::cout << ( 3 == solution.climbStairs(n1) ) << std::endl;

    int n2 = 1;
    std::cout << ( 1 == solution.climbStairs(n2) ) << std::endl;

    int n3 = 0;
    std::cout << ( 0 == solution.climbStairs(n3) ) << std::endl;

    return EXIT_SUCCESS;
}