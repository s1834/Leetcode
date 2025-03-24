class Solution {
    public:
        vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
            set<int> s;
            int i = 0, j = 0, n = nums1.size(), m = nums2.size();
            sort(nums1.begin(), nums1.end());
            sort(nums2.begin(), nums2.end());
            while(i < n && j < m) {
                if(nums1[i] == nums2[j]) {
                    s.insert(nums1[i]);
                    i++;
                    j++;
                } else if(nums1[i] < nums2[j]) i++;
                else j++;
            }
            return vector<int> (s.begin(), s.end());
        }
    };