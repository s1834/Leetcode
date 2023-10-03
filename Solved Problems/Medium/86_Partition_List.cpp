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
    ListNode* part(ListNode* head1, ListNode* head2, int x, int flag) {
        ListNode* ptr1 = head1, *ptr2 = head2, *temp1 = ptr1, *temp2 = ptr2;
        while (ptr1->next && ptr2->next) {
            if (flag) {
                if(ptr2->next->val < x) {
                    ptr1->next = ptr2->next;
                    ptr1 = ptr1->next;
                    flag = 0;
                } else {
                    ptr2 = ptr2->next;
                }
            } else {
                if (ptr1->next->val < x) {
                    ptr1 = ptr1->next;
                } else {
                    ptr2->next = ptr1->next;
                    ptr2 = ptr2->next;
                    flag = 1;
                }
            }
            
        }

        if (!ptr1->next) {
            ptr2->next = NULL;
            ptr1->next = head2;                    
        }
        if (!ptr2->next) {
            ptr1->next = head2;
        }

        return head1;
    }

public:
    ListNode* partition(ListNode* head, int x) {
        if (!head || !head->next) {
            return head;
        }

        ListNode *ptr1 = head, *ptr2 = head, *head1, *head2;
        int ls = 1, mx = 1, flag = 0;
        while (ptr1 && ptr2 && (ls || mx)) {
            if (ls && ptr1->val < x) {
                head1 = ptr1;
                ls = 0;
                if (!flag) {
                    flag = 1;
                }
            }
            if (mx && ptr2->val >= x) {
                head2 = ptr2;
                mx = 0;
                if (!flag) {
                    flag = 2;
                }
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        if (ls || mx) {
            return head;
        }

       if (flag == 1) {
           head1 = part(head1, head2, x, 1);
           return head1;
       } else {
           head2 = part(head1, head2, x, 0);
           return head2;
       }
    }
};