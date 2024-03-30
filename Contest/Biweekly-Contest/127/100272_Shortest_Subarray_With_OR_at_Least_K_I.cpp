class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size(), temp = 0, sum = 0, tempCount = 0, count = INT_MAX;
        for (int i = 0; i < n; i++) {
            temp += nums[i];
            tempCount++;
            if(temp > k) {
                if(count > tempCount) {
                    count = tempCount;
                }
                sum = temp;
                temp = 0;
                tempCount = 0;
            }
            if(nums[i] >= k) {
                temp = nums[i];
                count = 1;
                temp = 0;
                tempCount = 0;
            }
        }
        if(sum > k) {
            return count;
        }
        return -1;
    }
};