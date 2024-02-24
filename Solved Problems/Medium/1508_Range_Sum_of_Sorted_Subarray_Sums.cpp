class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        vector<long long> sum;
        long long int count = -1;
        for(int i = 0; i < n; i++) {
            sum.push_back(nums[i]);
            count++;
            for (int j = i + 1; j < n; j++) {
                sum.push_back(nums[j] + sum[count]);
                count++;
            }
        }
        
        sort(sum.begin(), sum.end());
        count = 0;
        for (int i = left - 1; i < right; i++) {
            count += sum[i];
        }

        return count % 1000000007;
    }
};