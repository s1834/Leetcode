/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA->next == NULL && headB->next == NULL) {
            if(headA == headB) {
                return headA, headB;
            }
            return NULL;
        }
 
        ListNode* ptrB = headB;
        while (headA) {
            while (ptrB) {
                if (headA->next == ptrB->next) {
                    return headA->next, ptrB->next;
                }
                ptrB = ptrB->next;
            }
            ptrB = headB;
            headA = headA->next;
        }

        return NULL;
    }
};