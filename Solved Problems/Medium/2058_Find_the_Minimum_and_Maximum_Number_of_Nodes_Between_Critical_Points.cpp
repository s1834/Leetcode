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
        vector<int> vec;
        if (!head->next->next) {
            vec.push_back(-1);
            vec.push_back(-1);
            return vec;
        }

        int count = 2;
        ListNode* prev = head, *cur = prev->next, *nxt = cur->next;
        while(nxt) {
            if((cur->val > prev->val && cur->val > nxt->val) || (cur->val < prev->val && cur->val < nxt->val)) {
                vec.push_back(count);
            }
            count++;
            prev = cur;
            cur = nxt;
            nxt = nxt->next;
        }

        int n = vec.size(), mn = INT_MAX;
        vector<int> ans;
        if (n < 2) {
            ans.push_back(-1);
            ans.push_back(-1);
            return ans;
        }
        for (int i = 0; i < n - 1; i++) {
            if (mn > vec[i + 1] - vec[i]) {
                mn = vec[i + 1] - vec[i];
            }
        }
        ans.push_back(mn);
        ans.push_back(vec[n - 1] - vec[0]);

        return ans;
    }
};