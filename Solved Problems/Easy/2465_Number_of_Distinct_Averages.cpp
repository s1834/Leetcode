class Solution {
    public:
        int distinctAverages(vector<int>& nums) {
            set<int> s;
            sort(nums.begin(), nums.end());
            int i = 0, j = nums.size() - 1;
            while(i < j) {
                s.insert((nums[i] + nums[j]) / 2);
                i++;
                j--;
            }
            return s.size();
        }
    };