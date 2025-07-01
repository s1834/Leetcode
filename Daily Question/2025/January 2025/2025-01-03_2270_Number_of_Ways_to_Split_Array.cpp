class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        int n = nums.size();
        
        vector<long long int> prefixLeft;
        prefixLeft.push_back(nums[0]);
        for(int i = 1; i < n; i++) prefixLeft.push_back(prefixLeft[i - 1] + nums[i]);
        
        vector<long long int> prefixRight;
        prefixRight.push_back(nums[n - 1]);
        for(int i = n - 2; i >= 0; i--) prefixRight.push_back(prefixRight.back() + nums[i]);
        reverse(prefixRight.begin(), prefixRight.end());

        int count = 0;
        for (int i = 0; i < n - 1; i++) {
            if(prefixLeft[i] >= prefixRight[i + 1]) count++;
        }
        return count;
    }
};