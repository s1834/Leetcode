class Solution {
    public:
        vector<int> transformArray(vector<int>& nums) {
            int even = 0, odd = 0;
            for(auto x : nums) {
                if(x % 2) odd++;
                else even++;
            }
    
            vector<int> ans;
            while(even--) ans.push_back(0);
            while(odd--) ans.push_back(1);
    
            return ans;
        }
    };