#include <cstdlib>
#include <iostream>

#include "include/union_find.hpp"

#include <algorithm>

#include <vector>

class Solution {
public:
    static const int BRICK = 1;
    static const int FREE = 0;
    static const int WALL_ID = -1;

    /**
     * @param grid: a grid
     * @param hits: some erasures order
     * @return: an array representing the number of bricks that will drop after each erasure in sequence
     */
    std::vector<int> hitBricks(
        std::vector<std::vector<int>> &grid, 
        std::vector<std::vector<int>> &hits
    ) {
        static const std::vector<std::pair<int, int>> DELTAS {
            // up:
            {-1,  0},
            // down:
            {+1,  0},
            // left:
            { 0, -1},
            // right:
            { 0, +1}
        };

        std::vector<int> num_falls;

        if ( 0 < grid.size() && 0 < hits.size() ) {
            const int N = grid.size();
            const int M = grid.at(0).size();
            
            // first, use all the hits and get the size of connected components at the very end:
            std::vector<int> actual_hit_indices;
            for (size_t i = 0; i < hits.size(); ++i) {
                const auto &hit = hits.at(i);
                const int hit_x = hit.at(0);
                const int hit_y = hit.at(1);

                if ( BRICK == grid[hit_x][hit_y] ) {
                    grid[hit_x][hit_y] = FREE;
                    actual_hit_indices.push_back(i);
                }
            }

            UnionFind union_find;
            union_find.Insert(WALL_ID);
            for (int n = 0; n < N; ++n) {
                for (int m = 0; m < M; ++m) {
                    if ( BRICK == grid[n][m] ) {
                        const int brick_id = GetID(N, M, n, m);

                        union_find.Insert(brick_id);

                        if ( 0 == n ) union_find.Union(WALL_ID, brick_id);
                        else {
                            for (size_t i = 0; i < DELTAS.size(); ++i) {
                                if ( 0 == i || 2 == i ) {
                                    const int neighbor_x = n + DELTAS.at(i).first;
                                    const int neighbor_y = m + DELTAS.at(i).second;

                                    if (
                                        0 <= neighbor_x && neighbor_x < N && 
                                        0 <= neighbor_y && neighbor_y < M && 
                                        BRICK == grid[neighbor_x][neighbor_y]
                                    ) {
                                        const int neighbor_brick_id = GetID(N, M, neighbor_x, neighbor_y);
                                        union_find.Union(neighbor_brick_id, brick_id);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // apply hits in reverse order and monitor the size change:
            int prev_size = union_find.GetSize(union_find.Find(WALL_ID));
            int hit_idx = hits.size() - 1;
            while ( 0 <= hit_idx ) {
                if ( actual_hit_indices.empty() || actual_hit_indices.back() != hit_idx ) {
                    num_falls.push_back(0);
                    --hit_idx;
                    continue;
                }
                
                const auto &hit = hits.at(hit_idx);
                const int hit_x = hit.at(0);
                const int hit_y = hit.at(1);

                grid[hit_x][hit_y] = BRICK;

                const int brick_id = GetID(N, M, hit_x, hit_y);

                union_find.Insert(brick_id);

                if ( 0 == hit_x ) union_find.Union(WALL_ID, brick_id);

                for (const auto &DELTA: DELTAS) {
                    const int neighbor_x = hit_x + DELTA.first;
                    const int neighbor_y = hit_y + DELTA.second;

                    if (
                        0 <= neighbor_x && neighbor_x < N &&
                        0 <= neighbor_y && neighbor_y < M && 
                        BRICK == grid[neighbor_x][neighbor_y]
                    ) {
                        const int neighbor_brick_id = GetID(N, M, neighbor_x, neighbor_y);
                        union_find.Union(neighbor_brick_id, brick_id);
                    }
                }

                int curr_size = union_find.GetSize(union_find.Find(WALL_ID));

                if ( prev_size == curr_size ) num_falls.push_back(0);
                else {
                    num_falls.push_back(curr_size - prev_size - 1);
                    prev_size = curr_size;
                }

                actual_hit_indices.pop_back();
                --hit_idx;
            }

            std::reverse(num_falls.begin(), num_falls.end());
        }

        return num_falls;
    }
private:
    static int GetID(const int N, const int M, const int n, const int m) {
        return M*n + m;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> grid1 {
        {1,0,0,0},
        {1,1,1,0}
    };
    std::vector<std::vector<int>> hits1 {
        {1,0}
    };

    for (const int num_fall: solution.hitBricks(grid1, hits1)) {
        std::cout << num_fall << " ";
    }
    std::cout << std::endl << std::endl;

    std::vector<std::vector<int>> grid2 {
        {1,0,1},
        {1,1,1}
    };
    std::vector<std::vector<int>> hits2 {
        {0,0},
        {0,2},
        {1,1}
    };
    for (const int num_fall: solution.hitBricks(grid2, hits2)) {
        std::cout << num_fall << " ";
    }
    std::cout << std::endl << std::endl;

    std::vector<std::vector<int>> grid3 {
        {1,1,1},
        {0,1,0},
        {0,0,0}
    };
    std::vector<std::vector<int>> hits3 {
        {0,2},
        {2,0},
        {0,1},
        {1,2}
    };
    for (const int num_fall: solution.hitBricks(grid3, hits3)) {
        std::cout << num_fall << " ";
    }
    std::cout << std::endl << std::endl;

    return EXIT_SUCCESS;
}