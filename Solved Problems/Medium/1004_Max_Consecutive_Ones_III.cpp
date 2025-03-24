class Solution {
    public:
        int longestOnes(vector<int>& nums, int k) {
            int n = nums.size(), count = 0;
            for(int i = 0; i < n; i++) {
                int temp = k, tempCount = 0;
                for(int j = i; j < n; j++) {
                    if(nums[j] == 1) tempCount++;
                    else if(nums[j] == 0 && temp) {
                        tempCount++;
                        temp--;
                    } else break;
                }
                count = count > tempCount ? count : tempCount;
            }
            return count;
        }
    };