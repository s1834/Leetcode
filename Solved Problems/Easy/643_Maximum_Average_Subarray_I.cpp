class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double ans = INT_MIN, temp = 0;
        int n = nums.size(), count = 0, j = 0;
        for (int i = j; i < n; i++) {
            temp += nums[i];
            count++;
            if (count == k) {
                temp /= k;
                if (temp > ans) {
                    ans = temp;
                }
                j++;
                i = j - 1;
                count = 0;
                temp = 0;
            }
        }

        return ans;
    }
};