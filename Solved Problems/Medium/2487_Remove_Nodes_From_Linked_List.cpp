/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        if (!head->next) {
            return head;
        }
        ListNode *prev = NULL, *cur = head, *nxt = cur->next;
        while (nxt != NULL) {
            cur->next = prev;
            prev = cur;
            cur = nxt;
            nxt = cur->next;
        }
        cur->next = prev;
        prev = cur;

        ListNode* max = prev, *ptr = prev->next; 
        while(ptr->next) {
            if (ptr->val >= max->val) {
                max->next = ptr;
                max = ptr;
            }
            ptr = ptr->next;
            if(!ptr->next) {
                max->next = NULL;
            }
        }
        if (!max->next && ptr->val >= max->val) {
            max->next = ptr;
        }

        cur = prev;
        prev = NULL;
        nxt = cur->next;
        while (nxt != NULL) {
            cur->next = prev;
            prev = cur;
            cur = nxt;
            nxt = cur->next;
        }
        cur->next = prev;
        prev = cur;
        return prev;
    }
};