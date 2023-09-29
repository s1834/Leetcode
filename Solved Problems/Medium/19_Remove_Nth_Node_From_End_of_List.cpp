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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* ptr = head;
        int count = 0;
        while (ptr) {
            count++;
            ptr = ptr->next;
        }
        if (count < 2) {
            return NULL;
        }
        ptr = head;
        if (count == n) {
            head = ptr->next;
        }
        count = count - n - 1;
        for (int i = 0; i < count; i++) {
            ptr = ptr->next;
        }
        ptr->next = ptr->next->next;
        return head;
    }
};