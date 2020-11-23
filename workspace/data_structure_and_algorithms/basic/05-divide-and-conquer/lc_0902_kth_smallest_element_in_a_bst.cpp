/**
 * Definition of TreeNode:
 */ 
#include <cstdlib>
#include <iostream>

#include <vector>

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
     * @param k: the given k
     * @return: the kth smallest element in BST
     */
    int kthSmallest(TreeNode * root, int k) {
        // perform in-order traversal on given tree:
        std::vector<int> k_smallest;
        inOrderTraverse(root, k, k_smallest);
        
        return k_smallest.back();
    }
private:
    void inOrderTraverse(const TreeNode *root, const size_t k, std::vector<int> &k_smallest) {
        if ( nullptr != root && k_smallest.size() < k ) {
            inOrderTraverse(root->left, k, k_smallest);
            if ( k == k_smallest.size() ) return;
            
            k_smallest.push_back(root->val);
            if ( k == k_smallest.size() ) return;
            
            inOrderTraverse(root->right, k, k_smallest);
        }
    }
};

int main() {
    std::cout << "Hello, Divide and Conquer!" << std::endl;

    return EXIT_SUCCESS;
}