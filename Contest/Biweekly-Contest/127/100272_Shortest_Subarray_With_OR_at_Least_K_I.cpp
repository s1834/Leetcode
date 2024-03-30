class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size(), temp = 0, sum = 0, tempCount = 0, count = INT_MAX;
        
        if (nums[0] >= k) {
            return 1;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                temp |= nums[j];
                tempCount++;
                if(temp >= k) {
                    if(count > tempCount) {
                        count = tempCount;
                        break;
                    }
                    sum = temp;
                    temp = 0;
                    tempCount = 0;
                }
                if(nums[j]  >= k) {
                    sum = nums[j];
                    count = 1;
                    temp = 0;
                    tempCount = 0;
                    break;
                }
            }
        }
        if(sum >= k) {
            return count;
        }
        return -1;
    }
};