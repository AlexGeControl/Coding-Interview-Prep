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

#include <queue>

#include <algorithm>

class Solution {
public:
    /**
     * @param points: a list of points
     * @param origin: a point
     * @param k: An integer
     * @return: the k closest points
     */
    std::vector<Point> kClosest(std::vector<Point> &points, Point &origin, int k) {
        std::vector<Point> result;

        const int N = points.size();
        if ( 0 < k && 0 < N ) {
            // init max pq.:
            std::priority_queue<PointDistance, std::vector<PointDistance>, std::less<PointDistance>> max_pq;

            // dynamic min k:
            for (int i = 0; i < N; ++i) {
                const Point &point = points.at(i);

                const int dx = point.x - origin.x;
                const int dy = point.y - origin.y;

                PointDistance pd(
                    dx*dx + dy*dy,
                    point.x, point.y,
                    i
                );

                max_pq.push(pd);

                if (static_cast<size_t>(k) < max_pq.size()) {
                    max_pq.pop();
                }
            }

            while ( !max_pq.empty() ) {
                const PointDistance &pd = max_pq.top();

                result.push_back(points.at(pd.idx));

                max_pq.pop();
            }

            std::reverse(result.begin(), result.end());
        }

        return result;
    }
private:
    struct PointDistance {
        int square_distance = 0;
        int x;
        int y;
        int idx;
        
        PointDistance(const int square_distance_, const int x_, const int y_, const int idx_)
         : square_distance(square_distance_), x(x_), y(y_), idx(idx_) {}

        friend bool operator< (const PointDistance &p, const PointDistance &q) {
            if ( p.square_distance != q.square_distance ) return p.square_distance < q.square_distance;

            if ( p.x != q.x ) return p.x < q.x;

            return p.y < q.y;
        }
    };
};

int main() {
    Solution solution;

    return EXIT_SUCCESS;
}