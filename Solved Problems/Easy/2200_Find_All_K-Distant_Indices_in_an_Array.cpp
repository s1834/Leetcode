class Solution {
    public:
        vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
            set<int> s;
            int n = nums.size(), i = 0, j = 0;
            while(j < n) {
                if(abs(i - j) <= k) {
                    if(nums[i] == key || nums[j] == key) {
                         s.insert(i);
                         s.insert(j);
                    }
                    j++;
                } else i++;
            }
            return vector<int>(s.begin(), s.end());
        }
    };