class Solution {
    public:
        int missingMultiple(vector<int>& nums, int k) {
            unordered_set<int> s;
            for(auto &x : nums) s.insert(x);
            
            int mul = k;
            while(true) {
                if(s.find(k) == s.end()) return k;
                k += mul;
            }
    
            return 0;
        }
    };