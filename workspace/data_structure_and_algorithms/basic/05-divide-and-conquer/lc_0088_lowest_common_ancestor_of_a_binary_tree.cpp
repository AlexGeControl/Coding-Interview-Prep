/**
 * Definition of TreeNode:
 */
#include <iostream>

#include <cstdlib>

#include <unordered_map>

#include <deque>

class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = nullptr;
    }
};

class Solution {
public:
    /*
     * @param root: The root of the binary search tree.
     * @param A: A TreeNode in a Binary.
     * @param B: A TreeNode in a Binary.
     * @return: Return the least common ancestor(LCA) of the two nodes.
     */
    TreeNode * lowestCommonAncestor(TreeNode * root, TreeNode * A, TreeNode * B) {
        if ( A->val == B->val ) {
            return A;
        }
        
        std::unordered_map<int, TreeNode *> parent_map;
        parent_map[root->val] = root;
        buildParentMap(root, A, B, parent_map);
        
        std::deque<TreeNode *> path_A, path_B;
        buildPath(parent_map, A, path_A);
        buildPath(parent_map, B, path_B);
        
        TreeNode *LCA = nullptr;
        while (
            !path_A.empty() && !path_B.empty()
        ) {
            const auto &curr_A = path_A.front();
            const auto &curr_B = path_B.front();
            
            if ( curr_A->val == curr_B->val ) {
                LCA = curr_A;
            } else {
                break;
            }
            
            path_A.pop_front();
            path_B.pop_front();
        }
        
        return LCA;
    }
private:
    void buildParentMap(TreeNode *root, TreeNode *A, TreeNode *B, std::unordered_map<int, TreeNode *> &parent_map) {
        if ( 
            nullptr != root && 
            ( parent_map.end() == parent_map.find(A->val) || parent_map.end() == parent_map.find(B->val) )
        ) {
            if ( nullptr != root->left ) parent_map[root->left->val] = root;
            if ( parent_map.end() != parent_map.find(A->val) && parent_map.end() != parent_map.find(B->val) ) return;
            if ( nullptr != root->right ) parent_map[root->right->val] = root;
            if ( parent_map.end() != parent_map.find(A->val) && parent_map.end() != parent_map.find(B->val) ) return;
            
            if ( nullptr != root->left ) buildParentMap(root->left, A, B, parent_map);
            if ( nullptr != root->right ) buildParentMap(root->right, A, B, parent_map);
        }
    }
    
    void buildPath(const std::unordered_map<int, TreeNode *> &parent_map, TreeNode *leaf, std::deque<TreeNode *> &path) {
        while ( parent_map.at(leaf->val) != leaf ) {
            path.push_front(leaf);
            leaf = parent_map.at(leaf->val);
        }
        path.push_front(leaf);
    } 
};

int main() {
    std::cout << "Hello, Lowest Common Ancestor of Binary Tree!" << std::endl;
    return EXIT_SUCCESS;
}