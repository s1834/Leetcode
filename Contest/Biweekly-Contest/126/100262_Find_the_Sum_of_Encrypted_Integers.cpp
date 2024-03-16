class Solution {
public:
    int sumOfEncryptedInt(vector<int>& nums) {
        int n = nums.size(), sum = 0;
        for(int i = 0; i < n; i++) {
            int temp = nums[i], max = INT_MIN;
            while(temp) {
                if(temp % 10 > max) {
                    max = temp % 10;
                }
                temp /= 10;
            }
            
            temp = nums[i];
            int num = 0, mul = 1;
            while(temp) {
                num += max * mul;
                temp /= 10;
                mul *= 10;
            }
            nums[i] = num;
            sum += nums[i];
        }
        
        return sum;
    }
};