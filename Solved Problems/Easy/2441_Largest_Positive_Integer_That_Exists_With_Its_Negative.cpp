class Solution {
public:
    int findMaxK(vector<int>& nums) {
        map<int, int> mp;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            mp[abs(nums[i])]++;
        }

        int max = -1;
        for(auto x : mp) {
            if(x.second > 1 && x.first > max) {
                max = x.first;
            }
        }

        return max;
    }
};