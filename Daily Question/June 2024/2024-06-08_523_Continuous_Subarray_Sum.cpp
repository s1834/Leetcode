class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size(), curSum = 0;
        for (int i = 0; i < n; i++) {
            curSum = nums[i];
            for (int j = i + 1; j < n; j++) {
                curSum += nums[j];
                if(curSum % k == 0) {
                    return true;
                }
            }
        }
        return false;
    }
};