/**
 * Definition for Directed graph.
 */
#include <cstdlib>
#include <iostream>

#include <vector>

#include <deque>

#include <unordered_set>
#include <unordered_map>

struct DirectedGraphNode {
    int label;
    std::vector<DirectedGraphNode *> neighbors;
    DirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
    /*
     * @param graph: A list of Directed graph node
     * @return: Any topological order for the given graph.
     */
    std::vector<DirectedGraphNode*> topSort(std::vector<DirectedGraphNode*>& graph) {
        // first, count the in-degree of each node, O(V):
        std::unordered_map<int, int> in_degree_count;
        for (const auto &node: graph) {
            if ( in_degree_count.end() == in_degree_count.find(node->label) ) {
                in_degree_count[node->label] = 0;
            }

            for (const auto &neighbor: node->neighbors) {
                if ( in_degree_count.end() == in_degree_count.find(neighbor->label) ) {
                    in_degree_count[neighbor->label] = 0;
                }

                ++in_degree_count.at(neighbor->label);
            }
        }

        // perform BFS on each node whose in-degree is 0, O(V + E):
        const int N = graph.size();
        std::unordered_set<int> traversed;
        std::vector<DirectedGraphNode*> result;
        for (int node_id = 0; node_id < N; ++node_id) {
            if ( 0 == in_degree_count.at(node_id) && traversed.end() == traversed.find(node_id) ) {
                std::deque<DirectedGraphNode*> frontier;
                frontier.push_back(graph.at(node_id));
                
                while ( !frontier.empty() ) {
                    const auto &current = frontier.front();
                    
                    if ( 
                        traversed.end() == traversed.find(current->label)
                    ) {
                        traversed.insert(current->label);
                        result.push_back(current);
                        
                        for (const auto &neighbor: current->neighbors) {
                            if (
                                traversed.end() == traversed.find(neighbor->label)
                            ) {
                                --in_degree_count.at(neighbor->label);
                                
                                if ( 0 == in_degree_count.at(neighbor->label) ) {
                                    frontier.push_back(neighbor);
                                }
                            }
                        }
                        
                    }
                    
                    frontier.pop_front();
                }
            }
        }
        
        return result;
    }
};

int main() {
    return EXIT_SUCCESS;
}