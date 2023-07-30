class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        if (nums[0] != 1) {
            ans.push_back(nums[0]);
            ans.push_back(1);
            return ans;
        }

        for (int i = 0; i < n - 1; i++) {
            if(nums[i] == nums[i + 1]) {
                if (i > 0 && nums[i] != nums[i - 1] + 1) {
                    ans.push_back(nums[i]);
                    ans.push_back(nums[i - 1] + 1);
                    break;
                } else {
                    ans.push_back(nums[i]);
                    ans.push_back(nums[i] + 1);
                    break;
                }
            }
        }

        return ans;
    }
};