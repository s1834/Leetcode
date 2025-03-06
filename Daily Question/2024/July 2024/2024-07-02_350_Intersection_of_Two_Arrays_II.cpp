class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> mp1, mp2;
        int n = nums1.size();
        for(int i = 0; i < n; i++) {
            mp1[nums1[i]]++;
        }
        
        n = nums2.size();
        for(int i = 0; i < n; i++) {
            mp2[nums2[i]]++;
        }

        vector<int> intersection;
        for(auto x : mp1) {
            if(mp2[x.first]) {
                if(mp2[x.first] < x.second) {
                    for(int i = 0; i < mp2[x.first]; i++) intersection.push_back(x.first);
                } else {
                    for(int i = 0; i < x.second; i++) intersection.push_back(x.first);
                }
            }
        }
        
        return intersection;
    }
};