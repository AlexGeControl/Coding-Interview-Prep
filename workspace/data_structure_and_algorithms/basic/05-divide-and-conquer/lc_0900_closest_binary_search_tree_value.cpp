/**
 * Definition of TreeNode:
 */
#include <cstdlib>

#include <cmath>
#include <limits>

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
     * @param root: the given BST
     * @param target: the given target
     * @return: the value in the BST that is closest to the target
     */
    int closestValue(TreeNode * root, double target) {
        // init result:
        Result result(root->val, std::numeric_limits<double>::max());
        
        FindClosestValue(root, target, result);
        
        return result.value_;
    }
private:
    struct Result {
        int value_;
        double residual_;
        
        Result(const int value, const double &residual) : value_(value), residual_(residual) {}
    };
    
    void FindClosestValue(const TreeNode * root, const double &target, Result &result) {
        if ( nullptr != root ) {
            double residual = std::fabs(root->val - target);
            
            if ( residual < result.residual_ ) {
                result.value_ = root->val;
                result.residual_ = residual;
            }
            
            if ( target < root->val ) {
                FindClosestValue(root->left, target, result);
            } else {
                FindClosestValue(root->right, target, result);
            }
        }
    }
};

int main() {
    return EXIT_SUCCESS;
}