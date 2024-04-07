class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        vector<int> ans;
        int n = nums.size();
        long long int sum = 0;
        if(n < k * 2 + 1) {
            for (int i = 0; i < n; i++) {
                ans.push_back(-1);
            }
            return ans;
        }

        for (int i = 0; i < k; i++) {
            sum += nums[i];
            ans.push_back(-1);
        }

        for (int i = k; i < k + k; i++) {
            sum += nums[i];
        }

        for (int i = k; i < n - k; i++) {
            sum += nums[i + k];
            ans.push_back(round(sum / (k + k + 1)));
            sum -= nums[i - k];
        }

        for (int i = 0; i < k; i++) {
            ans.push_back(-1);
        }

        return ans;
    }
};