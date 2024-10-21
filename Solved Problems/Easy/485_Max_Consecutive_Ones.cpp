class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size(), temp = 0, mx = INT_MIN;
        for (int i = 0; i < n; i++) {
            if(nums[i] == 0) {
                if(temp > mx) mx = temp;
                temp = 0;
                continue;
            }
            temp++;
        }

        return mx > temp ? mx : temp;
    }
};