class Solution {
public:
    int smallestRangeII(vector<int>& nums, int k) {
        int n = nums.size(), mx = 0, mn = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (nums[i] > k) {
                nums[i] -= k;
            } else {
                nums[i] += k;
            }
            if (nums[i] > mx) {
                mx = nums[i];
            }
            if (nums[i] < mn) {
                mn = nums[i];
            }
        }

        return mx - mn;
    }
};