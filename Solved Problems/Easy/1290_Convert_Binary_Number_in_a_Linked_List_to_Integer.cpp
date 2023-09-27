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
    int getDecimalValue(ListNode* head) {
        stack<int> st;
        while (head != NULL) {
            st.push(head->val);
            head = head->next;
        }
        int n = st.size(), ans = 0, mul = 1;
        for (int i = 0; i < n; i++) {
            ans += st.top() * mul;
            mul *= 2;
            st.pop();
        } 

        return ans;
    }
};