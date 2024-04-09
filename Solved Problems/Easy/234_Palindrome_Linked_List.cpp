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
    bool palindrome(ListNode* &begin, ListNode* &end) {
        if(!end) {
            return true;
        }

        bool ans = palindrome(begin, end->next) && (begin->val == end->val);
        begin = begin->next;

        return ans;
    }

    bool isPalindrome(ListNode* head) {
        return palindrome(head, head);
    }
};