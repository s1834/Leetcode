class Solution {
    public:
        vector<int> findMissingElements(vector<int>& nums) {
            sort(nums.begin(), nums.end());
            int x = nums[0] + 1, y = nums[nums.size() - 1];
            unordered_set<int> st(nums.begin(), nums.end());
            vector<int> ans;
            for(int i = x; i < y; i++) {
                if(st.find(i) == st.end()) ans.push_back(i);
            }
            return ans;
        }
    };