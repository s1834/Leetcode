class Solution {
    public:
        vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
            int n = grid.size();
            map<int, int> mp;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    mp[grid[i][j]]++;
                }
            }
    
            n = n * n;
            for(int i = 0; i < n; i++) {
                mp[i + 1]++;
            }
    
            int repeated = 0, missing = 0;
            for(auto x : mp) {
                if(x.second == 3) repeated = x.first;
                if(x.second == 1) missing = x.first;
            }
            
            return {repeated, missing};
        }
    };