class Solution {
    public:
        int longestOnes(vector<int>& nums, int k) {
            int n = nums.size(), count = 0;
            for(int i = 0; i < n; i++) {
                int temp = k, ptr = i, tempCount = 0;
                while(ptr < n) {
                    if(nums[ptr] == 1) tempCount++;
                    else if(nums[ptr] == 0 && temp) {
                        tempCount++;
                        temp--;
                    } else break;
                    ptr++;
                }
                count = count > tempCount ? count : tempCount;
            }
            return count;
        }
    };