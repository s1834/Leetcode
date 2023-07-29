class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        map <int,int> mp1, mp2;
        for (auto x:nums1) {
            mp1[x]++;
        }
        for (auto x:nums2) {
            if(mp1[x]-- > 0) {
                mp2[x]++;
            }
        }

        vector<int> vec;
        int count;
        for (auto x:mp2) {
            count = x.second;
            while (count--) {
                vec.push_back(x.first);
            }
        }

        return vec;
    }
};