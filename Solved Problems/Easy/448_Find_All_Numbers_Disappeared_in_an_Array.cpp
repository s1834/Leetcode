class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            int value = abs(nums[i]);
            if(value == n) {
                nums[0] = -abs(nums[0]);
            } else {
                nums[value] = -abs(nums[value]);
            }
        }
        vector<int> ans;
        for(int i = 1; i < n; i++) {
            if(nums[i] > 0) ans.push_back(i);
        }
        if(nums[0] > 0) ans.push_back(n);
        return ans;
    }
};