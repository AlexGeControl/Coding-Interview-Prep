#include <iostream>

#include <vector>

#include <algorithm>

class Solution {
public:
    /**
     * @param S: A list of integers
     * @return: An integer
     */
    int triangleCount(const std::vector<int> &sides) {
        const int N = sides.size();

        int triangle_count = 0;

        if ( 3 <= N ) {
            // sort sides, O(N*logN):
            std::vector<int> sorted_sides(sides);
            std::sort(sorted_sides.begin(), sorted_sides.end());

            // count by c: O(N)
            for (int c_index = N - 1; 1 < c_index; --c_index) {
                countTriangleByC(sorted_sides, c_index, triangle_count);
            }

            // count by a: O(N**2)
            // for (int a_index = 0; a_index < N - 2; ++a_index) {
            //     countTriangleByA(sorted_sides, a_index, triangle_count);
            // }
        }

        return triangle_count;
    }

private:
    void countTriangleByC(
        const std::vector<int> &sides,
        const int c_index,
        int &triangle_count
    ) {
        const int c = sides.at(c_index);

        int a_index = 0, b_index = c_index - 1;

        while ( a_index < b_index ) {
            if ( sides.at(a_index) + sides.at(b_index) > c ) {
                triangle_count += b_index - a_index;
                --b_index;
            } else {
                ++a_index;
            }
        }
    }

    void countTriangleByA(
        const std::vector<int> &sides,
        const int a_index,
        int &triangle_count
    ) {
        const int N = sides.size();
        const int a = sides.at(a_index);

        int b_index = a_index + 1, c_index = N - 1;

        while ( b_index < c_index ) {
            while (
                b_index < c_index && 
                a + sides.at(b_index) <= sides.at(c_index)
            ) {
                ++b_index;
            }

            if ( b_index < c_index ) {
                triangle_count += c_index - b_index;
            }

            --c_index;
            b_index = a_index + 1;
        }
    }
};

int main() {
    Solution solution;

    std::vector<int> sides1 {7, 4, 6, 3};
    
    std::cout << (solution.triangleCount(sides1)) << std::endl;

    std::vector<int> sides2 {4, 4, 4, 4};
    
    std::cout << (solution.triangleCount(sides2)) << std::endl;

    std::vector<int> sides3 {8990,3146,9568,3889,7253,7395,10032,6179,1299,8738,1315,1280,830,6593};

    std::cout << (solution.triangleCount(sides3)) << std::endl;

    return EXIT_SUCCESS;
}