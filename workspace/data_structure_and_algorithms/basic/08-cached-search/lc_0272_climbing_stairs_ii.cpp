#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param n: An integer
     * @return: An Integer
     */
    int climbStairs2(int n) {
        if ( 0 == n ) return 1;
        
        std::vector<int> climb_stairs_table(4, 0);
        
        climb_stairs_table.at(0) = 1;
        climb_stairs_table.at(1) = 2;
        climb_stairs_table.at(2) = 4;
        
        for (int i = 3; i < n; ++i) {
            climb_stairs_table.at( i % 4 ) = (
                climb_stairs_table.at( (i - 1) % 4 ) + 
                climb_stairs_table.at( (i - 2) % 4 ) + 
                climb_stairs_table.at( (i - 3) % 4 ) 
            );
        }
        
        return climb_stairs_table.at( (n - 1) % 4 );
    }
};

int main() {
    Solution solution;

    int n1 = 3;
    std::cout << ( 4 == solution.climbStairs2(n1) ) << std::endl;

    int n2 = 4;
    std::cout << ( 7 == solution.climbStairs2(n2) ) << std::endl;

    int n3 = 0;
    std::cout << ( 1 == solution.climbStairs2(n3) ) << std::endl;

    return EXIT_SUCCESS;
}
