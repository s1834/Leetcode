class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return true;
        }

        int flag = nums[0] < nums[1] ? 0 : 1;
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