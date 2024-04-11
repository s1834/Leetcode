class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> mp;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            mp[nums[i]]++;
        }

        multimap<int, int, greater<int>> mmp;
        for(auto x : mp) {
            mmp.insert({x.second, x.first});
        }

        vector<int> ans;
        for(auto x : mmp) {
            if(!k) {
                break;
            }
            ans.push_back(x.second);
            k--;
        }
        
        return ans;
    }
};