/**
 * Definition of singly-linked-list:
 * 
 */

#include <cstdlib>

struct ListNode {
    ListNode(int val) {
        this->val = val;
        this->next = NULL;
    }

    int val;
    ListNode *next;
};

class Solution {
public:
    /**
     * @param head: the head of linked list.
     * @return: a middle node of the linked list
     */
    ListNode *middleNode(ListNode *head) {
        // init two pointers, slow & fast:
        ListNode *result = NULL;
        ListNode *middle_ptr, *tail_ptr;
        
        middle_ptr = tail_ptr = head;
        while ( NULL != tail_ptr ) {
            // move tail one step forward:
            tail_ptr = tail_ptr->next;

            // update middle value pointer:
            result = middle_ptr;
            
            // termination check:
            if ( NULL == tail_ptr ) break;
            
            // move both one step forward:
            middle_ptr = middle_ptr->next;
            tail_ptr = tail_ptr->next;
        }
        
        return result;
    }
};

int main() {
    Solution solution;

    solution.middleNode(NULL);

    return EXIT_SUCCESS;
}