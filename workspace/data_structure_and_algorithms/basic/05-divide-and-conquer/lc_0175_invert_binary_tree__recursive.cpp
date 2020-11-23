/**
 * Definition of TreeNode:
 */ 
#include <cstdlib>
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
            TreeNode *node = root->left;
            root->left = root->right;
            root->right = node;
            
            invertBinaryTree(root->left);
            invertBinaryTree(root->right);
        }
    }
};

int main() {
    return EXIT_SUCCESS;
}