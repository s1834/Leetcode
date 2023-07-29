class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        int n1 = nums1.size(), n2 = nums2.size(), k =0;
        vector<int> ans;
        for (int i = 0; i < n1; i++) {
            for (int j = k; j < n2; j++) {
                if (nums1[i] == nums2[j]) {
                    ans.push_back(nums1[i]);
                    k++;
                    break;
                }
            }
        }

        return ans;
    }
};