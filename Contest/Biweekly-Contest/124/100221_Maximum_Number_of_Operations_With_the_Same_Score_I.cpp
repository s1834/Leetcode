class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int n = nums.size(), sum = nums[0] + nums[1], count = 1;
        for(int i = 2; i < n; i += 2) {
            if(nums[i] + nums[i + 1] != sum) {
                break;
            }
            count++;
        }
        
        return count;
    }
};