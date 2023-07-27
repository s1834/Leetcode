class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max = nums[0], temp = 0, n = nums.size(), j = 0;
        for (int i = j + 1; i < n; i++) {
            temp = nums[j];
            if (temp > max) {
                max = temp;
            }
            temp += nums[i];
            if (temp > max) {
                max = temp;
            }
            if (i == n - 1) {
                j++;
                i = j;
            }
        }
        

        return max;
    }
};