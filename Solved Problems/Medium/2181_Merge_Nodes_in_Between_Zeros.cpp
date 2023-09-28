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
    ListNode* mergeNodes(ListNode* head) {
        int sum = 0, flag = 1;
        ListNode* ptr, *head1;
        head = head->next;
        while(head->next) {
            if (head->val == 0) {
                ListNode* newNode = new ListNode(sum);
                if (flag) {
                    head1 = newNode;
                    ptr = head1;
                    flag = 0;
                } else {
                    ptr->next = newNode;
                    ptr = newNode;
                }
                sum = 0;
                head = head->next;
            }
            sum += head->val;
            head = head->next;

        }
        ListNode* newNode = new ListNode(sum);
        ptr->next = newNode;

        return head1;
    }
};