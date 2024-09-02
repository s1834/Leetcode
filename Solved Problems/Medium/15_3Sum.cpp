class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> st;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; i++) {
            int j = i + 1, k = n - 1;
            while(j < k) {
                int sum =  nums[i] + nums[j] + nums[k];
                if(!sum) {
                    st.insert({nums[i], nums[j], nums[k]});
                    j++;
                    k--;
                }
                else if (sum < 0) j++;
                else k--;
            }
        }
        vector<vector<int>> ans(st.begin(), st.end());
        return ans;
    }
};