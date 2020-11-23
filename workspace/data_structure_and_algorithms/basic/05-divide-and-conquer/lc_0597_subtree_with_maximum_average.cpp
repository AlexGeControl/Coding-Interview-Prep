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
     * @return: the root of the maximum average of subtree
     */
    TreeNode *findSubtree2(TreeNode *root) {
        Result result(std::numeric_limits<double>::lowest(), root);
        Stat stat;
        
        getSumAndCount(root, stat, result);
        
        return result.node_;
    }
private:
    struct Stat {
        int sum;
        int count;
        Stat() : sum(0), count(0) {}
    };
    
    struct Result {
        double mean_;
        TreeNode *node_;
        Result(const double &mean, TreeNode *node): mean_(mean), node_(node) {}
    };
    
    void getSumAndCount(TreeNode *root, Stat &stat, Result &result) {
        if ( nullptr != root ) {
            Stat left_sub_stat, right_sub_stat;
            
            getSumAndCount(root->left, left_sub_stat, result);
            getSumAndCount(root->right, right_sub_stat, result);
            
            stat.sum = left_sub_stat.sum + right_sub_stat.sum + root->val;
            stat.count = left_sub_stat.count + right_sub_stat.count + 1;
            
            double mean = static_cast<double>(stat.sum) / stat.count;
            if ( result.mean_ < mean ) {
                result.mean_ = mean;
                result.node_ = root;
            }
        } else {
            stat.sum = 0;
            stat.count = 0;
        }
    }
};

int main() {
    std::cout << "Hello, Subtree with Maximum Average!" << std::endl;
    return EXIT_SUCCESS;
}