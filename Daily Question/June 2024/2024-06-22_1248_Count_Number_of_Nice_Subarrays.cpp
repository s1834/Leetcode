class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int lastOddInd = -1, count = 0, n = nums.size();
        bool exists = false;
        for (int i = n - 1; i >= 0; i--) {
            if(nums[i] % 2) {
                if(lastOddInd == -1) {
                    lastOddInd = i;
                }
                count++;
            }
            if(count == k) {
                exists = true;
                break;
            }
        }

        if(!exists) {
            return 0;
        }

        int ans = 0;
        for (int i = 0; i < lastOddInd + 1; i++) {
            count = 0;
            for (int j = i; j < n; j++) {
                if(nums[j] % 2) {
                    count++;
                }
                if(count == k) {
                    ans++;
                }
                if(count > k) {
                    break;
                }
            }
        }
        return ans; 
    }
};