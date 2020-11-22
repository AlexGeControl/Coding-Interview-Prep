/**
 * Definition for a point.
 */
#include <cstdlib>
struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

#include <vector>

#include <unordered_set>

#include <deque>

class Solution {
public:
    static const int NOT_REACHABLE = -1;
    
    /**
     * @param grid: a chessboard included 0 (false) and 1 (true)
     * @param source: a point
     * @param destination: a point
     * @return: the shortest path 
     */
    int shortestPath(std::vector<std::vector<bool>> &grid, Point &source, Point &destination) {
        const int M = grid.size();
        const int N = grid.at(0).size();
        
        // reset visited set:
        if ( !grid[source.x][source.y] ) {
            Reset(M, N);
        
            std::deque<Neighbor> neighbors;
            neighbors.push_back( Neighbor(source, 0) );
        
            while ( !neighbors.empty() ) {
                const Neighbor &current = neighbors.front();
            
                if ( !IsVisited(current.point) ) {
                    AddVisited(current.point);
                    
                    if (
                        destination.x == current.point.x &&
                        destination.y == current.point.y
                    ) {
                        return current.distance;
                    }
                
                    for (const Neighbor &neighbor: getNeighbors(grid, current) ) {
                        neighbors.push_back(neighbor);
                    }
                }
            
                neighbors.pop_front();
            }
        }

        
        return NOT_REACHABLE;
    }
private:
    struct Neighbor {
        Neighbor(const Point &point, const int distance) {
            this->point = point;
            this->distance = distance;
        }
        Point point;
        int distance;
    };
    
    int M_;
    int N_;
    std::unordered_set<int> visited_;
    
    void Reset(const int M, const int N) {
        M_ = M;
        N_ = N;
        visited_.clear();
    }
    
    void AddVisited(const Point &point) {
        int id = point.x*N_ + point.y;
        visited_.insert(id);
    }
    
    bool IsVisited(const Point &point) {
        int id = point.x*N_ + point.y;
        return visited_.end() != visited_.find(id);
    }
    
    bool IsVisited(const int x, const int y) {
        int id = x*N_ + y;
        return visited_.end() != visited_.find(id);
    }
    
    bool WithInBound(int x, int y) {
        return (
            0 <= x && x < M_ &&
            0 <= y && y < N_
        );
    }
    
    std::vector<Neighbor> getNeighbors(const std::vector<std::vector<bool>> &grid, const Neighbor &current) {
        static int N = 8;
        static std::vector<Point> adjacency {
            Point(+1, +2),
            Point(+1, -2),
            Point(-1, +2),
            Point(-1, -2),
            Point(+2, +1),
            Point(+2, -1),
            Point(-2, +1),
            Point(-2, -1)
        };
        
        std::vector<Neighbor> neighbors;
        for (int i = 0; i < N; ++i) {
            const Point &a = adjacency.at(i);
            
            int ax = current.point.x + a.x;
            int ay = current.point.y + a.y;
            
            if (
                WithInBound(ax, ay) && !grid[ax][ay] && !IsVisited(ax, ay)
            ) {
                neighbors.push_back( Neighbor(Point(ax, ay), current.distance + 1) );
            }
        }
        
        return neighbors;
    }
};

int main() {
    return EXIT_SUCCESS;
}