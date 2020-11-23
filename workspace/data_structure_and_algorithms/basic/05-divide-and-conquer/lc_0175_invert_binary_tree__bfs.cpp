/**
 * Definition of TreeNode:
 */ 
#include <cstdlib>

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
    /**
     * @param root: a TreeNode, the root of the binary tree
     * @return: nothing
     */
    void invertBinaryTree(TreeNode *root) {
        if ( nullptr != root ) {
            std::deque<TreeNode *> frontier;
            frontier.push_back(root);
            
            while ( !frontier.empty() ) {
                const auto &current = frontier.front();
                
                if ( nullptr != current->left ) frontier.push_back(current->left);
                if ( nullptr != current->right ) frontier.push_back(current->right);
                
                swapLeftRightSubtrees(current);
                
                frontier.pop_front();
            }
        }
    }
private:
    void swapLeftRightSubtrees(TreeNode *root) {
        TreeNode *node = root->left;
        root->left = root->right;
        root->right = node;
    }
};

int main() {
    return EXIT_SUCCESS;
}