class Solution {
public:
    int minOperations(vector<int>& nums) {
        map<int,int> mp;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            mp[nums[i]]++;
        }
        
        int count = 0;
        bool change = false;
        for(int i = 0; i < n; i++) {
            if(change ? nums[i] == 0 : nums[i] == 1) {
                mp[1]--;
            } else {
                mp[0]--;
                mp[0] = mp[0] + mp[1];
                mp[1] = mp[0] - mp[1];
                mp[0] = mp[0] - mp[1];
                count++;
                change = change ? false : true;
            }
            
            if(mp[0] == 0) {
                break;
            }
            
        }
        return count;
    }
};