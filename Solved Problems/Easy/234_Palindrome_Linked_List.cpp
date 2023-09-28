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
    bool isPalindrome(ListNode* head) {
        if (!head) {
            return 0;
        }
        
        int count = 0;
        ListNode* ptr = head;
        while (ptr) {
            count++;
            ptr = ptr->next;
        }
        ptr = head;
        count = (count % 2) ? count / 2 - 1 : count / 2;
        ListNode *prev = NULL, *cur = head, *nxt = cur->next;
        while (count) {
            cur->next = prev;
            prev = cur;
            cur = nxt;
            nxt = cur->next;
            count--;
        }
        
        while (prev && cur) {
            if (prev->val != cur->val) {
                return false;
            }
            prev = prev->next;
            cur = cur->next;
        }

        return true;
    }
};