class Solution {
public:
    int minIncrementForUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int moves = 0, n = nums.size();
        for (int i = 1; i < n; i++) {
            if(nums[i - 1] >= nums[i]) {
                moves += nums[i - 1] + 1 - nums[i];
                nums[i] = nums[i - 1] + 1;
            }
        }
        return moves;
    }
};