class Solution {
public:
    vector<int> sortEvenOdd(vector<int>& nums) {
        vector<int> odd, even;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (i % 2) {
                odd.push_back(nums[i]);
            } else {
                even.push_back(nums[i]);
            }
        }
        sort(odd.begin(), odd.end(), greater<int>());
        sort(even.begin(), even.end());

        vector<int> ans;
        int ind = 0;
        n /= 2;
        for (int i = 0; i < n; i++) {
            ans.push_back(even[ind]);
            ans.push_back(odd[ind]);
            ind++;
        }

        if (odd.size() != even.size()) {
            ans.push_back(even[ind]);
        }
        return ans;
    }
};