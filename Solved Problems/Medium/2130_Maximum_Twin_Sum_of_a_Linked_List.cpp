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
    int pairSum(ListNode* head) {
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
        count /= 2;
        ListNode *prev = NULL, *cur = head, *nxt = cur->next;
        while (count) {
            cur->next = prev;
            prev = cur;
            cur = nxt;
            nxt = cur->next;
            count--;
        }
        
        int sum = 0, tempSum = 0;
        while (prev && cur) {
            tempSum = prev->val + cur->val;
            prev = prev->next;
            cur = cur->next;
            if (tempSum > sum) {
                sum = tempSum;
            }
        }

        return sum;
    }
};