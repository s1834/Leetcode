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
    int numberOfNodes(ListNode* head) {
        int count = 0;
        while(head) {
            count++;
            head = head->next;
        }
        return count;
    }

public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head) return nullptr;

        int count = numberOfNodes(head);
        if(count == k || k == 0 || count == 1) return head;
        count = count < k ? count - (k % count) : count - k;

        ListNode* ptr1 = head;
        while(ptr1->next && --count) ptr1 = ptr1->next;

        ListNode* ptr2 = head;
        head = ptr1->next;
        ptr1->next = nullptr;
        ptr1 = head;
        while(ptr1->next) ptr1 = ptr1->next;

        ptr1->next = ptr2;
        return head;
    }
};