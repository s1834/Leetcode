class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return true;
        }

        int flag = 2;
        while (flag == 2) {
            for (int i = 1; i < n; i++) {
                if (nums[0] != nums[i]) {
                    flag = nums[0] < nums[i] ? 0 : 1;
                }
                if (flag == 2 && i == n - 1) {
                    return true;
                }
            }
        }

        if (flag) {
            for (int i = 0; i < n - 1; i++) {
                if (nums[i] < nums[i + 1]) {
                    return false;
                }
            }
        } else {
            for (int i = 0; i < n - 1; i++) {
                if (nums[i] > nums[i + 1]) {
                    return false;
                }
            }
        }

        return true;
    }
};