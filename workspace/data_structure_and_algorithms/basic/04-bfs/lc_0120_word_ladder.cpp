#include <cstdlib>
#include <iostream>

#include <string>

#include <unordered_set>
#include <unordered_map>

#include <vector>

#include <deque>

class Solution {
public:
    static const int NOT_FOUND = -1;

    /*
     * @param start: a string
     * @param end: a string
     * @param dict: a set of string
     * @return: An integer
     */
    int ladderLength(
        std::string &start, 
        std::string &end, 
        std::unordered_set<std::string> &dict
    ) {
        dict.insert(start);
        dict.insert(end);
        
        int distance = NOT_FOUND;

        std::unordered_map<std::string, int> visited_from_start, visited_from_end;
        std::vector<std::string> path_from_start, path_from_end;
        std::deque<Node> frontier_from_start, frontier_from_end;

        if ( start != end ) {
            frontier_from_start.push_back( Node(start, 0) );
            frontier_from_end.push_back( Node(end, 0) );

            while ( !frontier_from_start.empty() || !frontier_from_end.empty() ) {
                if ( !frontier_from_start.empty() ) {
                    const Node &current_start = frontier_from_start.front();

                    if ( visited_from_start.end() == visited_from_start.find(current_start.data_) ) {
                        visited_from_start[current_start.data_] = current_start.distance_;

                        distance = getIntersection(visited_from_start, visited_from_end);
                        if ( NOT_FOUND != distance ) return ++distance;

                        for (const Node &neighbor: getNeighbors(current_start, dict, visited_from_start)) {
                            if ( neighbor.data_ == end ) return neighbor.distance_ + 1;

                            frontier_from_start.push_back(neighbor);
                        }
                    }

                    frontier_from_start.pop_front();
                }

                if ( !frontier_from_end.empty() ) {
                    const Node &current_end = frontier_from_end.front();

                    if ( visited_from_end.end() == visited_from_end.find(current_end.data_) ) {
                        visited_from_end[current_end.data_] = current_end.distance_;

                        distance = getIntersection(visited_from_start, visited_from_end);
                        if ( NOT_FOUND != distance ) return ++distance;

                        for (const Node &neighbor: getNeighbors(current_end, dict, visited_from_end)) {
                            if ( neighbor.data_ == start ) return neighbor.distance_ + 1;

                            frontier_from_end.push_back(neighbor);
                        }
                    }

                    frontier_from_end.pop_front();
                }
            }
        } else {
            distance = 0;
        }

        return ++distance;
    }

private:
    struct Node {
        Node(const std::string &data, const int distance): data_(data), distance_(distance) {}
        const std::string &data_;
        int distance_;
    };

    int getDistance(const std::string &x, const std::string &y) {
        const int N = x.length();

        int distance = 0;
        for (int n = 0; n < N; ++n) {
            if ( x.at(n) != y.at(n) ) ++distance;
        }

        return distance;
    }

    std::vector<Node> getNeighbors(
        const Node &word, 
        const std::unordered_set<std::string> &dict,
        const std::unordered_map<std::string, int> &visited
    ) {
        std::vector<Node> neighbors;

        for (const std::string &candidate: dict) {
            if ( 
                visited.end() == visited.find(candidate) && 
                1 == getDistance(word.data_, candidate) 
            ) {
                neighbors.push_back( Node(candidate, word.distance_ + 1) );
            }
        }

        return neighbors;
    }

    int getIntersection(
        const std::unordered_map<std::string, int> &x,
        const std::unordered_map<std::string, int> &y
    ) {
        for ( const auto &candidate_x: x ) {
            const auto &candidate_y = y.find(candidate_x.first);

            if ( y.end() != candidate_y ) {
                return candidate_x.second + candidate_y->second;
            }
        }

        return NOT_FOUND;
    }
};

int main() {
    Solution solution;

    std::string start1("hit");
    std::string end1("cog");
    std::unordered_set<std::string> dict1 {
        "hot","dot","dog","lot","log"
    };

    std::cout << ( 5 == solution.ladderLength(start1, end1, dict1) ) << std::endl;

    std::string start2("a");
    std::string end2("c");
    std::unordered_set<std::string> dict2 {
        "a","b","c"
    };

    std::cout << ( 2 == solution.ladderLength(start2, end2, dict2) ) << std::endl;

    return EXIT_SUCCESS;
}