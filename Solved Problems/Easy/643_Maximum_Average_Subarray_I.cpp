class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double ans = INT_MIN, temp = 0;
        int n = nums.size();
        for (int i = 0; i < n - k + 1; i++) {
            temp += nums[i];
            for (int j = i + 1; j < n && j < i + k; j++) {
                temp += nums[j];
            }
            temp /= k;
            if (temp > ans) {
                ans = temp;
            }
            temp = 0;
        }

        return ans;
    }
};