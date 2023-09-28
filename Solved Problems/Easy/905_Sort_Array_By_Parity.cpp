class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        vector<int> ans, odd;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2) {
                odd.push_back(nums[i]);
            } else {
                ans.push_back(nums[i]);
            }
        }
        n = odd.size();
        for (int i = 0; i < n; i++) {
            ans.push_back(odd[i]);
        }
        
        return ans;
    }
};