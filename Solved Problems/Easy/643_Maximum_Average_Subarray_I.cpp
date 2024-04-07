class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        double ans = 0, mx = 0;
        for(int i = 0; i < k; i++) {
            ans += nums[i];
        }
        
        mx = ans / k;
        ans -= nums[0];
        for(int i = k; i < n; i++) {
            ans += nums[i];
            mx = max(mx, ans / k);
            ans -= nums[i - k + 1];
        }
        return mx;
    }
};