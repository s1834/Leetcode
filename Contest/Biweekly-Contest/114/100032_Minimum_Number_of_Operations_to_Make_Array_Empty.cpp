class Solution {
public:
    int minOperations(vector<int>& nums) {
        map<int,int> mp;
        int n = nums.size(), count = 0;
        for (int i = 0; i < n; i++) {
            mp[nums[i]]++;
        }
        for(auto x:mp) {
            if (x.second % 3 == 0) {
                count += x.second / 3;
            } else if (x.second % 2 == 0) {
                count += x.second / 2;
            } else {
                return -1;
            }
        }
        
        return count;
    }
};