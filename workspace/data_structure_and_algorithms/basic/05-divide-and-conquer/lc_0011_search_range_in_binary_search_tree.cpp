/**
 * Definition of TreeNode:
 */
#include <cstdlib>
#include <vector>

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
     * @param root: param root: The root of the binary search tree
     * @param k1: An integer
     * @param k2: An integer
     * @return: return: Return all keys that k1<=key<=k2 in ascending order
     */
    std::vector<int> searchRange(TreeNode * root, int k1, int k2) {
        std::vector<int> output;
        
        if ( k1 <= k2 ) {
            findAllWithinRange(root, k1, k2, output);
        }
        
        return output;
    }
private:
    void findAllWithinRange(TreeNode *root, int k1, int k2, std::vector<int> &output) {
        if ( nullptr != root ) {
            if ( k1 <= root->val && root->val <= k2 ) {
                findAllWithinRange(root->left, k1, k2, output);
                
                output.push_back(root->val);
                
                findAllWithinRange(root->right, k1, k2, output);
            } else if ( root->val < k1 ) {
                findAllWithinRange(root->right, k1, k2, output);
            } else {
                findAllWithinRange(root->left, k1, k2, output);
            }
        }
    }
};

int main() {
    return EXIT_SUCCESS;
}