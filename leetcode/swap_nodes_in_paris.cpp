// https://leetcode.com/problems/swap-nodes-in-pairs/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:

    ListNode* swapPairs(ListNode* head) {
        if (!head)
            return nullptr;
        if (!(head->next))
            return head;
        
        
        ListNode* nextnode = head->next;
        ListNode* node = head;

        node->next = nextnode->next;
        nextnode->next = node;
        nextnode->next->next = swapPairs(nextnode->next->next);
  
        
        return nextnode;
        //printList(nextnode);

    }
    
    void printList(ListNode* node)
    {
        ListNode* tmpnode = node;
        while (!tmpnode)
        {
            std::cout << tmpnode->val << std::endl;;
            tmpnode = tmpnode->next;
        }
        
    }
};


int main()
{

    ListNode *node1 = new ListNode(1);
    ListNode *node2 = new ListNode(2);
    ListNode *node3 = new ListNode(3);
    ListNode *node4 = new ListNode(4);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
 


 
    Solution sol;
    ListNode* result = sol.swapPairs(node1);
    while (result) 
    {
        std::cout << result->val << std::endl;
        result = result->next;
    }

    return 0;
}