class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max = nums[0], temp = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            temp += nums[i];
            if (nums[i] > temp) {
                temp = nums[i];
            }
            if (temp > max) {
                max = temp;
            }
        }

        return max;
    }
};