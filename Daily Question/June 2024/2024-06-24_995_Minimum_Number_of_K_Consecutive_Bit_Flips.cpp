class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size(), count = 0;
        for (int i = 0; i < n - k + 1; i++) {
            if(nums[i] == 0) {
                for(int j = i; j < i + k; j++) {
                    nums[j] = nums[j] ? 0 : 1;
                }
                count++;
            }
        }

        for(int i = n - k + 1; i < n; i++) {
            if(nums[i] == 0) {
                return -1;
            }
        }
        return count;
    }
};