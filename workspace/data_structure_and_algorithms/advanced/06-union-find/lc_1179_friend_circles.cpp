#include <iostream>

#include "include/union_find.hpp"

#include <vector>

class Solution {
public:
    /**
     * @param M: a matrix
     * @return: the total number of friend circles among all the students
     */
    int findCircleNum(std::vector<std::vector<int>> &M) {
        int num_friends_circle = 0;

        if ( 0 < M.size() ) {
            const int N = M.size();
            const int D = M.at(0).size();

            UnionFind<int> union_find;
            for (int n = 0; n < N; ++n) {
                for (int d = 0; d < D; ++d) {
                    if ( 1 == M[n][d] ) {
                        if ( !union_find.IsInside(n) ) union_find.Insert(n);
                        if ( !union_find.IsInside(d) ) union_find.Insert(d);

                        union_find.Union(n, d);
                    }
                }
            }

            num_friends_circle = union_find.GetNumComponents();
        }

        return num_friends_circle;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> members1 {
        {1,1,0},
        {1,1,0},
        {0,0,1}
    };

    std::cout << (2 == solution.findCircleNum(members1) ) << std::endl;

    return EXIT_SUCCESS;
}