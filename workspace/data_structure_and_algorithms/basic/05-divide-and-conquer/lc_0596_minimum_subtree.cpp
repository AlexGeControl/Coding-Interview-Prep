/**
 * Definition of TreeNode:
 */ 
#include <cstdlib>
#include <iostream>

#include <limits>

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
     * @param root: the root of binary tree
     * @return: the root of the minimum subtree
     */
    TreeNode * findSubtree(TreeNode * root) {
        Result result(std::numeric_limits<int>::max(), root);
        
        int sum;
        postOrderTraverse(root, sum, result);
        
        return result.node_;
    }
private:
    struct Result {
        int sum_;
        TreeNode *node_;
        Result(const int sum, TreeNode *node): sum_(sum), node_(node) {}
    };
    
    void postOrderTraverse(TreeNode *root, int &sum, Result &result) {
        if ( nullptr != root ) {
            int sum_left_subtree, sum_right_subtree;
            
            postOrderTraverse(root->left, sum_left_subtree, result);
            postOrderTraverse(root->right, sum_right_subtree, result);
            
            sum = sum_left_subtree + sum_right_subtree + root->val;
            
            if ( sum < result.sum_ ) {
                result.sum_ = sum;
                result.node_ = root;
            }
        } else {
            sum = 0;
        }
    }
};

int main() {
    std::cout << "Hello, Minimum Subtree!" << std::endl;
    return EXIT_SUCCESS;
}