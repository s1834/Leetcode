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
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* ptr = head, *front, *end;
        int count = 0;
        while (ptr) {
            count++;
            if (count == k) {
                front = ptr;
            }
            ptr = ptr->next;
        }
        if (count < 2) {
            return head;
        }

        ptr = head;
        count -= k;
        while (ptr && count) {
            count--;
            ptr = ptr->next;
        }
        end = ptr;
        front->val = front->val + end->val;
        end->val = front->val - end->val;
        front->val = front->val - end->val;

        return head;
    }
};