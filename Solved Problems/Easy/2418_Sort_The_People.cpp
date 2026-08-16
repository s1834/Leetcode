class Solution {
    public:
        vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
            vector<pair<int, int>> v;
            int n = names.size();
            for(int i = 0; i < n; i++) v.push_back({heights[i], i});
            sort(v.begin(), v.end(), greater<pair<int, int>>());
    
            vector<string> ans;
            for(auto &x : v) ans.push_back(names[x.second]);
    
            return ans;
        }
    };