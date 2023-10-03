class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        // v1
        // map<int, int> mp;
        // int n = nums.size();
        // for (int i = 0; i < n; i++) {
        //     mp[nums[i]]++;
        // }

        // vector<int> vec;
        // for (auto x : mp) {
        //     if (x.second == 2) {
        //         vec.push_back(x.first);
        //     }
        // }

        // return vec;


        // v2
        vector<int> vec(nums.size(), 0), ans;
        for (int i = 0; i < nums.size(); i++) {
            if (vec[nums[i] - 1] != 0) {
                ans.push_back(nums[i]);
            } else {
                vec[nums[i] - 1] = nums[i];
            }
        } 
        return ans;
    }
};