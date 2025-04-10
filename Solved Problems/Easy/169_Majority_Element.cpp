class Solution {
    public:
        int majorityElement(vector<int>& nums) {
            sort(nums.begin(), nums.end());
            int n = nums.size(), temp = 1;
            for(int i = 1; i < n; i++) {
                if(nums[i] != nums[i - 1]) {
                    if(temp > n / 2) return nums[i - 1];
                    temp = 0;
                }
                temp++;
            }
            return nums[n - 1];
        }
    };