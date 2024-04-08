class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        map<int, int> mp1, mp2;
        int n1 = nums1.size(), n2 = nums2.size();
        for (int i = 0; i < n1; i++) {
            mp1[nums1[i]]++;
        }
        for (int i = 0; i < n2; i++) {
            mp2[nums2[i]]++;
        }
        vector<vector<int>> ans(2);
        for(auto x : mp1) {
            if(!mp2[x.first]) {
                ans[0].push_back(x.first);
            }
        }
        for(auto x : mp2) {
            if(!mp1[x.first]) {
                ans[1].push_back(x.first);
            }
        }

        return ans; 
    }
};