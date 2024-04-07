class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            mp[nums[i] * nums[i]]++;
        }
        
        int i = 0;
        for(auto x : mp) {
            if(x.second == 1) {
                nums[i] = x.first;
                i++;
            } else {
                for(int j = 0; j < x.second; j++) {
                    nums[i] = x.first;
                    i++;
                }
            } 
        }
        return nums;
    }
};