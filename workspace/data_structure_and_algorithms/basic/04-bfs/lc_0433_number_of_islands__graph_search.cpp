#include <cstdlib>
#include <iostream>

#include <vector>

#include <unordered_set>

#include <deque>


class Solution {
public:
    /**
     * @param grid: a boolean 2D matrix
     * @return: an integer
     */
    int numIslands(const std::vector<std::vector<bool>> &grid) {
        int num_islands = 0;

        const int M = grid.size();
        
        if ( 0 < M ) {
            const int N = grid.at(0).size();
            std::unordered_set<int> visited;

            for ( int x = 0; x < M; ++x ) {
                for ( int y = 0; y < N; ++y) {
                    int init = XY2I(x, y, M, N);

                    if ( grid[x][y] && visited.end() == visited.find(init) ) {
                        std::deque<int> frontier;
                        frontier.push_back(init);

                        while ( !frontier.empty() ) {
                            int curr = frontier.front();

                            if ( visited.end() == visited.find(curr) ) {
                                visited.insert(curr);

                                for ( const int neighbor: getNeighbors(grid, visited, curr) ) {
                                    frontier.push_back(neighbor);
                                }
                            }

                            frontier.pop_front();
                        }

                        ++num_islands;
                    }
                }
            }
        }

        return num_islands;
    }
private:
    std::vector<int> getNeighbors(
        const std::vector<std::vector<bool>> &grid, 
        const std::unordered_set<int> &visited,
        const int i
    ) {
        const int M = grid.size();
        const int N = grid.at(0).size();
        
        int X, Y;
        I2XY(i, M, N, X, Y);

        std::vector<int> neighbors;
        if ( 
            0 <= X - 1 && grid[X - 1][Y] && 
            visited.end() == visited.find(XY2I(X - 1, Y, M, N)) 
        ) {
            neighbors.push_back( XY2I(X - 1, Y, M, N) );
        }
        if ( 
            X + 1 < M && grid[X + 1][Y] && 
            visited.end() == visited.find(XY2I(X + 1, Y, M, N)) 
        ) {
            neighbors.push_back( XY2I(X + 1, Y, M, N) );
        }
        if ( 
            0 <= Y - 1 && grid[X][Y - 1] && 
            visited.end() == visited.find(XY2I(X, Y - 1, M, N)) 
        ) {
            neighbors.push_back( XY2I(X, Y - 1, M, N) );
        }
        if ( 
            Y + 1 < N && grid[X][Y + 1] && 
            visited.end() == visited.find(XY2I(X, Y + 1, M, N)) 
        ) {
            neighbors.push_back( XY2I(X, Y + 1, M, N) );
        }

        return neighbors;
    }

    inline int XY2I(const int X, const int Y, const int M, const int N) {
        return X*N + Y;
    }

    inline void I2XY(const int I, const int M, const int N, int &X, int &Y) {
        X = I / N;
        Y = I % N;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<bool>> grid1 {
        {1,1,0,0,0},
        {0,1,0,0,1},
        {0,0,0,1,1},
        {0,0,0,0,0},
        {0,0,0,0,1}
    };

    std::cout << (3 == solution.numIslands(grid1)) << std::endl;

    std::vector<std::vector<bool>> grid2 {
        {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0},
        {1,0,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
        {0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    std::cout << (1 == solution.numIslands(grid2)) << std::endl;

    return EXIT_SUCCESS;
}