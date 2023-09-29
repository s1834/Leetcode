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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* ptr1 = list1;
        while(a - 1) {
            a--;
            b--;
            ptr1 = ptr1->next;
        }
        ListNode* temp = ptr1->next;
        ptr1->next = list2;
        ptr1 = temp;
        
        ListNode* ptr2 = list2;
        while (ptr2->next) {
            ptr2 = ptr2->next;
        }
        while(b--) {
            ptr1 = ptr1->next;
        }
        ptr2->next = ptr1;

        return list1;
    }
};