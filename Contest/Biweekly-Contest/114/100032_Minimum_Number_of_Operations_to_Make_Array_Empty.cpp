class Solution {
public:
    int minOperations(vector<int>& nums) {
        map<int,int> mp;
        int n = nums.size(), count = 0;
        for (int i = 0; i < n; i++) {
            mp[nums[i]]++;
        }
        for(auto x:mp) {
            while(x.second >= 1) {
                if(x.second - 3 > 1 || x.second - 3 == 0) {
                    x.second -= 3;
                    count++;
                } else if (x.second - 2 > 1 || x.second - 2 == 0) {
                    x.second -= 2;
                    count++;
                } else {
                    return -1;
                }
            }
        }

        return count;
    }
};