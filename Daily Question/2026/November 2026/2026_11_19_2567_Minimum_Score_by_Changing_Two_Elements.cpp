class Solution {
    public:
        int minimizeSum(vector<int>& nums) {
            int n = nums.size();
            sort(nums.begin(), nums.end());
    
            // low score = 0, just minimize highest
            return min({
                nums[n-3] - nums[0], // remove 2 biggest
                nums[n-1] - nums[2], // remove 2 smallest
                nums[n-2] - nums[1]  // remove 1 smallest and 1 biggest
            });
        }
    };    