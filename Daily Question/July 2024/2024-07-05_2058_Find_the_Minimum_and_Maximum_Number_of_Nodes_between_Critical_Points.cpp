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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if(!head->next->next) return {-1, -1};

        ListNode* prev = head, *cur = prev->next, *nxt = cur->next;
        vector<int> ind;
        int count = 2;
        while(nxt) {
            if((cur->val > prev->val && cur->val > nxt->val) || (cur->val < prev->val && cur->val < nxt->val)) ind.push_back(count);
            prev = cur;
            cur = nxt;
            nxt = nxt->next;
            count++;
        }

        int mn = INT_MAX, n = ind.size() - 1;
        for(int i = 0; i < n; i++) mn = min(mn, ind[i + 1] - ind[i]);
        return {mn, ind[n] - ind[0]};
    }
};