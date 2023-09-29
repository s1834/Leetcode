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
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* ptr = head;
        int count = 0;
        while (ptr) {
            count++;
            ptr = ptr->next;
        }
        ptr = head;
        count = count % 2 ? (count - 1) / 2 - 1 : count / 2 - 1;
        for (int i = 0; i < count; i++) {
            ptr = ptr->next;
        }
        ptr->next = ptr->next->next;
        return head;
    }
};