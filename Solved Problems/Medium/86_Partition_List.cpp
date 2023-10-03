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
        ListNode* ptr1 = head1, *ptr2 = head2;
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

        ListNode *ptr = head, *head1, *head2, *temp;
        int ls = 1, mx = 1, flag = 0;
        while (ptr && (ls || mx)) {
            if (ptr->val < x) {
                if (!ls) {
                    temp->next = ptr;
                    temp = temp->next;
                } else {
                    head1 = ptr;
                    ls = 0;
                    if (!flag) {
                        temp = head1;
                        flag = 1;
                    }
                }
            }
            if (ptr->val >= x) {
                if (!mx) {
                    temp->next = ptr;
                    temp = temp->next;
                } else {
                    head2 = ptr;
                    mx = 0;
                    if (!flag) {
                        temp = head2;
                        flag = 2;
                    }
                }
            }
            ptr = ptr->next;
        }

        if (ls || mx) {
            return head;
        }

        if (flag == 1) {
            part(temp, head2, x, 1);
            return head1;
        } else {
            part(head1, temp, x, 0);
            ptr = head1;
            ListNode* ptr1 = head1;
            while (ptr->val < x) {
                ptr1 = ptr;
                ptr = ptr->next;
            }
            ptr1->next = head2;
            return head1;
        }
    }
};