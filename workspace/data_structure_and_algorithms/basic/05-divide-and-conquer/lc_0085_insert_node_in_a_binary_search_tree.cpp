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
    /*
     * @param root: The root of the binary search tree.
     * @param node: insert this node into the binary search tree
     * @return: The root of the new binary search tree.
     */
    TreeNode * insertNode(TreeNode *root, TreeNode *node) {
        if ( nullptr == root ) {
            root = node;
        } else if ( nullptr != node ) {
            TreeNode *current = root;
            
            while ( nullptr != current ) {
                if ( node->val < current->val ) {
                    if ( nullptr == current->left ) {
                        current->left = node;
                        break;
                    }
                    else current = current->left;
                } else {
                    if ( nullptr == current->right ) {
                        current->right = node;
                        break;
                    }
                    else current = current->right;
                }
            }
        }
        
        return root;
    }
};

int main() {
    return EXIT_SUCCESS;
}