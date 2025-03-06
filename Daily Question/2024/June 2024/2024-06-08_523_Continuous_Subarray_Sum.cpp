class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int prefixMod = 0, n = nums.size();
        map<int, int> mp;
        mp[0] = -1;

        for (int i = 0; i < nums.size(); i++) {
            prefixMod = (prefixMod + nums[i]) % k;

            if(mp.find(prefixMod) != mp.end()) {
                if(i - mp[prefixMod] > 1) {
                    return true;
                }
            } else {
                mp[prefixMod] = i;
            }
        }
        return false;
    }
};