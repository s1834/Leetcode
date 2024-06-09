class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();
        int prefixMod = 0, ans = 0;
        vector<int> mod(k);
        mod[0] = 1;
        for(int i = 0; i < n; i++) {
            prefixMod = (prefixMod + nums[i] % k + k) % k;
            ans += mod[prefixMod];
            mod[prefixMod]++;
        }
        return ans;
    }
};