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
    void sum(ListNode*& head, ListNode*& ans) {
        int sum = 0;
        while(head && head->val != 0) {
            sum += head->val;
            head = head->next;
        }
        ans->next = new ListNode(sum);
        ans = ans->next;
        head = head->next;
    }
public:
    ListNode* mergeNodes(ListNode* head) {
        if(!head || !head->next) return nullptr;
        ListNode* ptr = head;
        ListNode* ans = new ListNode(0);
        head = ans;
        while(ptr && ptr->next) {
            sum(ptr->next, ans);
        }
        return head->next;
    }
};