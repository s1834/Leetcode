class Solution {
    public:
        int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
            int n = nums.size(), m = pattern.size(), count = 0;
            for(int i = 0; i < n - m; i++) {
                bool flag = true;
                for(int j = 0; j < m; j++) {
                    if(pattern[j] == 1) {
                        if(nums[i + j + 1] < nums[i + j]) {
                            flag = false;
                            break;
                        }
                    } else if(pattern[j] == -1) {
                        if(nums[i + j + 1] > nums[i + j]) {
                            flag = false;
                            break;
                        }
                    } else {
                        if(nums[i + j + 1] != nums[i + j]) {
                            flag = false;
                            break;
                        }
                    }
                }
                if(flag) count++;
            }
            return count;
        }
    };