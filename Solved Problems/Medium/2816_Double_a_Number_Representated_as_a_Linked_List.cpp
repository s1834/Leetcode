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
private: 
    int carry = 0;

    ListNode* reverse(ListNode* head) {
        if (!head->next) {
            return head;
        }
        ListNode* prev = NULL, *cur = head, *nxt = cur->next;
        while (nxt) {
            cur->next = prev;
            prev = cur;
            cur = nxt;
            nxt = nxt->next;
        }
        cur->next = prev;
        prev = cur;
        return prev;
    }

    ListNode* mul(ListNode* head) {
        ListNode* ptr = head;
        while (ptr) {
            if (ptr->val * 2 + carry > 9) {
                ptr->val = (ptr->val * 2 + carry) % 10;
                carry = 1;
            } else {
                ptr->val = ptr->val * 2 + carry;
                carry = 0;
            }
            if (!ptr->next && carry) {
                ptr->next = new ListNode(1);
                return head;
            }
            ptr = ptr->next;
        }
        return head;
    }

public:
    ListNode* doubleIt(ListNode* head) {
        return reverse(mul(reverse(head)));
    }
};