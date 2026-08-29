class Solution {
    public:
        vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            int n = nums.size();
            for(int i = 0; i < n; i++) pq.push({nums[i], i});
    
            while(k--) {
                auto x = pq.top();
                pq.pop();
                pq.push({x.first * multiplier, x.second});
            }
    
            vector<int> ans(n);
            while(!pq.empty()) {
                auto x = pq.top();
                pq.pop();
                ans[x.second] = x.first;
            }
            
            return ans;
        }
    };