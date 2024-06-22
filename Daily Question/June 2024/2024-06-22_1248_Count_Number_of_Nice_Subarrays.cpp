class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            bool exists = false;
            int count = 0;
            for (int j = i; j < n; j++) {
                if(nums[j] % 2) {
                    count++;
                }
                if(count == k) {
                    exists = true;                
                    ans++;
                }
            }
            if(!exists) {
                break;
            }
        }
        return ans; 
    }
};