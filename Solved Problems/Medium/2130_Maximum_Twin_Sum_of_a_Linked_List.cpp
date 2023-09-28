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
        if (!head || !head->next) {
            return 0;
        }

        int sum = 0, tempSum = 0, count = 0;
        ListNode* cur = head, *prev = NULL;
        while (cur) {
            count++;
            cur = cur->next;
        }
        cur = head;
        int n = count / 2 - 1;
        for (int i = 0; i < n; i++) {
            prev = cur;
            cur = cur->next;
        }

        while (count && cur->next->next) {
            tempSum += cur->val + cur->next->val;
            if (sum < tempSum) {
                sum = tempSum;
            }
            prev->next = cur->next->next;
            cur = prev;
            prev = head;
            count -= 2;
            n = count / 2 - 2;
            tempSum = 0;
            for (int i = 0; i < n; i++) {
                prev = prev->next;
            }
        }
        tempSum += cur->val + cur->next->val;
        if (sum < tempSum) {
            sum = tempSum;
        }

        return sum;
    }
};