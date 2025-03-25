class Solution {
    public:
        vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
            set<int> s;
            int n = nums.size(), i = 0, j = 0;
            while(j < n && i < n) {
                if(abs(i - j) <= k) {
                    if(i > j && nums[i] == key) {
                         s.insert(i);
                         s.insert(j);
                         j++;
                    } else if(nums[j] == key) {
                         s.insert(i);
                         s.insert(j);
                         i++;
                    } else j++;
                } else i < j ? i++ : j++;
            }
            return vector<int>(s.begin(), s.end());
        }
    };