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
    static const int SENTINEL_NODE_ID = -1;
    /*
     * @param root: The root of the binary search tree.
     * @param value: Remove the node with given value.
     * @return: The root of the binary search tree after removal.
     */
    TreeNode * removeNode(TreeNode * root, const int value) {
        if ( nullptr != root ) {
            // first, create sentinel node as root parent:
            TreeNode *root_parent =  new TreeNode(SENTINEL_NODE_ID);
            root_parent->left = root;
            
            // first, find target node in BST:
            TreeNode *target_node = root, *target_node_parent = root_parent;
            while ( nullptr != target_node ) {
                if ( value == target_node->val ) break;
                
                target_node_parent = target_node;
                
                if ( value < target_node->val ) {
                    target_node = target_node->left;
                }
                else {
                    target_node = target_node->right;
                }
            }
            
            if ( nullptr != target_node ) {
                if ( nullptr == target_node->right ) {
                    if ( target_node == target_node_parent->left ) target_node_parent->left = target_node->left;
                    else target_node_parent->right = target_node->left;
                } else {
                    // find the smallest node in right subtree:
                    TreeNode *new_root_node = target_node->right, *new_root_node_parent = target_node;
                    
                    while ( nullptr != new_root_node->left ) {
                        new_root_node_parent = new_root_node;
                        new_root_node = new_root_node->left;
                    }
                    
                    // remove new root from tree:
                    if ( new_root_node == new_root_node_parent->left ) new_root_node_parent->left = new_root_node->right;
                    else new_root_node_parent->right = new_root_node->right;
                    
                    // connect new root to original BST:
                    new_root_node->right = target_node->right;
                    new_root_node->left = target_node->left;
                    
                    if ( target_node == target_node_parent->left ) target_node_parent->left = new_root_node;
                    else target_node_parent->right = new_root_node;   
                }
            }
            
            // update root if needed:
            if ( root_parent == target_node_parent ) root = target_node_parent->left;
            
            // in case of memory leakage:
            delete root_parent;
        }
        
        return root;
    }
};

int main() {
    std::cout << "Hello, Remove Node in BST!" << std::endl;
    return EXIT_SUCCESS;
}