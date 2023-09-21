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
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            return head;
        }
        ListNode* p = head;
        int n;
        while (p->next != NULL) {
            n = p->val > p->next->val ? p->next->val : p->val;
            while (p->val % n != 0 || p->next->val % n != 0) {
                n--;
            }
            ListNode* new_node = new ListNode(n);
            new_node->next = p->next;
            p->next = new_node;
            p = p->next->next;
        }
        return head;
    }
};