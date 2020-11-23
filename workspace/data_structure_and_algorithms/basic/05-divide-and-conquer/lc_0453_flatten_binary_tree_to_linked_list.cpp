/**
 * Definition of TreeNode:
 */
#include <cstdlib>

#include <iostream>

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
    void flatten(TreeNode * root) {
        TreeNode *head = nullptr, **curr = nullptr;
        
        if ( nullptr != root ) {
            head = new TreeNode(root->val);
            head->left = head->right = nullptr;
            curr = &(head->right);
            
            preOrderFlatten(root->left, curr);
            preOrderFlatten(root->right, curr);
            
            // delete all the nodes in original binary tree:
            postOrderDelete(root->left);
            postOrderDelete(root->right);
            
            root->left = nullptr;
            root->right = head->right;
        }
    }
private:
    void preOrderFlatten(TreeNode *root, TreeNode **&output) {
        if ( nullptr != root ) {
            *output = new TreeNode(root->val);
            (*output)->left = (*output)->right = nullptr;
            output = &((*output)->right);
            
            preOrderFlatten(root->left, output);
            preOrderFlatten(root->right, output);
        }
    }
    
    void postOrderDelete(TreeNode *root) {
        if ( nullptr != root ) {
            postOrderDelete(root->left);
            postOrderDelete(root->right);
            
            delete root;
        }
    }
};

int main() {
    std::cout << "Hello, Flatten Binary Tree to Linked List!" << std::endl;
    return EXIT_SUCCESS;
}