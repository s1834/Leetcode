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
    int count(ListNode* head) {
        ListNode* ptr = head;
        int count = 0;
        while(ptr) {
            count++;
            ptr = ptr->next;
        }
        return count;
    }

    ListNode* add(ListNode* head1, ListNode* head2) {
        ListNode* ptr1 = head1, *ptr2 = head2, *temp = ptr1;
        while (ptr1 && ptr2) {
             if (ptr1->val + ptr2->val + carry > 9) {
                ptr1->val = (ptr1->val + ptr2->val + carry) % 10;
                carry = 1;
            } else {
                ptr1->val = ptr1->val + ptr2->val + carry;
                carry = 0;
            }
            temp = ptr1;
            ptr1 = ptr1->next;
            if (!ptr2->next && carry) {
                if (!ptr1) {
                    temp->next = new ListNode(1);
                    return head1;
                }
                add(ptr1);
                break;
            }
            ptr2 = ptr2->next;
        }
        return head1;
    }

    ListNode* add(ListNode* head) {
        ListNode* ptr = head;
        while(ptr && carry) {
            if (ptr->val + carry > 9) {
                ptr->val = (ptr->val + carry) % 10;
                carry = 1;
            } else {
                ptr->val = ptr->val + carry;
                carry = 0;
            }
            if(!ptr->next && carry) {
                ptr->next = new ListNode(1);
                break;
            }
            ptr = ptr->next;
        }
        return head;
    }
    
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int count1 = count(l1), count2 = count(l2);
        if (count1 >= count2) {
            l1 = add(l1, l2);
            return l1;
        } else {
            l2 = add(l2, l1);
            return l2;
        }
    }
};