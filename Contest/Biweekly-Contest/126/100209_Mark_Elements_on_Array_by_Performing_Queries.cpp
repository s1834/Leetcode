class Solution {
public:
    vector<long long> unmarkedSumArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), sum = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
        }
        
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        
        int m  = queries.size();
        vector<long long> ans;
        for(int i = 0; i < m; i++) {
            if(nums[queries[i][0]] != 0) {
                sum -= nums[queries[i][0]];
                sorted.erase(find(sorted.begin(), sorted.end(), nums[queries[i][0]]));
                
        
                nums[queries[i][0]] = 0;
            }
            for (int j = 0; j < queries[i][1] && !sorted.empty(); j++) {
                    vector<int>::iterator rm = find(nums.begin(), nums.end(), sorted[0]);
                    int ind;
                    if(rm!=nums.end()) {
                        ind = rm-nums.begin();
                    }
                    sum -=  nums[ind];
                    nums[ind] = 0;
                    sorted.erase(sorted.begin(), sorted.begin() + 1);
                }
                
                ans.push_back(sum);
        }
        
        return ans;
    }
};