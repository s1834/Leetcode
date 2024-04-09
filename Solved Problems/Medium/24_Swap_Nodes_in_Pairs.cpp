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
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        if(!head->next->next) {
            ListNode* nxt = head->next;
            head->next = NULL;
            nxt->next = head;
            head = nxt;
            return head;
        }

        ListNode* prev = head, *cur = head->next, *nxt = head->next->next;
        cur->next = prev;
        head = cur;
        prev->next = swapPairs(nxt);

        return head;
    }
};