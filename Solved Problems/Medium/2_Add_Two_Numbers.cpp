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
    ListNode* add(ListNode* l1, ListNode* l2, int carry) {
        if(!l1 && !l2) {
            return l1;
        }
 
        if(l1 && !l2) {
            int sum = l1->val + carry;
            l1->val = sum % 10;
            if(!l1->next && sum / 10) {
                ListNode* newNode = new ListNode(carry);
                l1->next = newNode;
                l1 = l1->next;
            }
            add(l1->next, l2, sum / 10);
        } else {
            int sum = l1->val + l2->val + carry;
            l1->val = sum % 10;
            if(!l1->next && l2->next) {
                l1->next = l2->next;
                l2->next = NULL;
            }
            add(l1->next, l2->next, sum / 10);
        }

        return l1;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return add(l1, l2, 0);   
    }
};