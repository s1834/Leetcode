class Solution {
    public:
        vector<int> resultArray(vector<int>& nums) {
            vector<int> result, temp;
            result.push_back(nums[0]);
            temp.push_back(nums[1]);
    
            int n = nums.size();
            for(int i = 2; i < n; i++) {
                if(result.back() > temp.back()) result.push_back(nums[i]);
                else temp.push_back(nums[i]);
            }
            
            for (auto x : temp) result.push_back(x);
            return result;
        }
    };