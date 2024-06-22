class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            ans += nums[i] % 3 == 0 ? 0 : 1;
        }
        return ans;
    }
};