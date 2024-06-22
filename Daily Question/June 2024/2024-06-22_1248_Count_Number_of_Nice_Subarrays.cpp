class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int ind = 0, count = 0, ans = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            if(nums[i] % 2) {
                k--;
                count = 0;
            }
            while(!k) {
                k += (nums[ind] % 2);
                count++;
                ind++;
            }
            ans += count;
        }
        return ans;
    }
};