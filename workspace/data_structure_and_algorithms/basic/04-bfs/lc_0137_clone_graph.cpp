/**
 * Definition for undirected graph.
 */
#include <cstdlib>

#include <vector>

#include <unordered_set>

#include <deque>

#include <unordered_map>

struct UndirectedGraphNode {
    int label;
    std::vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
    /**
     * @param node: A undirected graph node
     * @return: A undirected graph node
     */
    UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node) {
        
        if ( nullptr != node ) {
            std::unordered_set<int> visited;
            std::deque<UndirectedGraphNode*> frontier;
            std::unordered_map<int, UndirectedGraphNode*> cloned_graph;
        
            frontier.push_back(node);
            
            while ( !frontier.empty() ) {
                const auto &current = frontier.front();
                
                if ( visited.end() == visited.find(current->label) ) {
                    visited.insert(current->label);
                    
                    if ( cloned_graph.end() == cloned_graph.find(current->label) ) {
                        cloned_graph[current->label] = new UndirectedGraphNode(current->label);
                    }
                    
                    for (const auto &neighbor: current->neighbors) {
                        if ( cloned_graph.end() == cloned_graph.find(neighbor->label) ) cloned_graph[neighbor->label] = new UndirectedGraphNode(neighbor->label);
                        
                        cloned_graph[current->label]->neighbors.push_back(cloned_graph.at(neighbor->label));
                        
                        if ( visited.end() == visited.find(neighbor->label) ) frontier.push_back(neighbor);
                    }
                }
                
                frontier.pop_front();
            }
            
            return cloned_graph.at(node->label);
        }
        
        return nullptr;
    }
};

int main() {
    return EXIT_SUCCESS;
}