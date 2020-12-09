/**
 * Definition for a point.
 */
#include <cstdlib>

#include <iostream>

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

#include <vector>

#include "include/union_find.hpp"

class Solution {
public:
    /**
     * @param n: An integer
     * @param m: An integer
     * @param operators: an array of point
     * @return: an integer array
     */
    std::vector<int> numIslands2(const int N, const int M, const std::vector<Point> &operators) {
        static const std::vector<std::pair<int, int>> DELTAS {
            { -1,  0 },
            { +1,  0 },
            {  0, -1 },
            {  0, +1 }
        };

        std::vector<int> num_islands;

        UnionFind union_find;
        for (const Point &point: operators) {
            const int id = GetID(N, M, point.x, point.y);

            union_find.Insert(id);

            for (const auto &delta: DELTAS) {
                const int new_x = point.x + delta.first;
                const int new_y = point.y + delta.second;
                const int new_id = GetID(N, M, new_x, new_y);

                if (
                    0 <= new_x && new_x < N &&
                    0 <= new_y && new_y < M && 
                    union_find.IsInside(new_id)
                ) {
                    union_find.Union(id, new_id);
                }
            }

            num_islands.push_back( union_find.GetNumComponents() );
        }

        return num_islands;
    }
private:
    static int GetID(const int N, const int M, const int x, const int y) {
        return x * M + y;
    }
};

int main() {
    Solution solution;

    const int N1 = 4;
    const int M1 = 5;
    const std::vector<Point> points1 {
        {1,1},
        {0,1},
        {3,3},
        {3,4}
    };

    for (const int c: solution.numIslands2(N1, M1, points1) ) {
        std::cout << c << " ";
    }
    std::cout << std::endl << std::endl;

    return EXIT_SUCCESS;
}