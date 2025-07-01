class Solution {
    public:
        int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
            int n = queries.size(), count = 0, flag;
            for (int i = 0; i < n; i++) {
                flag = 0;
                for(int j = queries[i][0]; j <= queries[i][1]; j++) {
                    if(nums[j] != 0) {
                        nums[j] = nums[j] < queries[i][2] ? nums[j] - nums[j] : nums[j] - queries[i][2];
                        flag = 1;
                    } 
                }
                if(flag) count = i + 1;
            }
            
            n = nums.size();
            for(int i = 0; i < n; i++) if(nums[i]) return -1;
            return count;
        }
    };