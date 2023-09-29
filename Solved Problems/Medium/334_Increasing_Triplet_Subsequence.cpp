class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) {
            return false;
        }

        for (int i = 0; i < n - 2; i++) {
            if (nums[i] < nums[i + 1] && nums[i + 1] < nums[i + 2]) {
                return true;
            }
        }

        return false;
    }
};